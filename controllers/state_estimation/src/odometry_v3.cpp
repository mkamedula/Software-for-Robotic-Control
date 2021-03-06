#include "mgnss/state_estimation/odometry_v3.h"

#include <iomanip>

mgnss::state_estimation::OdometryV3::OdometryV3(mwoibn::robot_class::Robot& robot,
                                                std::string config_file, std::string name)
        : mgnss::modules::Base(robot)
{
        _x << 1,0,0;
        _y << 0,1,0;
        _z << 0,0,1;

        YAML::Node config = mwoibn::robot_class::Robot::getConfig(config_file);

        if (!config["modules"])
                throw std::invalid_argument(
                              std::string("Couldn't find modules configurations."));
        if (!config["modules"]["odometry"])
                throw std::invalid_argument(
                              std::string("Couldn't find odometry module configuration."));

        config = config["modules"]["odometry"];
        config["name"] = name;
        _checkConfig(config);
        _initConfig(config);
}

mgnss::state_estimation::OdometryV3::OdometryV3(mwoibn::robot_class::Robot& robot,
                                                YAML::Node config)
        : mgnss::modules::Base(robot)
{
        _x << 1,0,0;
        _y << 0,1,0;
        _z << 0,0,1;

        _checkConfig(config);
        _initConfig(config);
}

void mgnss::state_estimation::OdometryV3::_initConfig(YAML::Node config){
        _name = config["name"].as<std::string>();
        std::vector<std::string> names = _robot.getLinks(config["chain"].as<std::string>());

        _r = config["wheel_radius"].as<double>();
        _allocate(names);
        _filter_ptr.reset(new mwoibn::filters::IirSecondOrder(3, config["filter"]["cut_off_frequency"].as<double>(), config["filter"]["damping"].as<double>()));
        _vel_ptr.reset(new mwoibn::filters::IirSecondOrder(3, config["filter"]["cut_off_frequency"].as<double>(), config["filter"]["damping"].as<double>()));
        _estimation_ptr.reset(new mwoibn::filters::IirSecondOrder(4, config["velocity"]["cut_off_frequency"].as<double>(), config["velocity"]["damping"].as<double>()));

}
void mgnss::state_estimation::OdometryV3::_checkConfig(YAML::Node config){

        if (!config["chain"])
                throw std::invalid_argument(
                              std::string("Please specify srdf chain for odometry plugin."));
        if (!config["filter"])
                throw std::invalid_argument(
                              std::string("Please specify filter parameters for odometry plugin."));
        if (!config["filter"]["damping"])
                throw std::invalid_argument(
                              std::string("Please specify filter damping for odometry plugin."));
        if (!config["filter"]["cut_off_frequency"])
                throw std::invalid_argument(
                              std::string("Please specify filter cut-off frequency for odometry plugin."));
        if (!config["wheel_radius"])
                throw std::invalid_argument(
                              std::string("Please specify wheel radius [m] for odometry plugin."));

        std::cout << "OdometryV3: read " << config["chain"].as<std::string>() << " chain." << std::endl;
        std::cout << "OdometryV3: filter damping " << config["filter"]["damping"].as<double>() << std::endl;
        std::cout << "OdometryV3: filter cut-off frequency " << config["filter"]["cut_off_frequency"].as<double>() << std::endl;
        std::cout << "OdometryV3: wheel radius " << config["wheel_radius"].as<double>() << std::endl;

}

