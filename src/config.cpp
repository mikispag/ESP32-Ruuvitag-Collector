// config.cpp - Part of ESP32 Ruuvitag Collector
// Hannu Pirila 2019
#include "config.hpp"

namespace config
{
    // Wifi access point name
    const std::string wiFiSSID = "EDIT_ME";
    // Wifi password
    const std::string wiFiPassword = "EDIT_ME";
    // NTP server, use IP address instead of name
    const std::string ntpServerIP = "129.6.15.28";

    // Only MAC values listed here are scanned or empty list will scan everything.
    // Example: {"D96BF9D2116A","C2CA7F7D07F5"} will scan only these two MAC's
    // Example: {} empty list, everything is scanned. Start with an empty list
    // and then populate it once you know the values. The system works more
    // efficiently with a whitelist as BLUE scan is stopped once list is fulfilled.
    std::set<std::string> macWhiteList = {"D96BF9D2116A", "C2CA7F7D07F5"};

    // MQTT configuration
    // MQTT server a.k.a broker IP address
    std::string mqttServerIP = "192.168.2.1";
    // and port number
    int mqttServerPort = 1883;
    // The topic name this ESP32 is publishing
    // The complete topic will be mqttTopicPrefix/+Ruuvitag mac address/+state
    // Example: ruuviesp32/C2CA7F7D07F5/state
    std::string mqttTopicPrefix = "ruuviesp32";
    // Username to connect MQTT server
    std::string mqttServerUsername = "esp32";
    // and password
    std::string mqttServerPassword = "";
    // Home Assistant can detect Ruuvitags automatically using MQTT discovery
    // Enter name of the topic or leave empty to disable MQTT discovery
    std::string mqttHomeAssistantDiscoveryTopic = "homeassistant";

    // timeZone: Use the second column of the table at https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
    const std::string timeZone = "CET-1CEST,M3.5.0,M10.5.0/3";

    // How often Ruuvitag measurements are collected.
    // Example value  60 causes wake-up at 12:00:00, 12:01:00, 12:02:00... and   ~50 s deep sleep.
    // Example value 120 causes wake-up at 12:00:00, 12:02:00, 12:04:00... and  ~110 s deep sleep.
    // Do not set value below 30 as there is maybe not enough time to handle
    // all the collected data in shorter time periods.
    const int deepSleepWakeUpAtSecond = 60;
    // Example value -2 causes wake-up at 12:00:58, 12:01:58, 12:02:58
    const int deepSleepWakeUpOffset = 0;

    // Watchdog will reset the ESP32 if no action in specified time
    const int watchdogTimeout = 60;

    // Column names are used in report formats, example 'temperature' is long format and 't' is short format
    bool longColumnNames = true;

    // No more settings below
} // namespace config

namespace global
{
    BLEScan *pBLEScan;
    const int BLEscanTime = 30;
    RTC_DATA_ATTR int bootCount = 1;
    const uint64_t nSToSFactor = 1000000000;
    const uint64_t uSToSFactor = 1000000;
    const uint64_t mSToSFactor = 1000;
    const std::vector<RecordHeader> validHeaders = {RecordHeader{20, 0}, RecordHeader{24, 1}};

} // namespace global
