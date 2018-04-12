#include <mgnss/xbot_plugins/wheeled_controller_v2.h>

REGISTER_XBOT_PLUGIN(WheelsV2, mgnss::xbot_plugins::WheelsV2)


bool mgnss::xbot_plugins::WheelsV2::init_control_plugin(XBot::Handle::Ptr handle){
  mgnss::plugins::XbotBase::init_control_plugin(handle);
  _support = get().getSupportReference();
  return true;
}

void mgnss::xbot_plugins::WheelsV2::on_start(double time)
{
    mgnss::plugins::XbotBase::on_start(time);
    if (_valid)
      _support.noalias() = get().getSupportReference();

}

void mgnss::xbot_plugins::WheelsV2::control_loop(double time, double period)
{

    _valid = _robot_ptr->get();

    if (!_valid)
      return;


    _robot_ptr->updateKinematics();

    if (!_initialized)
    {
      //      std::cout << "period\t" << period << std::endl;

 //     if(!_rate){
 //      _setRate(0.0002);
 //      _rate = true;
 //     }

        _setRate(_robot_ptr->rate());

       _valid = _robot_ptr->feedbacks.reset();
       if(_valid){
         _controller_ptr->init();
         _initialized = true;
       }
       //if(_rate && _valid)
    }

    _controller_ptr->update();

    _controller_ptr->send();


    _controller_ptr->log(*_logger_ptr.get(), time-_start);

}
