#include "mwoibn/dynamic_points/linear_force.h"

namespace mwoibn
{
namespace dynamic_points
{

  void LinearForce::computeJacobian(){
    _point_jacobian = _velocity.getJacobian();
    _point_transposed = _point_jacobian.transpose();

    _point_inverse.noalias() = _point_jacobian*_dynamic_model.getInertiaInverse();
    _point_temp.noalias() = _point_inverse*_point_transposed;

    _contacts_inverse->compute(_point_temp);

    _jacobian = _contacts_inverse->get();

  }

  void LinearForce::compute(){
    computeJacobian();

    _point.noalias() = _jacobian*_des_acc; //?

  }


} // namespace package
} // namespace library
