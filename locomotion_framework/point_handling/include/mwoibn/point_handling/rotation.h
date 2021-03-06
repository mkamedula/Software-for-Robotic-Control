#ifndef __MWOIBN__POINT_HANDLING__ROTATION_H
#define __MWOIBN__POINT_HANDLING__ROTATION_H

#include "mwoibn/point_handling/base.h"

namespace mwoibn
{

namespace point_handling
{

class Rotation: public Base<mwoibn::Matrix3>
{

public:
  //typedef mwoibn::Quaternion Angular;
  typedef mwoibn::Matrix3 R;

  template<typename Body>
  Rotation(Body body_id, RigidBodyDynamics::Model& model,
       const mwoibn::robot_class::State& state, std::string name = "")
      : Base(body_id, model, state, 9, name)
  { _current_fixed.setIdentity();
    _temp_world.setIdentity();}

  template<typename Body>
  Rotation(const Rotation::R& current, Body body_id,
        RigidBodyDynamics::Model& model, const mwoibn::robot_class::State& state,
        std::string name = "")
      : Base(current, body_id, model, state, 9, name)
  { }

  template<typename Other>
  Rotation( Other&& other)
      : Base(other, 9)
  {
    _current_fixed.setIdentity();
      _temp_world.setIdentity();
  }


  template<typename Other>
  Rotation(const Other& other)
      : Base(other, 9)
  {
    _current_fixed.setIdentity();
      _temp_world.setIdentity();
  }

  Rotation( Rotation&& other)
      : Base(other)
  {  }

  Rotation(const Rotation& other)
      : Base(other)
  {  }

  virtual ~Rotation() {}

  virtual Rotation* clone_impl() const {return new Rotation(*this);}

  /** @brief get Position in a world frame */
  virtual const Rotation::R&
  getWorld(bool update = false);

  virtual void
  getWorld(Rotation::R& rotation, bool update = false) const;

  virtual Rotation::R
  getWorld(bool update = false) const;

  /** @brief set new tracked point giving data in a world frame*/
  virtual void setWorld(const Rotation::R& current,
                        bool update = false);

  virtual void setFixed(const Rotation::R& current){ _current_fixed.noalias() = current; }

  /** @brief get Position in a user-defined reference frame */
  // virtual Rotation::R
  // getReference(unsigned int refernce_id, bool update = false) const;

  virtual void setReference(const Rotation::R& current,
                            unsigned int reference_id,
                            bool update = false);

  using Base::getReference;
  using Base::setReference;

};

} // namespace package
} // namespace library

#endif