void mgnss::state_estimation::OdometryV3::_allocate(std::vector<std::string> names){
        _ids.setConstant(names.size(), mwoibn::NON_EXISTING);
        _state.setZero(names.size());
        _error.setZero(names.size());
        _distance.setZero(names.size());
        _selector.setConstant(names.size(), true); // assume all legs in ground contact
        _contacts.setConstant(names.size(), true); // assume all legs in ground contact
        _previous_state.setZero(names.size());
        _ang_vel.setZero();
        _selector_th.setConstant(mwoibn::std_utils::factorial(names.size()-1), true);
        _translation_dofs = std::vector<int>{0,1,2};
        _base_ids.setZero(3);
        _base_map.setZero(6);
        _base_map << 0, 1, 2, 3, 4, 5;
        _raw.setZero(4);

        _ground_normal = _z;
        _projection.noalias() = _ground_normal*_ground_normal.transpose();
        _projection = mwoibn::Matrix3::Identity() - _projection;


        for (const auto& name : names){
          _wheels_frames.add(mwoibn::point_handling::FramePlus(name, _robot.getModel(), _robot.state) );
          _wheels_velocity.add(mwoibn::point_handling::SpatialVelocity(_wheels_frames.end(0)) );
          // _wheels_ph.addPoint(name);
        }

        mwoibn::Vector3 axis, pelvis;
        // add a reference point on the pelvis to compute the

        axis << 0, 0, 1; // for now assume flat ground
        pelvis = _robot.state.position.get().head(3);


        for (int i = 0; i < names.size(); i++)
        {
                _axes.push_back(axis);
                _pelvis.push_back(axis);

                _directions.push_back(_wheels_frames[i].rotation().getWorld().col(2));

                mwoibn::VectorInt dof = _robot.getDof(names[i]);
                if (dof.size() == 0)
                        throw std::invalid_argument(
                                      std::string("OdometryV3: Couldn't find a link ") + names[i]);
                _ids[i] = dof[0];

                _contact_points.push_back(_wheels_frames[i].position.getWorld());
        }

        for(auto& state: _wheels_frames){
           _estimated.push_back(state->position.getWorld()); // initialize add a current point
           _step.push_back(state->position.getWorld());
        }

        _twist_ptr.reset(new mgnss::state_estimation::Twist(_contacts.size(), _contact_points, _step, _estimated, _selector));
        _velocity_ptr.reset(new mgnss::state_estimation::Velocity(_contacts.size(), _contacts, _wheels_velocity, _ground_normal, _r, _ids, _twist_es));

   }


void mgnss::state_estimation::OdometryV3::init(){

        _filter_ptr->computeCoeffs(_robot.rate());
        _vel_ptr->computeCoeffs(_robot.rate());
        _estimation_ptr->computeCoeffs(_robot.rate());
        _robot.get();

        _robot.updateKinematics();
        _robot.state.position.get(_state, _ids);
        _base_pos = _robot.state.position.get().head<3>();

        _filter_ptr->reset(_base_pos);
        _vel_ptr->reset(_ang_vel);
        _estimation_ptr->reset(mwoibn::VectorN::Zero(4));
        //std::cout << "OdometryV3 filter: initial state: " << _base_pos.transpose() << std::endl;

        for(int i = 0; i < _estimated.size(); i++) {
                _contact_points[i].noalias() = _wheels_frames[i].position.getWorld();
                _estimated[i].noalias() = _contact_points[i];
        }



        _previous_state.noalias() = _state;

        update(); // in here I should set it up to zero


}

void mgnss::state_estimation::OdometryV3::update()
{

        // std::cout << "state position\t" << _robot.state.position.get().head<6>().transpose() << std::endl;
        // std::cout << "state velocity\t" << _robot.state.velocity.get().head<6>().transpose() << std::endl;

        // _robot.command.velocity.set(_robot.state.velocity.get().head<6>(), _base_map);
        for(int i = 0; i < _base_map.size(); i++) _robot.state.velocity.set(0.0, _base_map[i]);

        for(auto& i: _translation_dofs) _robot.state.position.set(0.0 , i);
        //Get wheels position
        _robot.state.position.get(_state, _ids);

        // Compute a difference
        _error.noalias() = _state - _previous_state;

        // which legs are in ground contact
        _selector.noalias() = _contacts;
        //_wheels_frames.update(true);
        //_wheels_velocity.update(true);

        _removeTwist();

        _increment();

        _twist_ptr->update();
        _twist_es = mwoibn::Quaternion::fromAxisAngle(_z, _twist_ptr->get());

        _poseEstimation();
        _filter();
        // for(int i = 0; i < _step.size(); i++)
        //         _step[i] = _wheels_ph.getPointStateWorld(i);

        mwoibn::Quaternion temp = _twist_es*_swing;
        _base.tail<3>() = temp.toMatrix().eulerAngles(0,1,2);
        // std::cout << "base" << _base.transpose() << std::endl;
        _robot.command.position.set(_base, _base_map);
        _robot.state.position.set(_base, _base_map);


        //std::cout << _base[5].transpose() << std::endl;
        _velocity_ptr->update();
//        //here I should estimate velocity
        _raw = _velocity_ptr->get();
        _estimation_ptr->update(_velocity_ptr->get());

//
        _robot.command.velocity.set(_velocity_ptr->get().head<3>(), _translation_dofs);
        _robot.command.velocity.set(_velocity_ptr->get()[3], _base_map[5] );
//
        _previous_state.noalias() = _state;

//       // std::cout << _velocity_ptr->get().transpose() << std::endl;
//
//        //  return _base;
}

