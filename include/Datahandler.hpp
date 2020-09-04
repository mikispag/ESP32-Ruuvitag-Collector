// Datahandler.hpp - Part of ESP32 Ruuvitag Collector
// Hannu Pirila 2019
#ifndef Datahandler_hpp
#define Datahandler_hpp

#include <Arduino.h>
#include "Measurement.hpp"
#include "config.hpp"
#include <vector>
#include <iomanip>
#include <sstream>

class Datahandler
{
private:
  std::string data;
  uint8_t dataLength{0};
  std::string macAddress;
  time_t epoch;
  Measurement measurement;

public:
  Datahandler(std::string dataIn, std::string macAddressIn);
  ~Datahandler();
  void buildMeasurement();
  void setTime();
  void setTime(time_t epochIn);
  void sendMqtt();
  std::string toString();
};

#endif
