// Datahandler.cpp - Part of ESP32 Ruuvitag Collector
// Hannu Pirila 2019
#include "Datahandler.hpp"
#include "network.hpp"

Datahandler::Datahandler(std::string dataIn, std::string macAddressIn)
{
    dataLength = dataIn.length();
    if (dataLength > 2)
    {
        data = dataIn;
        macAddress = macAddressIn;
        if (data[0] == 0x99 && data[1] == 0x04)
        {
            if (data[2] == 0x3 && dataLength > 15)
            {
                measurement.setType(Measurement::ruuviV3);
            }
            if (data[2] == 0x5 && dataLength > 19)
            {
                measurement.setType(Measurement::ruuviV5);
            }
        }
    }
}

Datahandler::~Datahandler()
{
}

void Datahandler::setTime()
{
    time(&epoch);
}

void Datahandler::setTime(time_t timeIn)
{
    epoch = timeIn;
}

void Datahandler::buildMeasurement()
{
    if (measurement.measurementType == Measurement::undefined)
    {
        return;
    }
    measurement.setTime(epoch);
    measurement.build(data);
}

void Datahandler::sendMqtt()
{
    std::string topic;
    std::string payload;

    if (measurement.measurementType == Measurement::undefined)
    {
        return;
    }

    if (global::bootCount < 5 || global::bootCount % 2 == 0)
    {
        network::mqtt::publishDiscovery(macAddress);
    }

    std::stringstream stream;
    stream << config::mqttTopicPrefix << "/";
    stream << macAddress << "/state";
    topic = stream.str();
    stream.str(std::string());
    stream.clear();

    stream << "{\"temperature\":" << measurement.getTemperature() << ",";
    stream << "\"humidity\":" << measurement.getHumidity() << ",";
    stream << "\"pressure\":" << measurement.getPressure() << ",";
    stream << "\"battery\":" << (double)measurement.getVoltage() / 1000 << ",";

    stream << "\"accel_x\":" << measurement.getAccelX() / 1000 << ",";
    stream << "\"accel_y\":" << measurement.getAccelY() / 1000 << ",";
    stream << "\"accel_z\":" << measurement.getAccelZ() / 1000 << ",";
    stream << "\"epoch\":" << measurement.getEpoch() << ",";
    stream << "\"txdbm\":" << measurement.getTXdBm() << ",";
    stream << "\"move_count\":" << measurement.getMoveCount() << ",";
    stream << "\"sequence\":" << measurement.getSequence() << "}";

    payload = stream.str();
    Serial.printf("%s: %s\n", macAddress.c_str(), payload.c_str());
    network::mqtt::publish(topic, payload);
}

std::string Datahandler::toString()
{
    if (measurement.measurementType != Measurement::undefined)
    {
        return measurement.toString();
    }
    else
    {
        return "Measurement undefined";
    }
}