void mgnss::state_estimation::OdometryV3::_removeTwist(){

        // For now, retrive the quaternion from eulerAngles
        _last_imu = _imu;
        _imu = mwoibn::Quaternion::fromAxisAngle(_x, _robot.state.position.get()[3]);
        _imu = _imu*mwoibn::Quaternion::fromAxisAngle(_y, _robot.state.position.get()[4]);
        _imu = _imu*mwoibn::Quaternion::fromAxisAngle(_z, _robot.state.position.get()[5]);

        if (_robot.state.position.get().segment<3>(3).norm() < mwoibn::EPS)
          std::cout << "norm!\t" << _imu << std::endl;


        _last_imu.ensureHemisphere(_imu);
        mwoibn::Position _euler;
        // get robot base eueler angles
        _euler = _swing.toMatrix().eulerAngles(0, 1, 2);

        _to_euler << 1, std::sin(_euler[0])*std::sin(_euler[1])/std::cos(_euler[1]), -std::cos(_euler[0])*std::sin(_euler[1])/std::cos(_euler[1]),
                     0, std::cos(_euler[0]), std::sin(_euler[0]),
                     0, -std::sin(_euler[0])/std::cos(_euler[1]), std::cos(_euler[0])/std::cos(_euler[1]);
        // std::cout << "_last_imu\t" << _last_imu << std::endl;

        // angular velocity estimation
        mwoibn::Quaternion temp = _imu*_last_imu.inversed();

        _ang_vel = temp.log().axis();


        _temp_est = _ang_vel;

        _vel_ptr->update(_ang_vel);
        _temp_fil = _ang_vel;

        _ang_vel = 2*_ang_vel/_robot.rate();

        _ang_vel = _projection*_ang_vel; // RT!


        // remove the rotation ground ground component
        _twist_raw = _imu.twistSwing(_z,_swing);


        // set _robot.base with _swing only
        _base_ids << 3, 4, 5;
        _robot.state.position.set(_euler, _base_ids);

        _euler.noalias() = _to_euler*_ang_vel;

        _robot.state.velocity.set(_euler, _base_ids);
        //_robot.command.velocity.set(_euler, _base_ids);
        // std::cout <<"angualr\t" <<  _euler.transpose() << std::endl;

        _robot.updateKinematics();   // this way the kinematics is updated twice, that is not good, this can be easily handled in the plugin

}

void mgnss::state_estimation::OdometryV3::_filter(){
        // add imu reading
        _base.tail(3) =
                _robot.state.position.get().segment<3>(3);

        // clear estimation based on a final result
        for(int i = 0; i < _wheels_frames.size(); i++)
                _estimated[i].noalias() = _base.head<3>() + _contact_points[i];

        _base_pos = _base.head(3);
        _base_raw = _base;

        // filter the results
        _filter_ptr->update(_base_pos);

        _base.head(3) = _base_pos;

        _base_filtered = _base;
        _base_filtered.head<3>() = _base_pos;
}

void mgnss::state_estimation::OdometryV3::_increment(){
        for (int i = 0; i < _state.size(); i++)
        {
                // compute world position of the wheel axis
                _directions[i] = _wheels_frames[i].rotation().getWorld().col(2); // z axis
                // compute the wheel direction of motion
                _directions[i] = _directions[i].cross(_axes[i]);

                _directions[i].normalize();
                // compute the distance travelled
                _error[i] *= _r;
                // estimate current contact point position
                _step[i].noalias() = _directions[i] * _error[i]; // in the world frame
                _contact_points[i].noalias() = _wheels_frames[i].position.getWorld(); // in the

        }

}

void mgnss::state_estimation::OdometryV3::_applyTwist(){
        for (int i = 0; i < _state.size(); i++)
        {
                // compute world position of the wheel axis
                //_directions[i] = _twist_es.rotate(_directions[i]); // z axis
                _contact_points[i].noalias() = _twist_es.rotate(_contact_points[i]);
                // estimate current contact point position
                _estimated[i].noalias() += _twist_es.rotate(_step[i]);
        }

}

