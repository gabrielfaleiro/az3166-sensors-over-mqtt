// Includes
#include <Arduino.h>
#include <SPI.h>
#include <AZ3166WiFi.h>

#include <CooperativeMultitasking.h>
#include <MQTTClient.h>

#include "configuration.h"
#include "utils.h"
#include "az3166-sensors.h"


// Global variables
char mqtt_host[] = MQTT_HOST;
char mqtt_clientid[] = MQTT_CLIENT_ID;
char mqtt_user[] = MQTT_USER;
char mqtt_pass[] = MQTT_PASS;

WiFiClient wificlient;

// TODO: try https://github.com/256dpi/arduino-mqtt
CooperativeMultitasking tasks;
MQTTClient mqttclient(&tasks, &wificlient, mqtt_host, 1883, mqtt_clientid, mqtt_username, mqtt_password);
topicNameSensors = MQTT_CLIENT_ID + "/" + "sensors";
MQTTTopic topicSensors(&mqttclient, topicNameSensors);


void setup() {
  char ssid[] = WIFI_SSID;
  char pass[] = WIFI_PASS;
  int wifi_status = WL_IDLE_STATUS;

  char buffer[40];

  // Init Screen
  Screen.init();

  // Init az3166 Sensors
  az3166SensorSetup();

  // Init PINOUT
  pinMode(LED_USER, OUTPUT);
  pinMode(USER_BUTTON_A, INPUT);
  pinMode(LED_AZURE, OUTPUT);

  // Connect to Wifi
  Screen.clean();
  Screen.print(0, "  > Wifi");
  Screen.print(1, "Connecting...");
  wifi_status = WiFi.begin(ssid, pass);
  while ( wifi_status != WL_CONNECTED) {
    delay(TICK_LENGTH_MS);
  }

  IPAddress ip = WiFi.localIP();
  Screen.print(1, "Connected");
  Screen.print(2, ip.get_address());
  
  // Connect to MQTT Broker
  Screen.clean();
  Screen.print(0, "  > MQTT");
  Screen.print(1, "Connecting...");
  sprintf(buffer, "Host: " + mqtt_host);
  Screen.print(2, buffer);
  if (!mqttclient.connected()) {
    mqttclient.connect();
  }

  digitalWrite(LED_AZURE, HIGH);

  // TODO: publish mqtt message watchdog to notify a reboot

  Screen.clean();
}

void loop() {
  static uint32_t tick_counter = 0;
  static float temp = 0;
  static float hum = 0;
  static float pres = 0;
  char buffer[40];

  // TODO Reboot board of MQTT or wifi is not connected

  // Operate on led feedback using a button
  button_led_feedback(USER_BUTTON_A, LED_USER);

  // Update LCD
  if (! (tick_counter % tick_5s)){
    temp = az3166ReadTemperature();
    hum = az3166ReadHumidity();
    pres = az3166ReadPressure();

    // 16 characters per line
    Screen.print(0, MQTT_CLIENT_ID);
    IPAddress ip = WiFi.localIP();
    Screen.print(1,ip.get_address());
    sprintf(buffer, "temp:%5.1f", temp);
    Screen.print(2, buffer);
    sprintf(buffer, "hum: %5.1f", hum);
    Screen.print(3, buffer);
  }

  // Send MQTT message
  if (! (tick_counter % tick_5s)){
  // TODO: send message every minute
  //if (! (tick_counter % tick_1m)){
    topicSensors.publish("test");
  }

  delay(TICK_LENGTH_MS);
  tick_counter++;
}