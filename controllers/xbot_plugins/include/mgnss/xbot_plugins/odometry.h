#ifndef __MGNSS_XBOT_PLUGINS_ODOMETRY_H
#define __MGNSS_XBOT_PLUGINS_ODOMETRY_H

#include <XCM/XBotControlPlugin.h>
#include <mwoibn/robot_class/robot_xbot_rt.h>
#include <mgnss/odometry/odometry.h>

namespace mgnss
{
namespace xbot_plugins
{
class Odometry : public XBot::XBotControlPlugin
{

public:
  virtual bool init_control_plugin(XBot::Handle::Ptr handle);

  virtual bool close();

  virtual void on_start(double time);

  virtual void on_stop(double time);

protected:
  virtual void control_loop(double time, double period);

private:

  std::unique_ptr<mgnss::odometry::Odometry> _controller_ptr;
  std::unique_ptr<mwoibn::robot_class::Robot> _robot_ptr;

  bool _initialized = false, _valid = false, _rate = false;

};
}
}
#endif // RT_MY_TEST_H