//main programm

#include <TheThingsNetwork.h>

#include <DHT.h>

const char *appEui = "70B3D57ED00361B5";
const char *appKey = "5468006F90DA80D229794D22A3DB5320";

#define loraSerial Serial1
#define debugSerial Serial

#define freqPlan TTN_FP_EU868

#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{ 
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);
  
  //debugSerial.println("-- STATUS");
  //ttn.showStatus();
  
  //debugSerial.println("-- JOIN");
  
  ttn.join(appEui, appKey);
  
  dht.begin();

  pinMode(6, OUTPUT);
}

void loop()
{
  while(!(Serial.available() > 0)){
      delay(1000);   
  }
    
  debugSerial.setTimeout(4000);
   
  uint16_t co2 = Serial.parseInt();
  uint16_t cov = Serial.parseInt();
  if(co2>1900 || cov>550){
    digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
  }else{
    digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)
  }

   
  // Read sensor values and multiply by 100 to effictively have 2 decimals
  
  uint16_t humidity = dht.readHumidity(false) * 100;
  uint16_t temperature = dht.readTemperature(false) * 100;
  
  // Split both words (16 bits) into 2 bytes of 8
 
  byte payload[8];
  
  payload[0] = highByte(temperature);
  payload[1] = lowByte(temperature);
  payload[2] = highByte(humidity);
  payload[3] = lowByte(humidity);
  payload[4] = highByte(co2);
  payload[5] = lowByte(co2);
  payload[6] = highByte(cov);
  payload[7] = lowByte(cov);

  debugSerial.println("------------------------------------------------");
    
  debugSerial.print("Tmp: ");
  debugSerial.print(temperature);
  debugSerial.print(" - Hum: ");
  debugSerial.print(humidity);
  debugSerial.print(" - CO2: ");
  debugSerial.print(co2);
  debugSerial.print(" - COV: ");
  debugSerial.println(cov);

  
  debugSerial.println("------------------------------------------------");

  ttn.sendBytes(payload, sizeof(payload));

  delay(10000);
}

/* //---------------------------------------------------

//byte[64] a='0';

//#define Serial
void setup(){
    Serial.begin(9600);
    Serial.setTimeout(2000);

  
//  loraSerial.begin(57600);
 // debugSerial.begin(9600);
}
void loop(){
  
  if (Serial.available() > 0){
   uint16_t co2 = Serial.parseInt();
   uint16_t cov = Serial.parseInt();

   Serial.print("co2 = ");
   Serial.print(co2);
   Serial.print("  -  cov = ");
   Serial.println(cov);
  }
} 
// ---------------------------------------------------------
*/
/* 

#include <TheThingsNetwork.h>

// First install "DHT sensor library" via the Library Manager
#include <DHT.h>

// Set your AppEUI and AppKey
const char *appEui = "70B3D57ED0035144";
const char *appKey = "AF2B3073166D85C35F6B6990D5F5470D";

#define loraSerial Serial1
#define debugSerial Serial

#define freqPlan TTN_FP_EU868

#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{ 
  loraSerial.begin(57600);
  debugSerial.begin(9600);
  //debugSerial.setTimeout(2000);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);
  
  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
  
  dht.begin();
}

void loop()
{
  //debugSerial.println("-- LOOP");
    uint16_t co2, cov;

    Serial.print("Serial available = ");

    Serial.println(Serial.available());
   while(!(Serial.available() > 0)){

        delay(1000);

   }
    
   debugSerial.setTimeout(1000);
   co2 = Serial.parseInt();
   cov = Serial.parseInt();

  //if (){   //if any data available
     
  //}

    // Read sensor values and multiply by 100 to effictively have 2 decimals
  uint16_t humidity = dht.readHumidity(false) * 100;

  // false: Celsius (default)
  // true: Farenheit
  uint16_t temperature = dht.readTemperature(false) * 100;

  // Split both words (16 bits) into 2 bytes of 8
 
  byte payload[8];
  
  payload[0] = highByte(temperature);
  payload[1] = lowByte(temperature);
  payload[2] = highByte(humidity);
  payload[3] = lowByte(humidity);
  payload[4] = highByte(co2);
  payload[5] = lowByte(co2);
  payload[6] = highByte(cov);
  payload[7] = lowByte(cov);

  debugSerial.print("Tmp: ");
  debugSerial.print(temperature);
  debugSerial.print(" - Hum: ");
  debugSerial.print(humidity);
  debugSerial.print(" - CO2: ");
  debugSerial.print(co2);
  debugSerial.print(" - COV: ");
  debugSerial.println(cov);

  ttn.sendBytes(payload, sizeof(payload));

  delay(3000);
}

/*------------------------------------------------------------

// program with 2 parts (for 2 diffrent applications)

#include <TheThingsNetwork.h>
#include <DHT.h>

const char *appEui_TH = "70B3D57ED0035144";
const char *appKey_TH = "AF2B3073166D85C35F6B6990D5F5470D";

const char *appEui_iAQ = "70B3D57ED0036162";
const char *appKey_iAQ = "8E3AE6F58531396D7EE774CA434032E3";

#define loraSerial Serial1
#define debugSerial Serial

#define freqPlan TTN_FP_EU868

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

TheThingsNetwork ttn_app1(loraSerial, debugSerial, freqPlan);
TheThingsNetwork ttn_app2(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);
  
  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);
 
  //debugSerial.println("-- STATUS");
  //ttn_app1.showStatus();
  
  //debugSerial.println("-- JOIN");
 
  ttn_app2.join(appEui_iAQ, appKey_iAQ);
  ttn_app1.join(appEui_TH, appKey_TH);
  
  dht.begin();
}

void loop()
{
  while(!(Serial.available() > 0)){
      delay(1000);   
  }
    
  debugSerial.setTimeout(1000);
   
  uint16_t co2 = Serial.parseInt();
  uint16_t cov = Serial.parseInt();
   
  // Read sensor values and multiply by 100 to effictively have 2 decimals
  
  uint16_t humidity = dht.readHumidity(false) * 100;
  uint16_t temperature = dht.readTemperature(false) * 100;
 
  byte payload_HT[4];
  byte payload_AQ[4];

  // Split both words (16 bits) into 2 bytes of 8
 
  payload_HT[0] = highByte(temperature);
  payload_HT[1] = lowByte(temperature);
  payload_HT[2] = highByte(humidity);
  payload_HT[3] = lowByte(humidity);
 
  payload_AQ[0] = highByte(co2);
  payload_AQ[1] = lowByte(co2);
  payload_AQ[2] = highByte(cov);
  payload_AQ[3] = lowByte(cov);
  
  debugSerial.print("Tmp: ");
  debugSerial.print(temperature);
  debugSerial.print(" - Hum: ");
  debugSerial.print(humidity);
  debugSerial.print(" - CO2: ");
  debugSerial.print(co2);
  debugSerial.print(" - COV: ");
  debugSerial.println(cov);
  
  ttn_app2.sendBytes(payload_AQ, sizeof(payload_AQ));
  ttn_app1.sendBytes(payload_HT, sizeof(payload_HT));

  
  delay(3000);
}

----------------------------------------------*/
