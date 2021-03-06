#include "mgnss/higher_level/steering_v7.h"

mgnss::higher_level::Steering7::Steering7(
        mwoibn::robot_class::Robot& robot,
        mwoibn::hierarchical_control::tasks::ContactPoint& plane,
        double K_icm, double K_sp, double K_v, double dt,
        double margin_icm, double margin_sp, double margin, double max)
        : SteeringReference(robot, plane, K_icm, K_sp, dt, margin, max), _K_v(K_v)
{
        _pb_icm.setZero(_size);
        _pb_sp.setZero(_size);
        _pb.setZero(_size);

        _damp_sp.setZero(_size);
        _damp_icm.setZero(_size);

        _treshhold_icm = margin_icm/dt;
        _treshhold_sp = margin_sp/dt;

}

void mgnss::higher_level::Steering7::_resetTreshhold(){
        _treshhold = _treshhold*_dt;

        _treshhold_icm = _treshhold_icm*_dt;
        _treshhold_sp = _treshhold_sp*_dt;
}

void mgnss::higher_level::Steering7::_computeTreshhold(){
        _treshhold = _treshhold/_dt;

        _treshhold_icm = _treshhold_icm/_dt;
        _treshhold_sp = _treshhold_sp/_dt;
//  std::cout << _treshhold << "\t" << _treshhold_icm << "\t" << _treshhold_sp << std::endl;
}


void mgnss::higher_level::Steering7::_merge(int i){
        if(_resteer[i]) {
                _b[i] -= mwoibn::PI;
                mwoibn::eigen_utils::wrapToPi(_b[i]);
        } // change velocity sign

        _pb[i] = _b[i];

        _v[i] = _computeVelocity(i);
        _damp[i] = std::tanh(std::fabs(_v[i]*_v_icm[i]) /_treshhold/ _treshhold_icm);


        _b[i] = std::atan2(  _K_icm * std::fabs(_v_icm[i]) * _v_icm[i]  * std::sin(_b_icm[i]) +
                             _K_sp  * std::fabs(_v_icm[i]) * _v_sp[i]   * std::sin(_b_sp[i]),
                             _K_icm * std::fabs(_v_icm[i]) * _v_icm[i]  * std::cos(_b_icm[i]) +
                             _K_sp  * std::fabs(_v_icm[i]) * _v_sp[i]   * std::cos(_b_sp[i]));


        _raw[i] = _b[i];
        _limited[i] = _b[i];

        limit2PI(_pb[i], _limited[i]);

        _b[i] = _pb[i] + _damp[i] * (_limited[i] - _pb[i]); // do give the result in the world frame

        _b_st[i] = _b[i] + _heading;
}




void mgnss::higher_level::Steering7::_ICM(mwoibn::Vector3 next_step)
{

        _pb_icm.noalias() = _b_icm;

        for (int i = 0; i < _size; i++)
        {
                double v_last = _v_icm[i];

                _steerICM(i, next_step);
                _velICM(i);

                int factor = mwoibn::eigen_utils::limitHalfPi(_pb_icm[i],_b_icm[i]);
                factor = limit2PI(_pb_icm[i], _b_icm[i], factor);

                _v_icm[i] = std::pow(-1,factor)*_v_icm[i]; // change sign to fit with steering

                _damp_icm[i] = std::tanh(std::fabs(_v_icm[i])/_treshhold_icm);

                _b_icm[i] = _pb_icm[i] + _damp_icm[i] * (_b_icm[i] - _pb_icm[i]);
                _v_icm[i] = v_last + _damp_icm[i] * (_v_icm[i] - v_last);

                factor = mwoibn::eigen_utils::limitHalfPi(_b[i],_b_icm[i]);
                factor = limit2PI_v(_b[i], _b_icm[i], factor);
                _v_icm[i] = std::pow(-1,factor)*_v_icm[i]; // change sign to fit with steering

        }
}

void mgnss::higher_level::Steering7::_velSP(int i){
        _v_sp[i] = _K_v*_plane_ref.norm();
}

void mgnss::higher_level::Steering7::_PT(int i)
{
        // Desired state

        _pb_sp[i] = _b_sp[i];
        double v_last = _v_sp[i];

        _plane_ref.noalias() = _plane.getReferenceError(i).head(2); // size 2

        _steerSP(i);
        _velSP(i);

        //_v_sp[i] = _v_icm[i]*_v_sp[i];

        int factor = mwoibn::eigen_utils::limitHalfPi(_pb_sp[i],_b_sp[i]);
        factor = limit2PI(_pb_sp[i], _b_sp[i], factor);

        //limit2PI(_b_sp[i], _pb_sp[i]);
        _v_sp[i] = std::pow(-1,factor)*_v_sp[i]; // change sign to fit with steering

        _damp_sp[i] = std::tanh(std::fabs(_v_sp[i]) /_treshhold_sp);
        _b_sp[i] = _pb_sp[i] + _damp_sp[i] *(_b_sp[i] - _pb_sp[i]);
        _v_sp[i] = v_last + _damp_sp[i] * (_v_sp[i] - v_last);

        factor = mwoibn::eigen_utils::limitHalfPi(_b[i],_b_sp[i]);
        factor = limit2PI_v(_b[i], _b_sp[i], factor);
        _v_sp[i] = std::pow(-1,factor)*_v_sp[i]; // change sign to fit with steering

}
