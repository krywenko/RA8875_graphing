
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <JsonListener.h>
#include "WundergroundForecast.h"
String command; // serial input capture string

/**
 * Wunderground Settings
 */
const String  WUNDERGRROUND_API_KEY = "e01e78beb97907b8";
const String  WUNDERGR_UND_STATE_OR_COUNTRY = "CAN";
const String  WUNDERGR_UND_CITY = "ARBORG";
const String  WUNDERGRROUND_LANGUAGE = "EN";
const boolean IS_METRIC = true;
const boolean USE_PM = false;
int startW =0;
// initiate the WundergoundClient
WundergroundForecast wunderground(IS_METRIC);

uint32_t runTime = -99999;


// --value carrier
String inString1 = ""; 
String inString2 = ""; 
String inString3 = "";
String inString4 = ""; 
String inString5 = ""; 
//--reserved for later use

String inString6 = ""; 
String inString7 = "";
String inString8 = ""; 
/*String inString9 = ""; 
String inString10 = ""; 
String inString11 = ""; 
String inString12 = ""; 
String inString13 = "";
String inString14 = ""; 
String inString15 = ""; 
String inString16 = ""; 
String inString17 = "";
String inString18 = ""; 
String inString19 = ""; 
String inString20 = "";
*/
//--topics
String input1 = "/invert";
String input2 = "/temp/28ff48a470165ae";
String input3 = "/humid";
String input4 = "/wind";
String input5 = "/grid";
//---reserved for later use

String input6 = "divert";
String input7 = "Ttemp";
String input8 = "Tset";
/*String input9 = "tmp4";
String input10 = "tmp5";
String input11 = "tmp6";
String input12 = "tmp7";
String input13 = "tmp8";
String input14 = "tmp9";
String input15 = "tmp10";
String input16 = "tmp11";
String input17 = "tmp12";
String input18 = "tmp13";
String input19 = "tmp14";
String input20 = "tmp15";
*/
// Update these with values suitable for your network.

const char* ssid = "IOT";
const char* password = "";
const char* mqtt_server = "192.168.168.150";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(19200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  weather();
}
void weather(){
   uint8_t maxForecasts = 1;
  WGForecast forecasts[maxForecasts];
  wunderground.updateForecast(forecasts, maxForecasts, WUNDERGRROUND_API_KEY, WUNDERGRROUND_LANGUAGE, WUNDERGR_UND_STATE_OR_COUNTRY, WUNDERGR_UND_CITY);

  for (int i = 0; i < maxForecasts; i++) {

    Serial.println("cmd_24(" + forecasts[i].forecastIcon + ")");//Serial.println(")");
    delay(150);
    //Serial.println("getForecastTitle: " + forecasts[i].forecastTitle);
   Serial.println("cmd_22(" + forecasts[i].forecastLowTemp + ")");//Serial.println(")");
   delay(150);
   Serial.println("cmd_23(" + forecasts[i].forecastHighTemp + ")");//Serial.println(")");
   delay(150);
   //Serial.print("cmd_26(" + forecasts[i].forecastDay);Serial.println(")");
   // Serial.println("getForecastMonth: " + forecasts[i].forecastMonth);
    Serial.println("cmd_21(" + forecasts[i].forecastText + ")");//;Serial.println(")");
    delay(150);
   Serial.println("cmd_25(" + forecasts[i].PoP + ")");//Serial.println(")");
   delay(150);
   Serial.println("cmd_0(DATA ERROR)");
  }

delay(1000);
}

void setup_wifi() {
WiFi.hostname("espTFTScreen2");
  delay(10);
WiFi.mode(WIFI_STA);   
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {


if (input1 == topic){
  inString1 = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString1 +=  ((char)payload[i]);
  }
  Serial.print("cmd_1("); Serial.print(inString1); Serial.println(")");
  }
if (input2 == topic){
 inString2 = "";
  for (int i=0;i<length;i++) {
     inString2 +=  ((char)payload[i]);  
  }
   Serial.print("cmd_2("); Serial.print(inString2); Serial.println(")");
} 
 if (input3 == topic){
  inString3 = "";
  for (int i=0;i<length;i++) {
     inString3 +=  ((char)payload[i]);
  }
   Serial.print("cmd_3("); Serial.print(inString3); Serial.println(")");
  }
if (input4 == topic){
 inString4 = "";
  for (int i=0;i<length;i++) {
     inString4 +=  ((char)payload[i]); 
  }
  Serial.print("cmd_4("); Serial.print(inString4); Serial.println(")");  
} 
if (input5 == topic){
 inString5 = "";
  for (int i=0;i<length;i++) {
     inString5 +=  ((char)payload[i]);     
  }
 Serial.print("cmd_5("); Serial.print(inString5); Serial.println(")"); 
} 
//---reseved for later use 

if (input6 == topic){
  inString6 = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString6 +=  ((char)payload[i]);   
  }
  Serial.print("cmd_6("); Serial.print(inString6); Serial.println(")");
  }
if (input7 == topic){
 inString7 = "";
  for (int i=0;i<length;i++) {
     inString7 +=  ((char)payload[i]);      
  }
   Serial.print("cmd_7("); Serial.print(inString7); Serial.println(")");
} 
 if (input8 == topic){
  inString8 = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString8 +=  ((char)payload[i]);    
  }
  Serial.print("cmd_8("); Serial.print(inString8); Serial.println(")");
  }
