#ifndef __MWOIBN__POINT_HANDLING__FRAME_PLUS_H
#define __MWOIBN__POINT_HANDLING__FRAME_PLUS_H

#include "mwoibn/point_handling/temp_base.h"
#include "mwoibn/point_handling/position.h"
#include "mwoibn/point_handling/rotation.h"
#include "mwoibn/point_handling/orientation.h"


namespace mwoibn
{

namespace point_handling
{

class FramePlus: public TempBase<mwoibn::Vector7>
{

public:

  template<typename Body>
  FramePlus(Body body_id, RigidBodyDynamics::Model& model, const mwoibn::robot_class::State& state,
        std::string name = "")
      : TempBase(body_id, model, state, 7, name), position(body_id, model, state, name), orientation(body_id, model, state, name)
  {   }

  template<typename Type>
  FramePlus(Point::Current linear, Type body_id,
        RigidBodyDynamics::Model& model, const mwoibn::robot_class::State& state,
        Orientation::O quat = Orientation::O(),  std::string name = "")
      : TempBase(body_id, model, state, 7, name), position(body_id, model, state, name), orientation(body_id, model, state, name)
  {
    position.setFixed(linear);
    orientation.setFixed(quat);
  }

  FramePlus(const FramePlus&& other)
      : TempBase(other), orientation(other.orientation), position(other.position)
  {  }

  FramePlus(const FramePlus& other)
      : TempBase(other), orientation(other.orientation), position(other.position)
  {  }

  virtual ~FramePlus() {}


  point_handling::Rotation& rotation(){return orientation.rotation();};

  point_handling::Position position;
  point_handling::Orientation orientation;

};

} // namespace package
} // namespace library

#endif
