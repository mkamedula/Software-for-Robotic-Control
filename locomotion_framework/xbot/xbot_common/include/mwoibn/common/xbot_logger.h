#ifndef __MWOIBN_COMMON_XBOT_LOGGER_H
#define __MWOIBN_COMMON_XBOT_LOGGER_H

#include "mwoibn/common/logger.h"
#include <matio.h>
#include "XBotInterface/MatLogger.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>

namespace mwoibn {
namespace common {
class XbotLogger: public Logger{

public:
  XbotLogger(std::string name){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;

    oss << name << "_" << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S") << ".txt";

    _logger = XBot::MatLogger::getLogger(oss.str());
    std::cout << "opened log _file " << oss.str() << std::endl;

    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL)
      std::cout << "working directory\t" << cwd << std::endl;

  }
  ~XbotLogger(){}

  virtual void write(){}

  virtual void flush(){_logger->flush();}
  virtual void close(){}

protected:
  XBot::MatLogger::Ptr _logger;

  virtual void _addField(const std::string& name, double init_value){
    _full_name = _prefix;
    _full_name += ":";
    _full_name += name;
    _logger->add(_full_name, init_value);
  }
  virtual void _addEntry(const std::string& name, double value){
    _full_name = _prefix;
    _full_name += ":";
    _full_name += name;
    _logger->add(_full_name, value);
  }

  virtual void _start(){}

};

}

}

#endif
