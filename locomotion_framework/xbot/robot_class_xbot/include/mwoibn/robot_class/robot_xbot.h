#ifndef ROBOT_CLASS_ROBOT_XBOT_H
#define ROBOT_CLASS_ROBOT_XBOT_H

#include "mwoibn/robot_class/robot.h"
#include "mwoibn/robot_class/contact_v2.h"
#include "mwoibn/robot_class/wheel_contact.h"

//#include <SharedLibraryClass.h>

#include <urdf/model.h>
#include <srdfdom/model.h>

namespace mwoibn
{
namespace robot_class
{

//! Implementation of the robot_class for ROS
/**
 * Automatically initializes RBDL model from given ros parameter.
 *
 */
class RobotXBot : public Robot
{

public:
  /**
   * \param[in] is_static information about the model type is required as there
   * are inconsistencies in the output from certain RBDL functions between two
   * types of models
   * \param[in] topic name of the ros parameter comprising the robot
   * description, if no value given dafualt "/robot_description" is used
   */
  RobotXBot(std::string config_file, std::string config_name, std::string secondary_file = "");

  virtual ~RobotXBot() {}
  virtual void wait(){}

protected:
  RobotXBot(){}
  YAML::Node _init(YAML::Node config, std::string config_name);
//  std::string _readUrdf(YAML::Node config);
//  std::string _readSrdf(YAML::Node config);

  int _base_ref = -1;
//  virtual void _readContacts();
  virtual void _readActuators(YAML::Node config);
  virtual void _readContacts(YAML::Node config);
  virtual void _readController(YAML::Node config);
  virtual std::string _getFile(YAML::Node config, std::string name);

//  void _initActuation();

};
} // namespace package
} // namespace library
#endif