void mgnss::state_estimation::OdometryV3::_poseEstimation(){

        // estimate postion of each wheel
        _applyTwist();

        for (int i = 0; i < _wheels_frames.size(); i++) {
                // compute the distance between the contact point and base origin
                // estimate the state for each leg
                _pelvis[i].noalias() = _estimated[i] - _contact_points[i];
        }

        // choose the solution
        _compute2();               // this seems to be the best

}


int mgnss::state_estimation::OdometryV3::_min(mwoibn::VectorBool& selector, const mwoibn::VectorN& distance)
{
        int id = -1;
        double value = mwoibn::MAX_DOUBLE;
        for (int i = 0; i < selector.size(); i++)
        {
                if (selector[i] && distance[i] < value)
                {
                        id = i;
                        value = distance[i];
                }
        }
        return id;
}


int mgnss::state_estimation::OdometryV3::_max(mwoibn::VectorBool& selector, const mwoibn::VectorN& distance)
{

        int id = -1;
        double value = -1;
        for (int i = 0; i < selector.size(); i++)
        {
                if (selector[i] && distance[i] > value)
                {
                        id = i;
                        value = distance[i];
                }
        }

        return id;
}





// just chose the "median"
void mgnss::state_estimation::OdometryV3::_compute1()
{

        _distances();

        _base.head(3) = _pelvis[_min(_selector, _distance)];
}

// remove element by element
void mgnss::state_estimation::OdometryV3::_compute2()
{
        if (_selector.count() < 3)
        {
                _average(); // return average no better option?
                return;
        }

        if (_selector.count() == 3)
        {
                _compute1();
                return;
        }

        _distances();
        _selector[_max(_selector, _distance)] = 0;

        _compute2();
}

// remove element by element
void mgnss::state_estimation::OdometryV3::_compute3()
{

}

void mgnss::state_estimation::OdometryV3::_mad()
{

        mwoibn::VectorN distanceSotr, madV, madVSort;
        distanceSotr = _distance;

        //order
        std::sort(distanceSotr.data(), distanceSotr.data()+distanceSotr.size()); // sort vector

        double median, mad;
        int sum = _selector.count(); // number of meaningfull elements
        if(_selector.count()%2) // odd values
                median = distanceSotr[(int)sum/2];
        else // even
                median = distanceSotr[(int)sum/2 - 1] + distanceSotr[(int)sum/2];


        madV = mwoibn::VectorN::Zero(sum);

        for (int i = 0; i < sum; i++) {
                if (!_selector[i]) continue;
                madV[i] = std::fabs(distanceSotr[i] - median);
        }

        madVSort = madV;
        std::sort(madVSort.data(), madVSort.data()+madVSort.size()); // sort vector

        if(_selector.count()%2) // odd values
                mad = madVSort[(int)sum/2];
        else // even
                mad = madVSort[(int)sum/2 - 1] + madVSort[(int)sum/2];

        mad = 1.4826 * mad * 3;

        for (int i = 0; i < sum; i++) {
                if (madV[i] > mad) {
                        for (int j = 0; j < _selector.size(); j++) {
                                if (std::fabs(_distance[j] - distanceSotr[i]) < mwoibn::EPS) {
                                        _selector(j) = 0; // remove outliers
                                }
                        }
                }
        }

        _average();
}


void mgnss::state_estimation::OdometryV3::_average()
{
        _base.head(3).setZero();
        for (int i = 0; i < _selector.size(); i++)
        {
                if (_selector[i])
                        _base.head(3) += _pelvis[i];
        }

        _base.head(3).noalias() = _base.head(3) / _selector.count();
}


void mgnss::state_estimation::OdometryV3::_distances()
{

        for (int i = 0; i < _distance.size(); i++)
                _distance[i] = (_selector[i]) ? 0 : mwoibn::MAX_DOUBLE;

        for (int i = 0; i < _distance.size(); i++)
        {
                if (!_selector[i])
                        continue;
                for (int j = i; j < _distance.size(); j++)
                {
                        if (!_selector[j])
                                continue;
                        _distance[i] += (_pelvis[i] - _pelvis[j]).norm();
                        _distance[j] += (_pelvis[i] - _pelvis[j]).norm();
                }
        }
}



