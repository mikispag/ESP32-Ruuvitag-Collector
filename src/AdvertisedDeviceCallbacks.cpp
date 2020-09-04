// AdvertisedDeviceCallbacks.cpp - Part of ESP32 Ruuvitag Collector
// Hannu Pirila 2019
#include "AdvertisedDeviceCallbacks.hpp"

using namespace std;

void AdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice)
{
    bool processMac = false;
    BLEAddress bleAddress = BLEAddress(advertisedDevice.getAddress());
    string data = advertisedDevice.getManufacturerData();
    string mac;

    mac = buildMac(bleAddress);

    for (auto m : config::macWhiteList)
    {
        if (mac == m)
        {
            Serial.printf("WHITELISTED %s FOUND!\n", mac.c_str());
            observedMacAddresses.insert(mac);
            processMac = true;
        }
    }
    if (config::macWhiteList.size() < 1)
    {
        processMac = true;
    }
    if (processMac)
    {
        Datahandler dh = Datahandler(data, mac);
        dh.setTime();
        dh.buildMeasurement();
        dh.sendMqtt();
    }
    else
    {
        Serial.printf("Ignored device with MAC %s found.\n", mac.c_str());
    }
    if (config::macWhiteList.size() > 0)
    {
        if (observedMacAddresses == config::macWhiteList)
        {
            global::pBLEScan->stop();
        }
    }
}

string AdvertisedDeviceCallbacks::buildMac(BLEAddress bleAddress)
{
    stringstream stream;
    for (int i = 0; i < 6; i++)
    {
        stream << setfill('0') << setw(2) << uppercase << hex << (int)((uint8_t *)(bleAddress.getNative()))[i];
    }
    return stream.str();
}