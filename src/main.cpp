#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define ROTARY_ANGLE_SENSOR A1 
#define LED_PIN 4              
#define NUMPIXELS 30           
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

int targetPos = 0; // Memorizza la posizione del "punto fisso"

void setup() {
  Serial.begin(9600);
  pinMode(ROTARY_ANGLE_SENSOR, INPUT);
  
  pixels.begin();
  pixels.setBrightness(150);

  randomSeed(analogRead(A0)); 
  targetPos = random(0, NUMPIXELS);
}

void loop() {
  
  int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
  
  int cursorPos = map(sensor_value, 0, 1023, 0, NUMPIXELS - 1);

  pixels.clear();

  pixels.setPixelColor(targetPos, pixels.Color(255, 0, 50));

  pixels.setPixelColor(cursorPos, pixels.Color(255, 0, 50));

  pixels.show();

  if (cursorPos == targetPos) {
    
    for(int i = 0; i < 4; i++) {
      pixels.fill(pixels.Color(255, 255, 255)); 
      pixels.show();
      delay(300);
      
      pixels.clear(); 
      pixels.show();
      delay(300);
    }
    
    targetPos = random(0, NUMPIXELS);
  }

  delay(30); 
}
