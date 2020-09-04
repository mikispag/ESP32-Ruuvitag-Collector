// main.cpp - Part of ESP32 Ruuvitag Collector
// Hannu Pirila 2019
#include <Arduino.h>
#include "config.hpp"
#include "AdvertisedDeviceCallbacks.hpp"
#include "network.hpp"
#include "timer.hpp"

void setup()
{
  Serial.begin(115200);
  timer::watchdog::set();
  timer::watchdog::feed();
  timer::deepsleep::printBootCount();

  network::wifi::begin();
  network::ntp::update();
  timer::printLocalTime();
  network::mqtt::begin();

  BLEDevice::init("");
  global::pBLEScan = BLEDevice::getScan();
  global::pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
  global::pBLEScan->setActiveScan(false);
  BLEScanResults foundDevices = global::pBLEScan->start(global::BLEscanTime);

  timer::deepsleep::updateBootCount();
  timer::deepsleep::start();
}

void loop()
{
}
