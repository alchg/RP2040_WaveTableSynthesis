#ifndef SYNTHESIS_H
#define SYNTHESIS_H

#define WAVE_TYPES    7
#define SHORT_WAVE    0
#define SAWTOOTH_WAVE 1
#define SINE_WAVE     2
#define TRIANGLE_WAVE 3
#define SAMPLE_WAVE1  4
#define SAMPLE_WAVE2  5
#define NOISE_WAVE    6


#define VOLUME_MAX  16
#define SAMPLE      128

#define CHANNELS    5
#define CH1 0
#define CH2 1
#define CH3 2
#define CH4 3
#define CH5 4

static uint16_t pwm_pin;
static uint16_t waveform[WAVE_TYPES][VOLUME_MAX][SAMPLE];
static uint16_t slice_num;
static uint16_t channel_wave[CHANNELS];
static uint16_t note[CHANNELS];
static uint16_t work[CHANNELS];
static uint16_t vol[CHANNELS];
static uint16_t level;

class Synthesis {
public:
  Synthesis();
  Synthesis(uint16_t pin);
  void begin();
  void setVolume(uint16_t ch,uint16_t value);
  void setNote(uint16_t ch,uint16_t value);
  void setWave(uint16_t ch,uint16_t value);
  uint16_t getWaveTableValue(uint16_t i,uint16_t j,uint16_t k);
private:
  void initializeWave();
  static bool isEven(uint16_t value);
  static void pwmIrq();
};

#endif // SYNTHESIS_H
