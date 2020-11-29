#include "DHT.h"

#define DHTPIN 11
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

int sensor_pin = A0; //Soil Sensor input at Analog Pin A0

int output_value ;

int relayPin = 7;

void setup() {

   Serial.begin(9600);
   
   pinMode(relayPin, OUTPUT);

   dht.begin();

   Serial.println("Reading From the Sensor ...");

//   delay(2000);

   }

void loop() {

   output_value= analogRead(sensor_pin);

   output_value = map(output_value,1019,303,0,100);//Mapping output value to percentage Test Data Dry : 1023 Wet:303
   Serial.print("Soil Moisture : ");
   if(output_value > 100) {

   Serial.print("100");
   Serial.print("Enough Water");
   }

   else if(output_value <=60)
   {
    Serial.print(output_value);
    Serial.println("%");
    Serial.println("Lack of water, pumping water into the field");
    digitalWrite(relayPin, LOW);
   }
   else {
    Serial.print(output_value);
    Serial.println("%");
    Serial.println("Enough Water");
    digitalWrite(relayPin, HIGH);
   }

   delay(2000);

   float h =dht.readHumidity();

  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

   }

   
