#ifndef __MGNSS__CONTROLLERS__CENTRALIZED_CONTROLLER_H
#define __MGNSS__CONTROLLERS__CENTRALIZED_CONTROLLER_H

#include "mgnss/modules/base.h"

#include <mwoibn/gravity_compensation/simple_qr_gravity_compensation.h>
//#include <mwoibn/motor_side_reference/sea_reference.h>
#include <mwoibn/dynamic_models/qr_decomposition.h>


namespace mgnss {
namespace controllers {

class CentralizedController : public mgnss::modules::Base {

public:
CentralizedController(mwoibn::robot_class::Robot& robot, std::string config_file, std::string name);
CentralizedController(mwoibn::robot_class::Robot& robot, YAML::Node config);

virtual ~CentralizedController(){
}

virtual void update();
// void fullUpdate(const mwoibn::VectorN& command);
// void fullUpdate(const mwoibn::VectorN& command, const mwoibn::VectorN& vel_command);

virtual void init();
virtual void send();
virtual void stop(){
}
virtual void close(){
}

virtual void initLog(mwoibn::common::Logger& logger){
        logger.addField("time", 0);
}

virtual void log(mwoibn::common::Logger& logger, double time){
        logger.addEntry("time", time);
}

protected:

virtual void _construct(YAML::Node config);
// mwoibn::robot_class::Robot& _reference; // this passes current reference

std::unique_ptr<mwoibn::dynamic_models::QrDecomposition> _dynamic_model_ptr;   // online set up
std::unique_ptr<mwoibn::gravity_compensation::SimpleQRGravityCompensation> _gravity_compensation_ptr;
// std::unique_ptr<mwoibn::motor_side_reference::SeaReference> _actuation_model_ptr;

bool _motor_side = true;
//  bool _valid = false;

};
}
}
#endif // __MGNSS_RT_PLUGINS_RT_MY_TEST_H