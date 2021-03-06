#include "mgnss/higher_level/steering_v2.h"


mgnss::higher_level::Steering2::Steering2(
        mwoibn::robot_class::Robot& robot,
        mwoibn::hierarchical_control::tasks::ContactPoint& plane,
        double K_icm, double K_sp, double dt,
        double margin, double max)
        : SteeringReference(robot, plane, K_icm, K_sp, dt, margin, max), _margin(margin)
{
        _temp.setZero(_size);

        _computeTreshhold();
}

void mgnss::higher_level::Steering2::_computeTreshhold(){

        double l = _margin / _dt;
        _treshhold = std::pow(l, _pow);
}


void mgnss::higher_level::Steering2::_merge(int i){

        double vel = _computeVelocity(i);
        SteeringReference::_merge(i);

        limit(_b_st[i] - _heading, _b[i]);

        if (vel < (_margin / _dt))
        {
                _temp[i] = _b[i] - (_b_st[i] - _heading);
                _b[i] = _b_st[i] - _heading;
                _b[i] += std::pow(vel,_pow) / _treshhold * _temp[i];
        }

        _b_st[i] = _b[i] + _heading; // do give the result in the world frame
}

void mgnss::higher_level::Steering2::_ICM(mwoibn::Vector3 next_step)
{

        for (int i = 0; i < _size; i++)
        {
                _steerICM(i, next_step);
                _velICM(i);
        }
}

void mgnss::higher_level::Steering2::_PT(int i)
{
        // Desired state

        _plane_ref.noalias() = _plane.getReferenceError(i).head(2); // size 2

        _steerSP(i);
        _velSP(i);

}
