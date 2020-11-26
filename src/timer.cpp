// timer.cpp - Part of ESP32 Ruuvitag Collector
// Hannu Pirila 2019
#include "timer.hpp"

namespace timer
{
    namespace
    {
        hw_timer_t *timer = NULL;
        time_t now;
        const int checkTime = 1500000000;
    } // namespace

    void printLocalTime()
    {
        struct tm timeInfo;

        time(&now);
        setenv("TZ", config::timeZone.c_str(), 1);
        tzset();

        if (!getLocalTime(&timeInfo))
        {
            Serial.println("Failed to obtain time.");
            return;
        }
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%A, %B %d %Y %H:%M:%S", &timeInfo);
        Serial.println(buffer);
    }

    namespace watchdog
    {
        void IRAM_ATTR resetModule()
        {
            Serial.println("Reset due to watchdog!\n");
            ESP.restart();
        }
        void feed()
        {
            timerWrite(timer, 0);
        }
        void set()
        {
            timer = timerBegin(0, 80, true);
            timerAttachInterrupt(timer, &resetModule, true);
            timerAlarmWrite(timer, config::watchdogTimeout * global::uSToSFactor, false);
            timerAlarmEnable(timer);
        }
    } // namespace watchdog
    namespace deepsleep
    {
        void updateBootCount()
        {
            global::bootCount++;
        }

        void printBootCount()
        {
            Serial.println();
            Serial.print("Boot number: ");
            Serial.println(global::bootCount);
        }

        void start()
        {
            time(&now);
            int sleepTime = config::deepSleepWakeUpAtSecond - now % config::deepSleepWakeUpAtSecond + config::deepSleepWakeUpOffset;
            esp_sleep_enable_timer_wakeup(sleepTime * global::uSToSFactor);
            Serial.print("Deep sleeping for ");
            Serial.print(sleepTime);
            Serial.println(" seconds...");
            Serial.flush();
            esp_deep_sleep_start();
        }
    } // namespace deepsleep
} // namespace timer
