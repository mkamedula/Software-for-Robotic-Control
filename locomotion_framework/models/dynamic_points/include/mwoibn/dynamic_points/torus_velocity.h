#ifndef __MWOIBN__DYNAMIC_POINTS__TORUS_VELOCITY_H
#define __MWOIBN__DYNAMIC_POINTS__TORUS_VELOCITY_H

#include "mwoibn/dynamic_points/torus.h"


namespace mwoibn
{

namespace dynamic_points
{

  // Esitmates a torus velocity from acceleration
class TorusVelocity: public Torus
{

public:


  TorusVelocity(robot_points::TorusModel& torus, mwoibn::robot_class::Robot& robot):
    Torus(torus, robot){
          _init();
  }

  TorusVelocity( TorusVelocity&& other)
      : Torus(other)
  {
    _init();
  }

  TorusVelocity(const TorusVelocity& other)
      : Torus(other)
  {
    _init();
  }

  using Point::operator=;

    virtual void compute();
    virtual void computeJacobian();

    mwoibn::Vector3 _support_offset;
    mwoibn::Matrix3 _support_jacobian;

  // protected:
  //   mwoibn::robot_class::Robot& _robot;

};

} // namespace package
} // namespace library

#endif
