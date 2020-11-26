// main.cpp - Part of ESP32 Ruuvitag Collector
// Hannu Pirila 2019
#include <Arduino.h>
#include "config.hpp"
#include "AdvertisedDeviceCallbacks.hpp"
#include "network.hpp"
#include "timer.hpp"

void print_reset_menu() {
  Serial.println("You have 3 seconds to press 'r' to reset...");
  delay(3000);
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'r') {
      Serial.println("Reset request received, restarting...");
      ESP.restart();
    }
  }
}

void setup()
{
  Serial.begin(115200);
  timer::watchdog::set();
  timer::watchdog::feed();
  timer::deepsleep::printBootCount();

  print_reset_menu();

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