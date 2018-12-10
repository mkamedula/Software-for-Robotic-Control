#include "mgnss/controllers/centralized_controller.h"


mgnss::controllers::CentralizedController::CentralizedController(mwoibn::robot_class::Robot& robot, std::string config_file, std::string name) :  modules::Base(robot){

        YAML::Node config = mwoibn::robot_class::Robot::getConfig(config_file)["modules"][name];
        config["name"] = name;
        _construct(config);
}

mgnss::controllers::CentralizedController::CentralizedController(mwoibn::robot_class::Robot& robot, YAML::Node config) :  modules::Base(robot){
        _construct(config);
}

void mgnss::controllers::CentralizedController::_construct(YAML::Node config){

        _name = config["name"].as<std::string>();
        _dynamic_model_ptr.reset(
                        new mwoibn::dynamic_models::QrDecomposition(_robot));

        _gravity_compensation_ptr.reset(
                new mwoibn::gravity_compensation::SimpleQRGravityCompensation(
                        *_dynamic_model_ptr, _robot));
}

void mgnss::controllers::CentralizedController::init(){
        update();
}

void mgnss::controllers::CentralizedController::send(){
        _robot.send();
}

void mgnss::controllers::CentralizedController::update(){
        _gravity_compensation_ptr->update();
        //std::cout << _gravity_compensation_ptr->getCommand().transpose() << std::endl;
}