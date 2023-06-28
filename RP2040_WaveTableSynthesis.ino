#include <hardware/pwm.h>
#include "Tone.h"
#include "Synthesis.h"

Synthesis synthesis;  // Default output pin is GPIO 0
/*
#define OUTPUT_PIN 0
Synthesis synthesis(OUTPUT_PIN);
*/
void setup()
{
  /* Check the wave table.
  Serial.begin(115200);
  delay(3000);
  for (uint8_t i = 0; i < WAVE_TYPES; i++) {
    Serial.print("WAVE_TYPE ");
    Serial.println(i + 1);
    for (uint8_t j = 0; j < VOLUME_MAX; j++) {
      for (uint8_t k = 0; k < SAMPLE; k++) {
        Serial.print("[");
        Serial.print(synthesis.getWaveTableValue(i,j,k));
        Serial.print("]");        
      }
      Serial.println("");
    }
  }
  */

  synthesis.begin();
  // setWave
  // CH1 - CH5
  // SHORT_WAVE,SAWTOOTH_WAVE,SINE_WAVE,TRIANGLE_WAVE,SAMPLE_WAVE,NOISE_WAVE
  synthesis.setWave(CH1,NOISE_WAVE);
  // setVolume
  // CH1 - CH5
  // 0 - 16(VOLUME_MAX)
  synthesis.setVolume(CH1,2);
  
  synthesis.setWave(CH2,SAMPLE_WAVE);
  synthesis.setWave(CH3,SAMPLE_WAVE);
  synthesis.setWave(CH4,SAMPLE_WAVE);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
  // setNote
  // CH1 - CH5
  // NOTE_NONE,NOTE_A0 - NOTE_C8,NOTE_20000
  synthesis.setNote(CH1,NOISE_20000);
  delay(100);
  synthesis.setNote(CH1,NOTE_NONE);
  delay(900);
  synthesis.setNote(CH1,NOISE_20000);
  delay(100);
  synthesis.setNote(CH1,NOTE_NONE);
  delay(900);
  synthesis.setNote(CH1,NOISE_20000);
  delay(100);
  synthesis.setNote(CH1,NOTE_NONE);
  delay(900);
  synthesis.setNote(CH1,NOISE_20000);
  delay(100);
  synthesis.setNote(CH1,NOTE_NONE);
  delay(900);
  
  synthesis.setNote(CH2,NOTE_C4);
  delay(1000);
  synthesis.setNote(CH2,NOTE_NONE);

  synthesis.setNote(CH3,NOTE_E4);
  delay(1000);
  synthesis.setNote(CH3,NOTE_NONE);

  synthesis.setNote(CH4,NOTE_G4);
  delay(1000);
  synthesis.setNote(CH4,NOTE_NONE);
  delay(1000);

  synthesis.setNote(CH2,NOTE_C4);
  synthesis.setNote(CH3,NOTE_E4);
  synthesis.setNote(CH4,NOTE_G4);
  delay(4000);
  synthesis.setNote(CH2,NOTE_NONE);
  synthesis.setNote(CH3,NOTE_NONE);
  synthesis.setNote(CH4,NOTE_NONE);
  
  synthesis.setNote(CH2,NOTE_C4);
  synthesis.setNote(CH3,NOTE_F4);
  synthesis.setNote(CH4,NOTE_A4);
  delay(4000);
  synthesis.setNote(CH2,NOTE_NONE);
  synthesis.setNote(CH3,NOTE_NONE);
  synthesis.setNote(CH4,NOTE_NONE);

  synthesis.setNote(CH2,NOTE_B3);
  synthesis.setNote(CH3,NOTE_F4);
  synthesis.setNote(CH4,NOTE_G4);
  delay(4000);
  synthesis.setNote(CH2,NOTE_NONE);
  synthesis.setNote(CH3,NOTE_NONE);
  synthesis.setNote(CH4,NOTE_NONE);

  synthesis.setNote(CH2,NOTE_C4);
  synthesis.setNote(CH3,NOTE_E4);
  synthesis.setNote(CH4,NOTE_G4);
  delay(4000);
  synthesis.setNote(CH2,NOTE_NONE);
  synthesis.setNote(CH3,NOTE_NONE);
  synthesis.setNote(CH4,NOTE_NONE);
}
