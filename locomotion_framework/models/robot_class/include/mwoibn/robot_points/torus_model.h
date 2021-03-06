#ifndef __MWOIBN__ROBOT_CLASS__TORUS_MODEL_H
#define __MWOIBN__ROBOT_CLASS__TORUS_MODEL_H

#include "mwoibn/robot_points/state.h"
#include "mwoibn/point_handling/frame_plus.h"
#include "mwoibn/point_handling/wrench.h"
#include "mwoibn/point_handling/spatial_velocity.h"
// #include "mwoibn/robot_class/robot.h"


namespace mwoibn
{

  namespace dynamic_points{
    class Torus;
    class Torus2;
    class TorusRoll;
    class TorusIntegratedRoll;
    class TorusVelocity;
  }

namespace robot_points
{

class TorusModel: public State
{



public:
  TorusModel(RigidBodyDynamics::Model& model, const mwoibn::robot_class::State& state, mwoibn::point_handling::FramePlus& centre,
             mwoibn::Axis axis, double r, double R, const mwoibn::Vector3& ground_normal);

  // TorusModel(mwoibn::robot_class::Robot& robot, mwoibn::point_handling::FramePlus centre,
  //            mwoibn::Axis axis, double r, double R, const mwoibn::Vector3& ground_normal);

  TorusModel(RigidBodyDynamics::Model& model, const mwoibn::robot_class::State& state, mwoibn::point_handling::FramePlus centre,
                        mwoibn::Axis axis, double r, double R, const mwoibn::Vector3& ground_normal);


  TorusModel(TorusModel&& other);

  TorusModel(const TorusModel& other);

  friend class dynamic_points::Torus;
  friend class dynamic_points::Torus2;
  friend class dynamic_points::TorusRoll;
  friend class dynamic_points::TorusIntegratedRoll;
  friend class dynamic_points::TorusVelocity;

  virtual ~TorusModel() {}


  using Point::operator=;

  void compute();

  void computeJacobian();

  const mwoibn::Vector3& groundNormal() const {return _ground_normal;}
  const mwoibn::Vector3& axis() const {return _axis_world;}

  const mwoibn::Matrix3& frame();
  mwoibn::point_handling::SpatialVelocity& wheelVelocity(){return _v_centre;}
  const mwoibn::Vector3& wheelAngularVelocity(){return _angular_world;}
  const mwoibn::Matrix3& getJacobianWheel(){return _wheel_jacobian;}
  const mwoibn::Vector3& positionOffset();

protected:  // should I add wrench here and attach the feedback to this? could be easier
  mwoibn::point_handling::FramePlus _centre;

  // mwoibn::point_handling::FramePlus _contact_point;
  // mwoibn::point_handling::Wrench _wrench; // I need another frame here

  mwoibn::Matrix3 _frame;
  mwoibn::point_handling::SpatialVelocity _v_centre;
  mwoibn::Vector3 _angular_world;
  const mwoibn::Vector3& _ground_normal;
  mwoibn::Axis _axis, _axis_world;

  mwoibn::Matrix3 _contact_1, _contact_2, _contact_3, _wheel_jacobian;
  mwoibn::Matrix  _contact_j, _contact_k;
  mwoibn::Vector3 _temp, _position_offset;
  double _r, _R;

  const mwoibn::Matrix& _jacobianOffset();


};

} // namespace package
} // namespace library

#endif // CENTER_OF_MASS_H
