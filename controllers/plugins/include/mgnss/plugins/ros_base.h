#ifndef __MGNSS__PLUGINS__ROS_BASE_H
#define __MGNSS__PLUGINS__ROS_BASE_H

#include "mgnss/plugins/generator.h"
#include <mwoibn/common/ros_logger.h>
#include <ros/ros.h>
#include "mwoibn/std_utils/map.h"


namespace mgnss::plugins
{
class RosPublisher{

public:
  RosPublisher(std::shared_ptr<ros::NodeHandle> node){
    _node.reset(new ros::NodeHandle());
  }
  ~RosPublisher(){
    _pub.shutdown();
  }

  template<typename Message>
  void reset(const RosPublisher& other){
      std::string topic = other._pub.getTopic();
      //other._pub.shutdown();
      _pub = _node->advertise<Message>(topic, 1);
  }

  template<typename Message>
  void reset(RosPublisher&& other){
      std::string topic = other._pub.getTopic();
      other._pub.shutdown();
      _pub = _node->advertise<Message>(topic, 1);
  }

  template<typename Message>
  void publish(const Message& msg ){
    _pub.publish(msg);
  }

  template<typename Message>
 void advertise(const std::string& topic){
   _pub = _node->advertise<Message>(topic, 1);
 }

protected:
  std::shared_ptr<ros::NodeHandle> _node;
  ros::Publisher _pub;
};
}


#define MGNSS_REGISTER_ROS_PLUGIN_(constructor) \
extern "C" mgnss::plugins::RosBase* make() \
{ \
  return new mgnss::plugins::RosPlugin<constructor<ros::Subscriber, ros::ServiceServer, ros::NodeHandle, mgnss::plugins::RosPublisher>>(); \
} \

namespace mgnss
{
namespace plugins
{

class RosBase
{

  typedef  std::map<std::string, std::shared_ptr<mwoibn::robot_class::Robot>> robot_map;
  typedef  MapKeyIterator<std::string, std::shared_ptr<mwoibn::robot_class::Robot>> _key_iter;
  typedef  MapValueIterator<std::string, std::shared_ptr<mwoibn::robot_class::Robot>> _val_iter;
  typedef  mgnss::plugins::Generator<ros::Subscriber, ros::ServiceServer, ros::NodeHandle, RosPublisher> RosGenerator_;
public:
// RosBase(int argc, char** argv, std::string name): _name(name){
//    _init(argc, argv);
// }

RosBase() { }

virtual void connect(int argc, char** argv, std::string name);
virtual void connect(std::string name);

virtual ~RosBase(){
}

virtual bool init();
virtual bool init(robot_map& share_robots, std::shared_ptr<mwoibn::common::Logger>& logger_ptr, std::shared_ptr<ros::NodeHandle> n, mwoibn::communication_modules::Shared& share, std::string name);

virtual bool close(){ _plugin_ptr->close(); return true;}

virtual void start(double time){_plugin_ptr->start(time);}

virtual void stop(){_plugin_ptr->stop();}
virtual void control_loop(double time){_plugin_ptr->control_loop(time);}

  RosGenerator_& plugin(){return *_plugin_ptr;}

protected:
std::unique_ptr<RosGenerator_> _plugin_ptr;
std::string _configFile();

//std::shared_ptr<ros::NodeHandle> _n;

};

template<typename Plugin>
class RosPlugin: public RosBase{
public:
    RosPlugin(): RosBase(){
        _plugin_ptr.reset(new Plugin());
    }
};

}
}
#endif // RT_MY_TEST_H
