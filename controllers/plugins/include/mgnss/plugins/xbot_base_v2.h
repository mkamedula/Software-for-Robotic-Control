#ifndef __MGNSS_PLUGINS_XBOT_BASE_UNIFY_H
#define __MGNSS_PLUGINS_XBOT_BASE_UNIFY_H

#include <XCM/XBotControlPlugin.h>
#include <mwoibn/robot_class/robot_xbot_rt.h>
#include "mgnss/modules/base.h"
#include "mgnss/plugins/generator.h"
#include <mwoibn/common/xbot_logger.h>

#define MGNSS_REGISTER_XBOT_PLUGIN_(constructor) \
    REGISTER_XBOT_PLUGIN_((mgnss::plugins::XBotPlugin<constructor<XBot::RosUtils::SubscriberWrapper::Ptr, XBot::RosUtils::ServiceServerWrapper::Ptr, XBot::RosUtils::RosHandle> >)) \


namespace mgnss
{
namespace plugins
{

class XbotBaseUnify : public XBot::XBotControlPlugin
{

  typedef  mgnss::plugins::Generator<XBot::RosUtils::SubscriberWrapper::Ptr, XBot::RosUtils::ServiceServerWrapper::Ptr, XBot::RosUtils::RosHandle> XbotGenerator_;
  typedef  std::map<std::string, std::shared_ptr<mwoibn::robot_class::Robot>> robot_map;


public:
  XbotBaseUnify(){
  }

  void connect(XBot::Handle::Ptr handle)
  {
          _plugin_ptr->n = handle->getRosHandle();
  }

virtual bool init_control_plugin(XBot::Handle::Ptr handle);
virtual bool init_control_plugin(XBot::Handle::Ptr handle, robot_map& share_robots, std::shared_ptr<mwoibn::common::Logger>& logger_ptr, std::shared_ptr<XBot::RosUtils::RosHandle> n, mwoibn::communication_modules::Shared& share, std::string name);

virtual bool close(){_plugin_ptr->close();}

virtual void on_start(double time){_plugin_ptr->start(time);}

virtual void on_stop(double time){_plugin_ptr->stop();}

XbotGenerator_& plugin(){return *_plugin_ptr;}

protected:

  std::unique_ptr<XbotGenerator_> _plugin_ptr;

  std::string _configFile(XBot::Handle::Ptr handle);

  virtual void control_loop(double time, double period){
      _plugin_ptr->control_loop(time);}


};

template<typename Plugin>
class XBotPlugin: public XbotBaseUnify{
public:
    XBotPlugin(): XbotBaseUnify(){
        _plugin_ptr.reset(new Plugin());
    }
};
}
}
#endif // RT_MY_TEST_H