void mgnss::state_estimation::OdometryV3::log(mwoibn::common::Logger& logger, double time){

        logger.add("time", time);
//        
//        logger.add("heading", _twist_es.angle());
//        logger.add("raw", _twist_raw.angle());
//        logger.add("base", _robot.state.position.get()[3]);
//        logger.add("imu_e3", _temp_est[2]);
//        logger.add("imu_f3", _temp_fil[2]);
        logger.add("vx", _robot.command.velocity.get()[0]);
        logger.add("vy", _robot.command.velocity.get()[1]);
        logger.add("vz", _robot.command.velocity.get()[2]);
        logger.add("wx", _robot.command.velocity.get()[3]);
        logger.add("wy", _robot.command.velocity.get()[4]);
        logger.add("wz", _robot.command.velocity.get()[5]);
        
        logger.add("rvx", _raw[0]);
        logger.add("rvy", _raw[1]);
        logger.add("rvz", _raw[2]);
        logger.add("rwx", _raw[3]);
   
//        logger.add("imu_x", _imu.x());
//        logger.add("imu_y", _imu.y());
//        logger.add("imu_z", _imu.z());
//        logger.add("imu_w", _imu.w());
//        logger.add("l_imu_x", _last_imu.x());
//        logger.add("l_imu_y", _last_imu.y());
//        logger.add("l_imu_z", _last_imu.z());
//        logger.add("l_imu_w", _last_imu.w());

}



void mgnss::state_estimation::Twist::_average()
{
        double twist = 0;

        for (int i = 0; i < _selector.size(); i++)
        {
                if (_selector[i]){
                        twist += _estimates[i];
                      }
        }

        _estimate = twist / _selector.count();
}



void mgnss::state_estimation::Twist::update()
{
        int k = 0;
        // std::cout << _selector.transpose() << std::endl;
        // std::cout << "error "<< _error.transpose() << std::endl;
        for(int i = 0; i < _leg_selector.size(); i++) {
                if (!_leg_selector[i]) {
                      std::fill (_estimates.begin()+k, _estimates.end()-i-1,mwoibn::MAX_DOUBLE);   // myvector: 5 5 5 5 0 0 0 0
                        // _estimates.segment(k, _leg_selector.size()-i-1).setConstant(mwoibn::MAX_DOUBLE);
                        _selector.segment(k, _leg_selector.size()-i-1).setConstant(false);


                        k+=_leg_selector.size()-i-1;
                        continue;
                }
                //std::cout << "diff " << __es_2.transpose() << ", " << __st_2.transpose() << std::endl;
                // std::cout << "step "<< _step[i].transpose() << ", " << _contact_points[i].transpose() << std::endl;


                for(int j = i+1; j < _leg_selector.size(); j++) {
                        if(!_leg_selector[j]) {
                                _selector[k] = false;
                                _estimates[k] = mwoibn::MAX_DOUBLE;
                                k+=1;
                        }
                        else{
                                _selector[k] = true;
                                __es_2[0] = _base[i][0] - _base[j][0];
                                __es_2[1] = _base[i][1] - _base[j][1];
                                __st_2[0] = _contact_points[i][0] - _contact_points[j][0];
                                __st_2[1] = _contact_points[i][1] - _contact_points[j][1];
                                __st_2[0] -= _step[i][0] - _step[j][0];
                                __st_2[1] -= _step[i][1] - _step[j][1];

                                _estimates[k] = std::atan2(__st_2[0]*__es_2[1] - __st_2[1]*__es_2[0], __st_2[1]*__es_2[1] + __st_2[0]*__es_2[0]);
                                // std::cout << "i, " << i << " j " << j << std::endl;
                                // std::cout << "norm " << __es_2.norm() << std::endl;
                                // std::cout << "diff " << __es_2.transpose() << ", " << __st_2.transpose() << std::endl;
                                k+=1;
                        }
                }

        }
        _measure();
        // std::cout << "_selector " << _selector.transpose() << std::endl;

        _compute();

}




// compute MAD - remove and average
void mgnss::state_estimation::Twist::_measure()
{
        for (int i = 0; i < _measures.size(); i++)
                _measures[i] = (_selector[i]) ? 0 : mwoibn::MAX_DOUBLE;

        for (int i = 0; i < _measures.size(); i++)
        {
                if (!_selector[i])
                        continue;
                for (int j = i; j < _measures.size(); j++)
                {
                        if (!_selector[j])
                                continue;
                        double sum = std::fabs(_estimates[i] - _estimates[j]);
                        mwoibn::eigen_utils::wrapToPi(sum);
                        _measures[i] += sum;
                        _measures[j] += sum;
                }
        }
}


