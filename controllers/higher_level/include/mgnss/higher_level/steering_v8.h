#ifndef __MGNSS_HIGHER_LEVEL_STEERING_V8_H
#define __MGNSS_HIGHER_LEVEL_STEERING_V8_H

#include "mgnss/higher_level/steering_reference.h"

namespace mgnss
{

namespace higher_level
{

/*
 *  Steering version with contact point open-loop reference
 *
 */
class Steering8 : public SteeringReference
{

public:
Steering8(mwoibn::robot_class::Robot& robot,
          mwoibn::hierarchical_control::tasks::ContactPointTracking& plane, const mwoibn::VectorN& contact_vel,
          mwoibn::VectorN init_pose, double K_icm, double K_sp, double K_v, double dt,
          double margin_icm, double margin_sp, double margin = 0.04, double max = 2.79252680);

virtual ~Steering8() {
}

protected:

virtual void _merge(int i);
mwoibn::VectorN _pb_icm, _pb_sp, _pb;
double _K_v, _treshhold_icm, _treshhold_sp;
virtual void _ICM(mwoibn::Vector3 next_step);
const mwoibn::VectorN& _contact_vel;

virtual void _PT(int i);

virtual void _velSP(int i);

virtual void _computeTreshhold();
virtual void _resetTreshhold();
virtual void _steerICM(int i, const mwoibn::Vector3 next_step);

virtual double _computeVelocity(int i){
        return std::sqrt(_K_icm*_v_icm[i]*_K_icm*_v_icm[i] + _K_sp*_v_sp[i]*_K_sp*_v_sp[i] + 2*_K_sp*_v_sp[i]*_K_icm*_v_icm[i]*std::cos(_b_icm[i] - _b_sp[i]));
}

};
}
}
#endif // PROGRAM_STEERING_H