/*if (input9 == topic){
 inString9 = "";
  for (int i=0;i<length;i++) {
     inString9 +=  ((char)payload[i]); 
  }
  Serial.print("cmd_9("); Serial.print(inString9); Serial.println(")");    
} 
if (input10 == topic){
 inString10 = "";
  for (int i=0;i<length;i++) {
     inString10 +=  ((char)payload[i]); 
  }
     Serial.print("cmd_10("); Serial.print(inString10); Serial.println(")");
      
} 

if (input11 == topic){
  inString11 = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString11 +=  ((char)payload[i]);
     Serial.print("cmd_11("); Serial.print(inString11); Serial.println(")");
  }
  }
if (input12 == topic){
 inString12 = "";
  for (int i=0;i<length;i++) {
     inString12 +=  ((char)payload[i]); 
  } 
     Serial.print("cmd_12("); Serial.print(inString12); Serial.println(")");
} 
 if (input13 == topic){
  inString13 = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString13 +=  ((char)payload[i]);
  }
     Serial.print("cmd_13("); Serial.print(inString13); Serial.println(")");
  }
if (input14 == topic){
 inString14 = "";
  for (int i=0;i<length;i++) {
     inString14 +=  ((char)payload[i]);  
  }
     Serial.print("cmd_14("); Serial.print(inString14); Serial.println(")");
} 
if (input15 == topic){
 inString15 = "";
  for (int i=0;i<length;i++) {
     inString15 +=  ((char)payload[i]); 
  }
     Serial.print("cmd_15("); Serial.print(inString15); Serial.println(")");
} 

 if (input16 == topic){
  inString16 = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString16 +=  ((char)payload[i]);
  }
     Serial.print("cmd_16("); Serial.print(inString16); Serial.println(")");
  }
if (input17 == topic){
 inString17 = "";
  for (int i=0;i<length;i++) {
     inString17 +=  ((char)payload[i]); 
  } 
     Serial.print("cmd_17("); Serial.print(inString17); Serial.println(")");
} 
 if (input18 == topic){
  inString18 = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString18 +=  ((char)payload[i]);
  }
     Serial.print("cmd_18("); Serial.print(inString18); Serial.println(")");
  }
if (input19 == topic){
 inString19 = "";
  for (int i=0;i<length;i++) {
     inString19 +=  ((char)payload[i]); 
  } 
     Serial.print("cmd_19("); Serial.print(inString19); Serial.println(")");
} 
if (input20 == topic){
 inString20 = "";
  for (int i=0;i<length;i++) {
     inString20 +=  ((char)payload[i]); 
  }
     Serial.print("cmd_20("); Serial.print(inString20); Serial.println(")");
      
} 


*/
if (startW <1) {weather(); delay(3000);startW++;}
     
    if (millis() - runTime >=(600000 )){
  runTime=millis();
   weather();
  }

 
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("LCDClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe


      client.subscribe("/grid");
      client.subscribe("/wind");
      client.subscribe("/temp/28ff48a470165ae");
      client.subscribe("/invert");
      client.subscribe("/humid");
//---reserved

      client.subscribe("divert");
      client.subscribe("Ttemp");
      client.subscribe("Tset");
 /*     client.subscribe("tmp4");
      client.subscribe("tmp5");
      client.subscribe("tmp6");
      client.subscribe("tmp7");
      client.subscribe("tmp8");
      client.subscribe("tmp9");
      client.subscribe("tmp10");
      client.subscribe("tmp11");
      client.subscribe("tmp12");
      client.subscribe("tmp13");
      client.subscribe("tmp14");
      client.subscribe("tmp15");
*/
     
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
if(WiFi.status() != WL_CONNECTED) {setup_wifi();}
  if (!client.connected()) {
    reconnect();
 }
  client.loop();

   if(Serial.available())
   {
      char c = Serial.read();
    
      if (c == ')')
      {
       
        parseCommand(command);
        
        command="";
      }
      else
      {
       command += c;
      }
  }

}


void parseCommand(String com)
{

//--com variables  
char test[5];
  String part1;
  String part2;
  
  part1 = com.substring(6, com.indexOf("("));
  //int test = part1.toInt();
 // Serial.print(part1);
  //Serial.println("#");
  part2 = com.substring(com.indexOf("(")+1);
  //Serial.println(part2);

//--input 
//////////////////////  

  if (part1 == "100")
  {
    String raw_CMD = part2;
         if (client.connected()){
    if (client.publish("Sw1", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
    }
  if (part1== "101")
    {
      //Serial.println(part2);
     String raw_CMD = part2;
            if (client.connected()){
     if (client.publish("SW2", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
  }

 if (part1 == "102")
    {
     // Serial.println(part2);
      String raw_CMD = part2;
          if (client.connected()){
     if (client.publish("SW3", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
  }

  if (part1 == "103")
  {
    String raw_CMD = part2;
    if (client.connected()){
    if (client.publish("SW4", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
       }
  if (part1== "104")
    {
     // Serial.println(part2);
      String raw_CMD = part2;
          if (client.connected()){
     if (client.publish("SW5", (char*) raw_CMD.c_str())) {
     Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
    }

    if (part1== "105")
    {
      //Serial.println(part2);
      String raw_CMD = part2;
   if (client.connected()){
     if (client.publish("SW6", (char*) raw_CMD.c_str())) {
      Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
   }
    }
    if (part1== "106")
    {
     //Serial.println(part2);
      String raw_CMD = part2;
          if (client.connected()){
  
    if (client.publish("SW7", (char*) raw_CMD.c_str())) {
       Serial.println("cmd_51(published)");
      digitalWrite(BUILTIN_LED, LOW);
    }
    else {
      Serial.println("cmd_52(failed)");
    }
     }
    }
}
