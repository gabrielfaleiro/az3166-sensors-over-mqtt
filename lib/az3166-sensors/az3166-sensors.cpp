
#include "az3166-sensors.h"

// Global variables
DevI2C *i2c;
HTS221Sensor *sensorTH;
LPS22HBSensor *sensorP;

void az3166SensorSetup(){
    // Init sensors
    i2c = new DevI2C(D14, D15);
    sensorTH = new HTS221Sensor(*i2c);
    sensorP = new LPS22HBSensor(*i2c);

    sensorTH -> init(NULL);
    sensorP -> init(NULL);
}

float az3166ReadTemperature(){
    unsigned char id;
    float temp = 0;
    sensorTH -> enable();
    // read id
    sensorTH -> readId(&id);
    // get temperature
    sensorTH -> getTemperature(&temp);
    // disable the sensor
    sensorTH -> disable();
    // reset
    sensorTH -> reset();

    return temp;
}

float az3166ReadHumidity(){
    unsigned char id;
    float hum = 0;
    sensorTH -> enable();
    // read id
    sensorTH -> readId(&id);
    // get humidity
    sensorTH -> getHumidity(&hum);
    // disable the sensor
    sensorTH -> disable();
    // reset
    sensorTH -> reset();

    return hum;
}

float az3166ReadPressure(){
    unsigned char id;
    float pres = 0;
    // get pressure
    sensorP -> getPressure(&pres);

    return pres;
}