#define USE_ARDUINO_INTERRUPTS false
#include <PulseSensorPlayground.h>
#include <Wire.h>
#include "rgb_lcd.h"
const int OUTPUT_TYPE = SERIAL_PLOTTER;

const int PULSE_INPUT = A0;
const int PULSE_BLINK = LED_BUILTIN;
const int PULSE_FADE = 5;
const int THRESHOLD = 550;   

byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

PulseSensorPlayground pulseSensor;
rgb_lcd lcd;

void setup() {
  Serial.begin(115200);
  // Configure the PulseSensor manager.
  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.blinkOnPulse(PULSE_BLINK);
  pulseSensor.fadeOnPulse(PULSE_FADE);

  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);

  // Skip the first SAMPLES_PER_SERIAL_SAMPLE in the loop().
  samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

  // reading for the PulseSensor signal.
  if (!pulseSensor.begin()) {
    for(;;) {
      // Flash the led to show things didn't work.
      digitalWrite(PULSE_BLINK, LOW);
      delay(50); Serial.println('!');
      digitalWrite(PULSE_BLINK, HIGH);
      delay(50);
    }
  }
}

void loop() {
  if (pulseSensor.sawNewSample()) {
    if (--samplesUntilReport == (byte) 0) {
      samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

      pulseSensor.outputSample();

      if (pulseSensor.sawStartOfBeat()) {
        pulseSensor.outputBeat();
      }
    }

    /*******
      add code here
    *******/
  }
}