#ifndef __MWOIBN_HIERARCHICAL_CONTROL_TASKS_CONTACT_POINT_3D_RBDL_TASK_H
#define __MWOIBN_HIERARCHICAL_CONTROL_TASKS_CONTACT_POINT_3D_RBDL_TASK_H

#include "mwoibn/hierarchical_control/tasks/contact_point_tracking_task.h"
#include "mwoibn/robot_points/point.h"
#include "mwoibn/robot_points/ground_wheel.h"
#include "mwoibn/robot_points/torus_model.h"



namespace mwoibn
{
namespace hierarchical_control
{
namespace tasks
{

/**
 * @brief The CartesianWorld class Provides the inverse kinematics task
 *to control the position of a point defined in one of a robot reference frames
 *
 */

class ContactPoint3DRbdl : public ContactPointTracking
{

public:
  /**
   * @param[in] ik the point handler mamber that defines which point is
   *controlled by this task instance it makes a local copy of a point handler to
   *prevent outside user from modifying a controlled point
   *
   */
  ContactPoint3DRbdl(const std::string& group, mwoibn::robot_class::Robot& robot, YAML::Node config,
                          mwoibn::robot_points::Point& base_point, std::string base_link)
      : ContactPointTracking(robot, base_point, base_link)
  {

    for(auto& contact: _robot.contacts().group(group))
    {
        std::string name = _robot.getBodyName(contact->wrench().getBodyId());
        // if(!std::count(names.begin(), names.end(), name)){
        //   std::cout << "Tracked point " << name << " could not be initialized" << std::endl;
        //   names.erase(std::remove(names.begin(), names.end(), name), names.end());
        //   continue;
        // }

        std::unique_ptr<mwoibn::robot_points::TorusModel> torus_(new mwoibn::robot_points::TorusModel(
                           _robot.getModel(), _robot.state, mwoibn::point_handling::FramePlus(name,
                           _robot.getModel(), _robot.state),
                           mwoibn::Axis(config["reference_axis"][name]["x"].as<double>(),
                                        config["reference_axis"][name]["y"].as<double>(),
                                        config["reference_axis"][name]["z"].as<double>()),
                                        config["minor_axis"].as<double>(), config["major_axis"].as<double>(),
                                        contact->getGroundNormal()));

        _wheel_transforms.push_back(std::unique_ptr<mwoibn::robot_points::Rotation>(
                  new mwoibn::robot_points::GroundWheel(torus_->axis(), torus_->groundNormal())));
        _contacts.add(std::move(torus_));

    }

        _allocate();
        _temp_jacobian.setZero(3, _robot.getDofs());
        reset();

  }

  virtual ~ContactPoint3DRbdl() {}



protected:
  virtual void _updateError()
  {
    _base_point.update(true);
    // std::cout << "_updateError" << std::endl;
    _last_error.noalias() = _error; // save previous state

    // std::cout << "_reference\t" << _reference.transpose() << std::endl;
    // std::cout << "_q_twist\t" << _q_twist << std::endl;
    for (int i = 0; i < _contacts.size(); i++)
    {

      _full_error.segment<3>(3*i) = _q_twist.rotate(_reference.segment<3>(i*3)) - _minus[i].get();
      // _error.segment<3>(3*i) = (_wheel_transforms[i]->rotation.transpose()*_full_error.segment<3>(3*i)); // 10 is for a task gain should be automatic
      mwoibn::Vector3 test__;
      test__.noalias() = (_wheel_transforms[i]->rotation.transpose()*_full_error.segment<3>(3*i));
      _error[i] = test__[0];
      test__.noalias() = (_wheel_transforms[i]->rotation.transpose()*_velocity_reference.segment<3>(3*i));
      _velocity[i] = test__[0];

      // std::cout << "_minus\t" << _minus[i].get().transpose() << std::endl;

      // if (_selector[i])
        // _error.segment<2>(3*i+1).setZero();
        // std::cout << "test__\t" << test__.transpose() << std::endl;

      _force.segment<3>(3*i).noalias() =  _wheel_transforms[i]->rotation.transpose()*(_robot.contacts()[i].wrench().force.getWorld());
    }

    //std::cout << "get\n" << _base_point.get() << std::endl;
  }


  virtual void _updateJacobian()
  {

    _last_jacobian.noalias() = _jacobian;

    for (int i = 0; i < _contacts.size(); i++)
    {
      // _jacobian.block(3*i, 0, 3, _jacobian.cols()).noalias() = -_wheel_transforms[i]->rotation.transpose()*(_minus[i].getJacobian());
      _temp_jacobian.noalias() = -_wheel_transforms[i]->rotation.transpose()*(_minus[i].getJacobian());
      _projected.noalias() = _ground_normal*_ground_normal.transpose();
      mwoibn::eigen_utils::skew(_q_twist.rotate(_reference.segment<3>(i*3)), _rot);
      _rot_project.noalias() = _rot*_projected;
      _rot.noalias() = _wheel_transforms[i]->rotation.transpose()*_rot_project;
      //_jacobian.block(3*i, 0, 3, _jacobian.cols()).noalias() -= _rot*_base_ang_vel.getJacobian();

      _jacobian.row(i) = _temp_jacobian.row(0);
      _jacobian.row(i) -= (_rot*_base_ang_vel.getJacobian()).row(0); // here I have only a 1D task
      //_jacobian.row(i) = (_temp_jacobian - _rot*_base_ang_vel.getJacobian()).row(0);
      // if (_selector[i])
        // _jacobian.block(3*i+1, 0, 2, _jacobian.cols()).setZero();
    }

    // std::cout << "_jacobian\n" << _jacobian.transpose() << std::endl;
  }

protected:
  mwoibn::Matrix _temp_jacobian;

};
}
} // namespace package
} // namespace library
#endif
