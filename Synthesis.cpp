#include <Arduino.h>
#include "Synthesis.h"
#include <hardware/pwm.h>

Synthesis::Synthesis() {
  Synthesis(0);
}

Synthesis::Synthesis(uint16_t pin) {
  pwm_pin = pin;
  initializeWave();
  for(int i = 0;i < CHANNELS;i++){
    vol[i] = 7;
  }
}

void Synthesis::initializeWave() {
  for (uint8_t i = 0; i < WAVE_TYPES; i++) {
    for (uint8_t j = 0; j < VOLUME_MAX; j++) {
      for (uint8_t k = 0; k < SAMPLE; k++) {
        switch (i) {
          case SHORT_WAVE:
            waveform[i][j][k] = (k < SAMPLE/2) ? j : 0;
            break;
          case SAWTOOTH_WAVE:
            waveform[i][j][k] = j * k / SAMPLE; 
            break;
          case SINE_WAVE:
            waveform[i][j][k] = j * sin(2 * PI * k / SAMPLE);
            break;
          case TRIANGLE_WAVE:
            if(k / (SAMPLE / 2)){
              waveform[i][j][k] = 0;
            }else{
              waveform[i][j][k] = (k / (SAMPLE / 4)) ? (VOLUME_MAX - ((k - (SAMPLE / 4)) / 2)) * (float(j) / float(VOLUME_MAX)) : (k / 2) * (float(j) / float(VOLUME_MAX));
            }
            break;
          case SAMPLE_WAVE:
            waveform[i][j][k] = (k < SAMPLE/2) ? j * (2 * k) / SAMPLE : j * (2 * (SAMPLE - k)) / SAMPLE;
            break;
          case NOISE_WAVE:
            waveform[i][j][k] = random(j);
            break;
        }
      }
    }
  }
}

uint16_t Synthesis::getWaveTableValue(uint16_t ch,uint16_t vol,uint16_t sample){
  return waveform[ch][vol][sample];
}

bool Synthesis::isEven(uint16_t value){
  bool ret = false;
  
  if((value >> 1) << 1 == value){
    ret = true;
  }

  return ret;
}

void Synthesis::begin(){
  gpio_set_function(pwm_pin, GPIO_FUNC_PWM);

  slice_num = pwm_gpio_to_slice_num(pwm_pin);
  pwm_clear_irq(slice_num);

  pwm_set_irq_enabled(slice_num, true);

  irq_set_exclusive_handler(PWM_IRQ_WRAP, pwmIrq);
  irq_set_enabled(PWM_IRQ_WRAP, true);

  pwm_set_clkdiv(slice_num, 7.8125);
  //pwm_set_wrap(slice_num, 255);
  pwm_set_wrap(slice_num, 256);

  if(isEven(pwm_pin)){
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
  }else{
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);    
  }

  pwm_set_enabled(slice_num, true);
}

void Synthesis::setVolume(uint16_t ch,uint16_t value){
  vol[ch] = value;
}

void Synthesis::setNote(uint16_t ch,uint16_t value){
  note[ch] = value;
}

void Synthesis::setWave(uint16_t ch,uint16_t value){
  if(ch < CHANNELS && value < WAVE_TYPES){
    channel_wave[ch] = value;
  }
}


void Synthesis::pwmIrq(){
  pwm_clear_irq(slice_num);

  for(int i = 0;i < CHANNELS;i++){
    if(channel_wave[i] == NOISE_WAVE){
      work[i] = work[i] + random(note[i]);
    }else{
      work[i] = work[i] + note[i];
    }
  }
  
  level = 0;
  for(int i = 0;i < CHANNELS;i++){
    if(note[i] != 0){ // 0:NOTE_NONE
      level = level + waveform[channel_wave[i]][vol[i]][work[i]>>9];
    }
  }

  if(isEven(pwm_pin)){
    pwm_set_chan_level(slice_num, PWM_CHAN_A, level);
  }else{
    pwm_set_chan_level(slice_num, PWM_CHAN_B, level);
  }
  
}
