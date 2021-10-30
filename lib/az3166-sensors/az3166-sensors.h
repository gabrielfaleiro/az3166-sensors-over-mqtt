
#include <AzureIotHub.h>

#include "HTS221Sensor.h"
#include "LPS22HBSensor.h"

#ifndef _AZ3166_SENSORS_
#define _AZ3166_SENSORS_

void az3166SensorSetup();
float az3166ReadTemperature();
float az3166ReadHumidity();
float az3166ReadPressure();

#endif