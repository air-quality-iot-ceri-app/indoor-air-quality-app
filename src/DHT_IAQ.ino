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

  pinMode(3, OUTPUT);
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
   
  // Read sensor values and multiply by 100 to effictively have 2 decimals
  
  uint16_t humidity = dht.readHumidity(false) * 100;
  uint16_t temperature = dht.readTemperature(false) * 100;
 
  // Activat an alert 
  // Serious situation
  
  if(co2>1300 || cov>730 || temperature>38){
      digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);
      digitalWrite(3, LOW);
  }else{
      digitalWrite(3, LOW);   // turn the LED off
  }
  
  // Very serious situation
  
  if(co2>3000 || cov>1500 || temperature>45){
      digitalWrite(6, HIGH);   // turn the LED on
  }else{
      digitalWrite(6, LOW);   // turn the LED off
  }

  
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
  
  // Display
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
  
  // Send the data to the TTN
  ttn.sendBytes(payload, sizeof(payload));

  delay(10000);
}
