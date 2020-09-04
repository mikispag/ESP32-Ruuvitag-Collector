// config.hpp - Part of ESP32 Ruuvitag Collector
// Hannu Pirila 2019
#ifndef config_h
#define config_h
#include <set>
#include <string>
#include <vector>
#include <esp_system.h>
#include <BLEDevice.h>
#define DEBUG_ERROR
#define DEBUG_INFORMATION

// See setting descriptions in config.cpp where you can also set values
// Do not set any values here.
namespace config
{
    extern const std::string wiFiSSID;
    extern const std::string wiFiPassword;
    extern const std::string ntpServerIP;
    extern bool longColumnNames;

    extern const int watchdogTimeout;
    extern const int deepSleepWakeUpAtSecond;
    extern const int deepSleepWakeUpOffset;
    extern const std::string timeZone;

    extern std::set<std::string> macWhiteList;

    extern std::string mqttTopicPrefix;
    extern std::string mqttServerIP;
    extern int mqttServerPort;
    extern std::string mqttServerUsername;
    extern std::string mqttServerPassword;
    extern std::string mqttHomeAssistantDiscoveryTopic;
} // namespace config
namespace global
{

    extern const uint64_t nSToSFactor;
    extern const uint64_t uSToSFactor;
    extern const uint64_t mSToSFactor;

    struct RecordHeader
    {
        bool operator==(const RecordHeader &other) const
        {
            return recordLength == other.recordLength && recordType == other.recordType;
        }
        bool operator!=(const RecordHeader &other) const
        {
            return recordLength != other.recordLength || recordType != other.recordType;
        }
        uint8_t recordLength : 5;
        uint8_t recordType : 3;
    };
    extern RTC_DATA_ATTR int bootCount;
    extern BLEScan *pBLEScan;
    extern const int BLEscanTime;
    extern const std::vector<RecordHeader> validHeaders;
    extern int bootCount;
} // namespace global
#endif
