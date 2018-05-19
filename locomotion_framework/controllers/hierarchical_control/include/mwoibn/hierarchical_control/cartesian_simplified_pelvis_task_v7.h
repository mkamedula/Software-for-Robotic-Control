#ifndef HIERARCHICAL_CONTROL_CATRESIAN_SIMPLIFIED_PELVIS_TASK_7_H
#define HIERARCHICAL_CONTROL_CATRESIAN_SIMPLIFIED_PELVIS_TASK_7_H

#include "mwoibn/hierarchical_control/contact_point_3D_rbdl_task.h"
#include "mwoibn/hierarchical_control/center_of_mass_task.h"

namespace mwoibn
{
namespace hierarchical_control
{

/**
 * @brief The CartesianWorldTask class Provides the inverse kinematics task
 *to control the position of a point defined in one of a robot reference frames
 *
 */
class CartesianFlatReferenceTask4 : public ContactPoint3DRbdlTask
{

public:
  /**
   * @param[in] ik the point handler mamber that defines which point is
   *controlled by this task instance it makes a local copy of a point handler to
   *prevent outside user from modifying a controlled point
   *
   */
  CartesianFlatReferenceTask4(point_handling::PositionsHandler ik,
                              mwoibn::robot_class::Robot& robot, mwoibn::hierarchical_control::CenterOfMassTask& com)
      : ContactPoint3DRbdlTask(ik, robot), _com(com)
  {
    init();
  }

  virtual ~CartesianFlatReferenceTask4() {}

  mwoibn::Vector3 computeContact(int i){
    double norm = 1/(_ground_normal - _axes_world[i]*_ground_normal.transpose()*_axes_world[i]).norm();
    mwoibn::Vector3 contact = -(_ground_normal - _axes_world[i]*_ground_normal.transpose()*_axes_world[i])*norm*R;
    contact -= (_ground_normal)*r;
    return contact;
  }

  mwoibn::Matrix computeContactJacobian(int i){
    double norm = 1/(_ground_normal - _axes_world[i]*_ground_normal.transpose()*_axes_world[i]).norm();

    mwoibn::Vector3 vector = _axes_world[i]*_ground_normal.transpose()*_axes_world[i];
    mwoibn::Matrix3 contact_j, contact_temp;
    mwoibn::eigen_utils::skew(vector, contact_j);
    mwoibn::eigen_utils::skew(_axes_world[i], contact_temp);

    contact_j += (_axes_world[i]*_ground_normal.transpose()*contact_temp);

    mwoibn::Matrix3 contact_2 = 0.5*norm*norm*_ground_normal*_ground_normal.transpose();
    contact_2 -= mwoibn::Matrix3::Identity();
    contact_2 -= 0.5*norm*norm*_axes_world[i]*_axes_world[i].transpose()*_ground_normal*_ground_normal.transpose();

    mwoibn::Matrix contact;
    contact = contact_2*contact_j*_wheels_ptr->point(i).getOrientationJacobian(_robot.state.get(mwoibn::robot_class::INTERFACE::POSITION))*R*norm;

    return contact;
  }

  virtual void updateState(){

    ContactPoint3DRbdlTask::updateState();

    q_twist = _pelvis_ptr->point(0).getOrientationWorld(_robot.state.get(mwoibn::robot_class::INTERFACE::POSITION));
    q_twist = q_twist.twistSwing(_ground_normal);
    angle_twist = q_twist.toAxisAngle(axis_twist);

  }

  double getTwist() const {return angle_twist;}

  virtual mwoibn::Vector3 twistTransform(const mwoibn::Vector3& vec) const {
    return q_twist.rotate(vec);
  }

  virtual mwoibn::Vector3 twistReference(int i){

    mwoibn::Vector3 reference;
    reference = _reference.segment(i * 3, 3);

    reference = q_twist.rotate(reference);

    //std::cout << "twist\n" << q_twist.toMatrix()<< std::endl;
    //std::cout << "state\n" << _getTransform() << std::endl;
    //reference.head<2>() += _robot.centerOfMass().get().head<2>();

    return reference;
  }

protected:
  mwoibn::hierarchical_control::CenterOfMassTask& _com;
  mwoibn::Quaternion q_twist;
  double angle_twist;
  mwoibn::Vector3 axis_twist;

  double R = 0.01, r = 0.068;

  virtual mwoibn::Vector3 _contactPoint(int i)
  {
    return _ik.getPointStateWorld(i) + computeContact(i);
  }

  virtual const mwoibn::Matrix& _referenceJacobian(int i)
  {
    _temp_jacobian.setZero();
    _temp_jacobian.topRows<2>().noalias() = -_com.getJacobian();

    _temp_jacobian(0, 2) -= (std::sin(_state[2]) * _reference[3 * i] +
                             std::cos(_state[2]) * _reference[3 * i + 1]);
    _temp_jacobian(1, 2) += (std::cos(_state[2]) * _reference[3 * i] -
                             std::sin(_state[2]) * _reference[3 * i + 1]);
    return _temp_jacobian;
  } // ?

  virtual const mwoibn::Matrix& _contactJacobian(int i)
  {
    _temp_jacobian.noalias() = _ik.getFullPointJacobian(i);
    _temp_jacobian.noalias() += computeContactJacobian(i);

    return _temp_jacobian;
  }


  virtual mwoibn::Vector3 _worldToBase(mwoibn::Vector3 point)
  {

    mwoibn::Vector3 basePoint;
    basePoint.noalias() = point;
    basePoint.head<2>() -= _robot.centerOfMass().get().head<2>();

    return _getTransform().transpose() * basePoint;
  }

  virtual mwoibn::Vector3 _baseToWorld(mwoibn::Vector3 point)
  {

    mwoibn::Vector3 basePoint;
    basePoint.noalias() = _getTransform() * point;
    basePoint.head<2>() += _robot.centerOfMass().get().head<2>();

    return basePoint;
  }

  virtual void _updateTransform()
  {
    _transform << std::cos(_state[2]), -std::sin(_state[2]), 0,
        std::sin(_state[2]), std::cos(_state[2]), 0, 0, 0,
        1;
  }


};
} // namespace package
} // namespace library
#endif
