#ifndef __MGNSS__CONTROLLERS_BASE_H
#define __MGNSS__CONTROLLERS_BASE_H

#include <mwoibn/robot_class/robot.h>

namespace mgnss
{
namespace modules
{
class Base
{

public:
  Base(mwoibn::robot_class::Robot& robot): _robot(robot){}

  ~Base() {}

  virtual void init() = 0;
  virtual void update() = 0;
  virtual void send() = 0;
  virtual void stop() = 0;
  virtual void close() = 0;
  virtual void setRate(double rate){
    _robot.setRate(rate);
  }

protected:
  mwoibn::robot_class::Robot& _robot;
};
}
}

#endif // WHEELED_MOTION_H