#ifndef __MGNSS_CONTROLLERS_WHEELS_CONTROLLER_H
#define __MGNSS_CONTROLLERS_WHEELS_CONTROLLER_H

#include <mgnss/modules/base.h>

#include <mwoibn/hierarchical_control/hierarchical_controller.h>
#include <mwoibn/hierarchical_control/constraints_task.h>

#include <mwoibn/hierarchical_control/contact_point_tracking_task.h>
#include <mgnss/controllers/steering_reference.h>

#include <mwoibn/hierarchical_control/cartesian_selective_task.h>
#include <mwoibn/hierarchical_control/orientation_selective_task.h>

namespace mgnss
{

namespace controllers {

class WheelsController: public mgnss::modules::Base
{

public:
  WheelsController(mwoibn::robot_class::Robot& robot);

  ~WheelsController() {}

  virtual void init() { _setInitialConditions(); }

  virtual void startLog(mwoibn::common::Logger& logger){}
  virtual void log(mwoibn::common::Logger& logger, double time){}

  virtual void stop(){
      _command.setZero();
      _robot.command.set(_command, mwoibn::robot_class::INTERFACE::VELOCITY);
      _robot.send();
  }

  virtual void send(){
    _robot.send();
  } // NOT IMPLEMENTED

  virtual void close(){} // NOT IMPLEMENTED
  virtual void setRate(double rate){
   mgnss::modules::Base::setRate(rate);
    setRate();

  }

  virtual void update(){
    nextStep();
    compute();
  }

  virtual void setRate(){ _dt = _robot.rate(); _steering_ref_ptr->setRate(_dt);}

  virtual void resetSteering() = 0;

  virtual void setSteering(int i, double th) = 0;

  void rotateBaseX(double th)
  {
    _orientation = mwoibn::Quaternion::fromAxisAngle(_x, th) * _orientation;
  }

  void rotateBaseY(double th)
  {
    _orientation = mwoibn::Quaternion::fromAxisAngle(_y, th) * _orientation;
  }

  virtual void setBaseRotVelX(double dth) { _angular_vel[0] = dth; }
  virtual void setBaseRotVelY(double dth) { _angular_vel[1] = dth; }

  void setBaseX(double x){
    _position[0] = x;
  }
  void setBaseY(double y){
    _position[1] = y;
  }
  void setBaseZ(double z){
    _position[2] = z;
  }

  virtual void setBaseHeading(double th) { _heading = th; }

  virtual void setBaseDotX(double dx) { _linear_vel[0] = dx; }
  virtual void setBaseDotY(double dy) { _linear_vel[1] = dy; }
  virtual void setBaseDotZ(double dz) { _linear_vel[2] = dz; }
  virtual void setBaseDotHeading(double th) { _angular_vel[2] = th; }

  mwoibn::VectorN getSteering() { return steerings; }

  virtual const mwoibn::Vector3& getCp(int i){ return _steering_ptr->getPointStateReference(i);}
  virtual mwoibn::VectorN errorCp(int i){ return _steering_ptr->getReferenceError(i);}
  virtual const mwoibn::VectorN& refCp(){ return _steering_ptr->getReference();}

  virtual const mwoibn::VectorN& refSteer(){ return steerings;}

  virtual const mwoibn::Vector3& getLinVel(){ return _linear_vel;}
  virtual const mwoibn::Vector3& getAngVel(){ return _angular_vel;}

  virtual void updateSupport(const mwoibn::VectorN& support)
  {
    _steering_ptr->setReference(support);
  }

  virtual double getBaseGroundX() = 0;
  virtual double getBaseGroundY() = 0;
  virtual double getBaseGroundZ() = 0;
  virtual double getBaseGroundRz() = 0;


  virtual void updateBase() = 0;

  virtual void stepBase();

  virtual void steering();

  virtual void compute();

  virtual double limit(const double th);

  virtual bool isRunning() { return _robot.isRunning(); }

  virtual bool isDonePosition(const double eps)
  {
    return _isDone(*_pelvis_position_ptr, eps);
  }
  virtual bool isDoneOrientation(const double eps)
  {
    return _isDone(*_pelvis_orientation_ptr, eps);
  }
  virtual bool isDoneSteering(const double eps) const = 0;
//  {
//    return _isDone(*_leg_steer_ptr, eps);
//  }
  virtual bool isDonePlanar(const double eps) const = 0;
//  {
//    return _isDone(*_steering_ptr, eps);
//  }
  virtual bool isDoneWheels(const double eps) const = 0;
//  {
//    return _isDone(*_leg_castor_ptr, eps);
//  }

  const mwoibn::VectorN& getSupportReference()
  {
    return _steering_ptr->getReference();
  }
  const mwoibn::VectorN& getBodyPosition()
  {
    return _pelvis_position_ptr->getReference();
  }

  virtual void nextStep();

  virtual void update(const mwoibn::VectorN& support);

protected:
  bool _isDone(mwoibn::hierarchical_control::ControllerTask& task,
               const double eps) const
  {
    return task.getError().cwiseAbs().maxCoeff() < eps;
  }

  std::unique_ptr<mwoibn::hierarchical_control::ConstraintsTask>
      _constraints_ptr;

  std::unique_ptr<mwoibn::hierarchical_control::CartesianSelectiveTask>
      _pelvis_position_ptr;
  std::unique_ptr<mwoibn::hierarchical_control::OrientationSelectiveTask>
      _pelvis_orientation_ptr;

  std::unique_ptr<mwoibn::hierarchical_control::ContactPointTrackingTask>
      _steering_ptr;

  std::unique_ptr<mgnss::events::SteeringReference> _steering_ref_ptr;

  mwoibn::hierarchical_control::HierarchicalController _hierarchical_controller;

  double rate = 200;
  double _dt, orientation = 0, _heading;
  mwoibn::VectorN steerings, _command, _previous_command;
  mwoibn::Vector3 _position, _next_step, _angular_vel, _linear_vel;
  mwoibn::Axis _x, _y, _z;

  mwoibn::Quaternion _orientation;
  bool _reference = false;
  mwoibn::VectorInt _select_steer;
  mwoibn::VectorN _l_limits, _u_limits;
  int count = 0;

  virtual void _setInitialConditions() = 0;
  virtual void _allocate();

};
}
}
#endif // WHEELED_MOTION_H