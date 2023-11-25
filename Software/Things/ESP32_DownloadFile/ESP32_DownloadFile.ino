#include <ArduinoJson.h>

#include <WiFi.h>
#include <PubSubClient.h>
// #include "host_bootloader.h"
// #include "port_min.h"
// MAC "c0:49:ef:64:84:f0"
#define ROOM_ID 1
#define NODE_ID 1
//WiFi Config
const char *ssid = "HUST_ManhPD";     
const char *password = "12345687";     

//MQTT Config
const char *mqtt_server = "test.mosquitto.org";//
const int mqtt_port = 1883;

const char *mqttTopic = "WSN/sensor_data"; 
const char *mqttCommandTopic = "WSN/command";
const char *mqttResponseTopic = "WSN/response";

//Led Debug
const int ledPin = 2;  // GPIO_PIN_13

bool wifiConnected = false;


WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
  /*
     Initializing Wifi connections
     When wifi is connected, turn 2 off.
  */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(2, HIGH);
    delay(250);
    digitalWrite(2, LOW);
    delay(250);
  }
}
void reconnectWiFi()
{

  //Retry connect WiFi
  while (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid, password);
    digitalWrite(2, HIGH);
    delay(250);
    digitalWrite(2, LOW);
    delay(250);
  }


}
void reconnect() {
  /* Connecting to MQTT server*/
  // Loop until we're reconnected
  while (!client.connected())
  {
    // Signalizing a MQTT connection
    digitalWrite(2, LOW);
    delay(50);
    digitalWrite(2, HIGH);
    delay(50);

    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      /* If connection to MQTT server is successful, turn 2 on */
      digitalWrite(2, LOW);
      // Resubscribe to topic
      client.subscribe(mqttCommandTopic);
    }
    else
    {
      /* If connection to MQTT server is failed, turn 2 on */
      digitalWrite(2, HIGH);
      // Wait 5 seconds before retrying
      delay(500);
    }
  }
}
void send_mqtt_data(JsonObject jsonObject)
{
    String jsonString;
    serializeJson(jsonObject, jsonString);

    client.publish(mqttTopic, jsonString.c_str());
    //Serial.println("Published to topic: " + jsonString);
}

void MQTT_Data_Callback(char *topic, byte *payload, unsigned int length)
{

  // Handle the received message payload here
  String payloadString;
  
  for (int i = 0; i < length; i++)
  {
    payloadString += (char)payload[i];
  }
  String temp = payloadString;
  char *token = strtok((char *)temp.c_str(), " ");
  
 if (token != NULL)
  {
    token = strtok(NULL, " ");
    int room_id = atoi(token);

    if (token != NULL)
    {
      token = strtok(NULL, " ");

      int node_id = atoi(token);
      
      if (room_id == ROOM_ID && node_id == NODE_ID)
      {
        Serial.println(payloadString);
        digitalWrite(2, HIGH);
        delay(200);
        digitalWrite(2, LOW);
      }
      else
        return;

    }
  }

}

void setup()
{
    //   download_file_init();
    //   bootloader_init();
    // Set up LED pin
    pinMode(ledPin, OUTPUT);

    setup_wifi();

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(MQTT_Data_Callback);


    Serial.begin(115200);
    Serial2.begin(115200);
}



void loop()
{
  //   bootloader_handle();
  if (WiFi.status() != WL_CONNECTED)
  {
    reconnectWiFi();
  }
  if (!client.connected()) {
    reconnect(); 
  }
  client.loop();


  //Task 1
  //CLI
  if (Serial.available())
  {
     String jsonString = Serial.readString(); // Đọc dữ liệu từ UART0
     if (jsonString[0] != '{' )
     {
      String finalJsonString = String("{\"MAC\":\"") + MAC + "\",\"ROOM_ID\":" + String(ROOM_ID) + ",\"NODE_ID\":" + String(NODE_ID) + ",\"DATA_RESPONSE\":" + jsonString + "}";
      client.publish(mqttResponseTopic, finalJsonString.c_str());
     }
     else
     {
        DynamicJsonDocument jsonDocument(256);
        DeserializationError error = deserializeJson(jsonDocument, jsonString);

        if (error)
        {
            Serial2.print("Failed to parse JSON: ");
            Serial2.println(jsonString);
            Serial2.println(error.c_str());
        }
        else
        {
            int node_id = jsonDocument["node_id"];
            uint32_t unixtime = jsonDocument["unixtime"];
            int temp = jsonDocument["temp"];
            int x_axis = jsonDocument["x_axis"];
            int y_axis = jsonDocument["y_axis"];
            int room_id = jsonDocument["room_id"];

            Serial2.print("Received JSON: ");
            Serial2.println(jsonString);

            JsonObject jsonObject = jsonDocument.as<JsonObject>();
            
            send_mqtt_data(jsonObject);
            digitalWrite(2, HIGH);
            delay(50);
            digitalWrite(2, LOW);
            delay(50);
        }
      }
    delay(100);
   }
  
}