void mgnss::state_estimation::Velocity::_average()
{
        _estimate.setZero();

        for (int i = 0; i < _selector.size(); i++)
        {
          if (_selector[i])  _estimate += _estimates[i];
        }

        _estimate = _estimate / _selector.count();
}


// compute MAD - remove and average
void mgnss::state_estimation::Velocity::_measure()
{
          for (int i = 0; i < _measures.size(); i++)
                  _measures[i] = (_selector[i]) ? 0 : mwoibn::MAX_DOUBLE;

          for (int i = 0; i < _measures.size(); i++)
          {
                  if (!_selector[i])
                          continue;
                  for (int j = i; j < _measures.size(); j++)
                  {
                          if (!_selector[j])
                                  continue;
                          _measures[i] += (_estimates[i] - _estimates[j]).norm();
                          _measures[j] += (_estimates[i] - _estimates[j]).norm();
                  }
          }
}



void mgnss::state_estimation::Velocity::update()
{
  int k = 0;

  for(int i = 0; i < _leg_selector.size(); i++) {

          if (!_leg_selector[i]) {
                  _selector.segment(k, _leg_selector.size()-i-1).setConstant(false);

                  k+=_selector.size()-i-1;
                  continue;
          }

          for(int j = i+1; j < _leg_selector.size(); j++) {
                  if(!_leg_selector[j])
                          _selector[k] = false;
                  else
                          _selector[k] = true;
                  k+=1;
          }
  }



  for(int i = 0; i < _estimates.size(); i++) _update(i);

  _measure();
  _compute();

//  // std::cout << "vel_est\t" << _estimate.transpose() << std::endl;
}


void mgnss::state_estimation::Velocity::_update(int n)
{
  int m = n;
  // move m to one base operation
  ++m;
  // update base velocity based on the base twist estimation
  int i = 0, j, sum = 0;
    while (m > sum){
       i++;
       sum += _ids.size() - i;
    }
    // step back
    sum -= _ids.size() - i;
    --i;
    j = i - sum + m;


    // mwoibn::Matrix _base_jacobian(6, 4);
    // mwoibn::Matrix jacobian = _wheels_velocity[i].linear().getJacobian();
    _temp_jacobian = _wheels_velocity[i].linear().getJacobian();

    _base_jacobian.block<3,3>(0,0) = _temp_jacobian.leftCols<3>();
    _base_jacobian.block<3,1>(0,3).noalias() = _twist_es.toMatrix()*_temp_jacobian.col(5);

    _base_jacobian.block<3,3>(3,0) = _wheels_velocity[j].linear().getJacobian().leftCols<3>();
    _base_jacobian.block<3,1>(3,3).noalias() = _twist_es.toMatrix()*_wheels_velocity[j].linear().getJacobian().col(5);

    // mwoibn::VectorN x(6), y(6);
    mwoibn::Vector3 temp;

    _x.setZero();
    _y.setZero();
    _x.head<3>() = _twist_es.rotate( _wheels_velocity[i].linear().getWorld()); // wheel velocity assuming unknown values are 0

    _x.tail<3>() = _twist_es.rotate(_wheels_velocity[j].linear().getWorld()); // wheel velocity assuming unknown values are 0

    temp =  _twist_es.rotate(_wheels_velocity[i].angular().getWorld());
    _y.head<3>() = temp.cross(_ground_normal*_r);

    temp =  _twist_es.rotate(_wheels_velocity[j].angular().getWorld());
    _y.tail<3>() = temp.cross(_ground_normal*_r);

    _inverse->compute(_base_jacobian);

    _y -= _x;
    
//    std::cout << _estimates[m-1].size() << "\t" << m << "\n" << std::endl;
//    std::cout << _inverse->get()*_y << std::endl;
//
    _estimates[m-1].noalias() = _inverse->get()*_y;

//    if(std::isnan(_estimates[m-1][0])){
//        std::cout << "v\t " <<  << std::endl;
//        std::cout << "w\t " << _wheels_velocity[i].angular().getWorld() << std::endl;
//    }
//    // std::cout << "m\t" << m << "\tindices\t" << i << ", " << j << "\t" <<  _estimates[m-1].transpose() << std::endl;
}
