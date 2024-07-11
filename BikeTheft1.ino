#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3p_Rk73NI"
#define BLYNK_TEMPLATE_NAME "Bike Theft Alert System"
#define BLYNK_AUTH_TOKEN "HzkkEtBX8GOcLuIlVKMvG02IY88ASzI3"

#include <MPU9250_asukiaaa.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Alen's";
char pass[] = "giveitup";

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("started");

#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  mySensor.beginAccel();
  mySensor.beginGyro();

  Blynk.begin(auth, ssid, pass);
  // You can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;
}

void loop() {
  uint8_t sensorId;
  int result;

  result = mySensor.readId(&sensorId);
  /*if (result == 0) {
    //Serial.println("sensorId: " + String(sensorId));
  } else {
    Serial.println("Cannot read sensorId " + String(result));
  }*/

  result = mySensor.accelUpdate();
  if (result == 0) {
    aX = mySensor.accelX();
    aY = mySensor.accelY();
    aZ = mySensor.accelZ();
    aSqrt = mySensor.accelSqrt();
    Serial.println(String(aX));
    //Serial.println(String(aY));
    //Serial.println(String(aZ));
    //Serial.println(String(aSqrt));
  } else {
    Serial.println("Cannod read accel values " + String(result));
  }

  result = mySensor.gyroUpdate();
  if (result == 0) {
    gX = mySensor.gyroX();
    gY = mySensor.gyroY();
    gZ = mySensor.gyroZ();
    //Serial.println(String(gX));
    //Serial.println(String(gY));
    //Serial.println(String(gZ));
  } else {
    Serial.println("Cannot read gyro values " + String(result));
  }

  BLYNK_WRITE(V6) { // virtual pin
  int buttonState = param.asInt(); // get the state of the button
  if (buttonState == 1) { // check if the button is ON
    if (gX >= min1 && gX <= max1 ||
        gY >= min2 && gY <= max2 &&) {
      Blynk.virtualWrite(V5, 1);
    }
    else{
      Blynk.virtualWrite(V5, 0);
    }
  }
  delay(50);
}

  Blynk.virtualWrite(V0, mySensor.accelX());
  //Blynk.virtualWrite(V1, mySensor.accelY()*10);
  //Blynk.virtualWrite(V2, mySensor.accelZ()*10);
  Blynk.virtualWrite(V3,mySensor.gyroX());
  Blynk.virtualWrite(V4,mySensor.gyroY());
  Blynk.virtualWrite(V5,mySensor.gyroY());
  delay(50);


  //Serial.println("at " + String(millis()) + "ms");
  //Serial.println(""); // Add an empty line
  delay(500);
}