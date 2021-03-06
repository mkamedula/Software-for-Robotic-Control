#ifndef COMMUNICATION_MODULES_ROS_CONTROLLER_H
#define COMMUNICATION_MODULES_ROS_CONTROLLER_H

#include "mwoibn/communication_modules/basic_controller.h"
#include "ros/ros.h"
#include <custom_messages/CustomCmnd.h>

namespace mwoibn
{
namespace communication_modules
{

class RosController : public BasicController
{

public:
  RosController(mwoibn::robot_class::State& command, mwoibn::robot_class::BiMap& map, std::string topic, bool position = true, bool velocity = true, bool effort = true)
      : BasicController(command, map, position, velocity, effort)
  {
    _command_pub = _node.advertise<custom_messages::CustomCmnd>(topic, 1);
    _init();
  }

  // for now only full robot is supported for this controller
  RosController(mwoibn::robot_class::State& command, mwoibn::robot_class::BiMap& map, YAML::Node config)
      : BasicController(command, map, config)
  {
    if(!config["sink"]) throw(std::invalid_argument("Missing required parameter: topic"));

    _command_pub = _node.advertise<custom_messages::CustomCmnd>(config["sink"].as<std::string>(), 1);
    _init(config);

    std::cout << "Loaded ROS controller " << config["name"] << std::endl;

  }

  RosController(mwoibn::robot_class::State& command, mwoibn::robot_class::BiMap&& map, std::string topic, bool position = true, bool velocity = true, bool effort = true)
      : BasicController(command, map, position, velocity, effort)
  {
    _command_pub = _node.advertise<custom_messages::CustomCmnd>(topic, 1);

    _init();
  }

  // for now only full robot is supported for this controller
  RosController(mwoibn::robot_class::State& command, mwoibn::robot_class::BiMap&& map, YAML::Node config)
      : BasicController(command, map, config)
  {
    if(!config["sink"]) throw(std::invalid_argument("Missing required parameter: topic"));

    _command_pub = _node.advertise<custom_messages::CustomCmnd>(config["sink"].as<std::string>(), 1);

    _init(config);

    std::cout << "Loaded ROS controller " << config["name"] << std::endl;

  }

  RosController(RosController& other)
      : BasicController(other),   _node(other._node),
        _des_q(other._des_q), _filtered(other._filtered)
  {
    std::string topic = other._command_pub.getTopic();
    other._command_pub.shutdown();
    _command_pub = _node.advertise<custom_messages::CustomCmnd>(topic, 1);

   }

  RosController(RosController&& other)
      : BasicController(other),   _node(other._node),
        _des_q(other._des_q), _filtered(other._filtered)
  {
    std::string topic = other._command_pub.getTopic();
    other._command_pub.shutdown();
    _command_pub = _node.advertise<custom_messages::CustomCmnd>(topic, 1);
   }


  virtual ~RosController() {}

  virtual bool run();
  virtual bool initialize(){_initFilters(); _initialized = true; return _initialized;}
protected:
  ros::NodeHandle _node;
  ros::Publisher _command_pub;
  custom_messages::CustomCmnd _des_q;
  mwoibn::VectorN _filtered;

  void _initFilters(){
    if(!_filter) return;
    if(_position){
      mapTo(_command.position.get(), _filtered);
      _position_filter_ptr->reset(_filtered);
    }
    if(_velocity){
      mapTo(_command.velocity.get(), _filtered);
      _velocity_filter_ptr->reset(_filtered);
    }
    if(_torque){
      mapTo(_command.torque.get(), _filtered);
      _torque_filter_ptr->reset(_filtered);
    }
  }

  void _init(){
    _des_q.position.resize(getDofs(),0);
    _des_q.velocity.resize(getDofs(),0);
    _des_q.effort.resize(getDofs(),0);
  }

  void _init(YAML::Node config){

    _init();

    if (_filter)
    {
      if (!config["rate"])
        throw(std::invalid_argument(
            "Missing parameter required to initialize filters : rate"));

      _filtered.setZero(getDofs());

      if (_position){
        _position_filter_ptr->computeCoeffs(config["rate"].as<double>());
      }
      if (_velocity)
        _velocity_filter_ptr->computeCoeffs(config["rate"].as<double>());
      if (_torque)
        _torque_filter_ptr->computeCoeffs(config["rate"].as<double>());
    }
  }
//  std::vector<double> pub_qq;

};
}
}

#endif // COMMUNICATION_MODULES_ROS_BASIC_H
