#ifndef HIERARCHICAL_CONTROL_CATRESIAN_POSITION_TASK_H
#define HIERARCHICAL_CONTROL_CATRESIAN_POSITION_TASK_H

#include "mwoibn/hierarchical_control/hierarchical_control.h"
#include "mwoibn/hierarchical_control/controller_task.h"
#include <rbdl/rbdl.h>
//#include "point_handling/points_handler.h"
#include "mwoibn/point_handling/robot_points_handler.h"

namespace mwoibn
{
namespace hierarchical_control
{

/**
 * @brief The CartesianWorldTask class Provides the inverse kinematics task
 *to control the position of a point defined in one of a robot reference frames
 *
 */
class CartesianWorldTask : public ControllerTask
{

public:
  /**
   * @param[in] ik the point handler mamber that defines which point is
   *controlled by this task instance it makes a local copy of a point handler to
   *prevent outside user from modifying a controlled point
   *
   */
  CartesianWorldTask(point_handling::PositionsHandler ik)
      : ControllerTask(), _ik(ik)
  {
    _init(_ik.getFullJacobianRows(), _ik.getFullJacobianCols());
    _reference = _ik.getFullStateWorld();
  }

  virtual ~CartesianWorldTask() {}

  //! updates task error based on the current state of the robot and task
  // reference position
  virtual void updateError();
  //! updates task Jacobian based on the current state of the robot
  virtual void updateJacobian();
  //! sets task reference
  virtual void setReference(const mwoibn::VectorN& reference)
  {
    for (int i = 0; i < _reference.size(); i++)
      _reference[i] = reference[i];
  }
  //! sets task reference
  virtual void setReference(int i, const mwoibn::Vector3& reference)
  {
    _reference.segment<3>(i * 3) = reference;
  }
  //! sets current state as a desired reference
  virtual void resetReference() { _reference.noalias() = _ik.getFullStateWorld(); }
  //! returnes task reference
  virtual const mwoibn::VectorN& getReference() const { return _reference; }
  const point_handling::PositionsHandler& points() { return _ik; }
  //! sets task reference
  virtual mwoibn::VectorN getReference(int i) const
  {
    return _reference.segment<3>(i * 3);
  }

protected:
  //!point handler mamber for point controlled by this task instance
  point_handling::PositionsHandler _ik;
  //! task reference position of a controlled point expressed in a world frame
  mwoibn::VectorN _reference;
};
} // namespace package
} // namespace library
#endif
