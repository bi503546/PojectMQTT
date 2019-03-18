/*********
 Based on Rui Santos work :
 https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/
 Modified by GM
*********/
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "OneWire.h"
#include "DallasTemperature.h"

WiFiClient espClient;           // Wifi 
PubSubClient client(espClient); // MQTT client

/*===== MQTT broker/server and TOPICS ========*/
const char* mqtt_server = "192.168.43.168"; /* "broker.shiftr.io"; */

#define TOPIC_TEMP "UCA/Batiments/salles/temp"
#define TOPIC_LIGHT "UCA/Batiments/salles/lumiére"
#define TOPIC_RADIATEUR "UCA/Batiments/salles/radiateur"



/*============= GPIO ======================*/
float temperature = 0;
float light = 0;
int sensorValue;
const int radiateur = 0;
const int portOneWire = 23;
const int ledPin = 25; // LED Pin
const int rad =24; //LED representant le radiateur

const float min_temp = 15;
const float max_temp = 20;

OneWire tempOneWire(portOneWire);
DallasTemperature tempSensor(&tempOneWire);

/*==========Déclaration des fonctions =========*/

/* Set Lumiére */
void set_LED(int v){ 
  digitalWrite(ledPin, v);
}

/* Set radiateur */  
void set_rad(int v){  
   digitalWrite(rad, v);  
}

/* Calculer la température d'une salle*/
float get_Temperature(){
  float temp ;
  tempSensor.requestTemperaturesByIndex(0) ; // Le capteur 0 realise une acquisition
  temp = tempSensor.getTempCByIndex(0) ; // On transfert le float qui correspond a
  // temp acquise
  return temp;
  delay(1000) ;
}

/*================ WIFI =======================*/
void print_connection_status() {
  Serial.print("WiFi status : \n");
  Serial.print("\tIP address : ");
  Serial.println(WiFi.localIP());
  Serial.print("\tMAC address : ");
  Serial.println(WiFi.macAddress());
}

void connect_wifi() {
  const char* ssid = "HUAWEI Y5 2018";
  const char *password= "14a2fc1a96e6";
  
  Serial.println("Connecting Wifi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect Wifi ..");
    delay(1000);
  }
  Serial.print("Connected to local Wifi\n");
  print_connection_status();
}

/*=============== SETUP =====================*/
void setup() {  
  pinMode(ledPin, OUTPUT);
  pinMode(rad, OUTPUT);
  tempSensor.begin(); 

  Serial.begin(9600);
  
  connect_wifi();
  client.setServer(mqtt_server, 1883);
  // set callback when publishes arrive for the subscribed topic
  client.setCallback(mqtt_pubcallback); 
}

/*============== CALLBACK ===================*/
void mqtt_pubcallback(char* topic, byte* message, 
                      unsigned int length) {
  // Callback if a message is published on this topic.
  
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  // Byte list to String and print to Serial
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic,
  // you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == TOPIC_LIGHT) {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      set_LED(HIGH);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      set_LED(LOW);
    }
  }

  if (String(topic) == TOPIC_TEMP) {
    
    float currentTemperature = get_Temperature();
    char currentTempStr[5];
    dtostrf(currentTemperature,5,2,currentTempStr);
    client.publish(TOPIC_TEMP,currentTempStr);
  }
  if(String(topic) == TOPIC_RADIATEUR){
    float currentTemperature = get_Temperature();
    if(currentTemperature < 23){
      digitalWrite(rad, HIGH);
      client.publish(TOPIC_RADIATEUR,"Radiateur en marche !");
    }
    else {
      digitalWrite(rad, LOW);
      client.publish(TOPIC_RADIATEUR,"Radiateur éteint !");
    }
    delay(500) ;  // wait 1s for next readin
  }
}

/*============= SUBSCRIBE =====================*/
void mqtt_mysubscribe(char *topic) {
  while (!client.connected()) { // Loop until we're reconnected
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Projet MQTT ESP32 - Rachida & Imen", "try", "try")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/*================= LOOP ======================*/
void loop() {
  int32_t period = 5000; // 5 sec
  /*--- subscribe to TOPIC if not yet ! */
  if (!client.connected()) { 
    mqtt_mysubscribe((char *)(TOPIC_TEMP));    
    //mqtt_mysubscribe((char *)(TOPIC_RADIATEUR));
    
  }

  /*--- Publish Temperature periodically   */
  delay(period);
  temperature = get_Temperature();
  // Convert the value to a char array
  char tempString[8];
  dtostrf(temperature, 1, 2, tempString);
  // Serial info
  Serial.print("Published Temperature : ");
  Serial.println(tempString);
  // MQTT Publish
  client.publish(TOPIC_TEMP, tempString);
 
  client.loop(); // Process MQTT ... une fois par loop()
}
