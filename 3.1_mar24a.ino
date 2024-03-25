#include "arduino_secrets.h"
// hp_BH1750 - Version: Latest 
#include <hp_BH1750.h>
#include "thingProperties.h"

float sensor;
hp_BH1750 BH1750;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

pinMode(LED_BUILTIN, OUTPUT);
bool avail= BH1750.begin(BH1750_TO_GROUND);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
//initalise light sensor
BH1750.start();
sensor= BH1750.getLux();
//this stores the value of sensor in intensity
intensity= sensor;
  
}

/*
  Since Intensity is READ_WRITE variable, onIntensityChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onIntensityChange()  {

  if(intensity>300)
  {
    sunlight= true;
    onSunlightChange();
    
    Serial.print("Light intensity: ");
    Serial.print(intensity);
    Serial.println("Good Amount of SUnlight");
  }
  
  //else turn led off
  else
  {
    sunlight=false;
    onSunlightChange();
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Light intensity: ");
    Serial.print(intensity);
    Serial.println("Insufficient Sunlight");
  }
}

/*
  Since Sunlight is READ_WRITE variable, onSunlightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSunlightChange()  {
  if (sunlight=true)
  {
    //turn led on
    digitalWrite(LED_BUILTIN, HIGH);
    //delay 2 sec
    delay(2000);
  }
  else if (sunlight=false)
  {
    //turn led on
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);
  }
}





