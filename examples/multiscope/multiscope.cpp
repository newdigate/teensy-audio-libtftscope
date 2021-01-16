#include <Audio.h>
#include <Wire.h>
#include "ScopeView.h"
#include <ST7735_t3.h> // Hardware-specific library for ST7735

#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   -1 // RST can use any pin
ST7735_t3 TFT = ST7735_t3(TFT_CS, TFT_DC, TFT_RST);

// GUItool: begin automatically generated code
AudioInputTDM            tdm_in;           //xy=514,291
AudioOutputTDM           tdm_out;           //xy=544,281
AudioControlCS42448      cs42448;
AudioRecordQueue         audioRecordQueue1; 
AudioRecordQueue         audioRecordQueue2; 
AudioRecordQueue         audioRecordQueue3; 
AudioRecordQueue         audioRecordQueue4; 
AudioRecordQueue         audioRecordQueue5; 
AudioRecordQueue         audioRecordQueue6; 
AudioRecordQueue         audioRecordQueue7; 
AudioRecordQueue         audioRecordQueue8; 

AudioSynthWaveformSine   sine1;          //xy=272,218
AudioSynthWaveformSine   sine2;          //xy=272,218
AudioSynthWaveformSine   sine3;          //xy=272,218
AudioSynthWaveformSine   sine4;          //xy=272,218
AudioSynthWaveformSine   sine5;          //xy=272,218
AudioSynthWaveformSine   sine6;          //xy=272,218
AudioSynthWaveformSine   sine7;          //xy=272,218
AudioSynthWaveformSine   sine8;          //xy=272,218

AudioConnection          patchCord1(tdm_in, 0, audioRecordQueue1, 0);
AudioConnection          patchCord2(tdm_in, 2, audioRecordQueue2, 0);
AudioConnection          patchCord3(tdm_in, 4, audioRecordQueue3, 0);
AudioConnection          patchCord4(tdm_in, 6, audioRecordQueue4, 0);
AudioConnection          patchCord5(tdm_in, 8, audioRecordQueue5, 0);
AudioConnection          patchCord6(tdm_in, 10, audioRecordQueue6, 0);
AudioConnection          patchCord7(tdm_in, 12, audioRecordQueue7, 0);
AudioConnection          patchCord8(tdm_in, 14, audioRecordQueue8, 0);
AudioConnection          patchCord9(sine1, 0, tdm_out, 0);
AudioConnection          patchCord10(sine2, 0, tdm_out, 2);
AudioConnection          patchCord11(sine3, 0, tdm_out, 4);
AudioConnection          patchCord12(sine4, 0, tdm_out, 6);
AudioConnection          patchCord13(sine5, 0, tdm_out, 8);
AudioConnection          patchCord14(sine6, 0, tdm_out, 10);
AudioConnection          patchCord15(sine7, 0, tdm_out, 12);
AudioConnection          patchCord16(sine8, 0, tdm_out, 14);
// GUItool: end automatically generated code

uint16_t colors[8] = {ST7735_GREEN,ST7735_RED,ST7735_BLUE,ST7735_CYAN,ST7735_MAGENTA,ST7735_YELLOW,0x00AA,ST7735_WHITE};

ScopeView scopeViewCV1 = ScopeView(TFT, audioRecordQueue1, colors[1], (int16_t)ST7735_BLACK, 64); 
ScopeView scopeViewCV2 = ScopeView(TFT, audioRecordQueue2, colors[2], (int16_t)ST7735_BLACK, 64);
ScopeView scopeViewCV3 = ScopeView(TFT, audioRecordQueue3, colors[3], (int16_t)ST7735_BLACK, 64);
ScopeView scopeViewCV4 = ScopeView(TFT, audioRecordQueue4, colors[4], (int16_t)ST7735_BLACK, 64);
ScopeView scopeViewCV5 = ScopeView(TFT, audioRecordQueue5, colors[5], (int16_t)ST7735_BLACK, 64);
ScopeView scopeViewCV6 = ScopeView(TFT, audioRecordQueue6, colors[6], (int16_t)ST7735_BLACK, 64);
ScopeView scopeViewCV7 = ScopeView(TFT, audioRecordQueue7, colors[7], (int16_t)ST7735_BLACK, 64);
ScopeView scopeViewCV8 = ScopeView(TFT, audioRecordQueue8, colors[8], (int16_t)ST7735_BLACK, 64); 

ScopeView* cvscopes[] = {&scopeViewCV1, &scopeViewCV2, &scopeViewCV3, &scopeViewCV4, &scopeViewCV5, &scopeViewCV6, &scopeViewCV7, &scopeViewCV8};

void setup() {
  Serial.begin(9600);
  AudioMemory(120);

  TFT.initR(INITR_144GREENTAB);
  TFT.setRotation(3);
  TFT.fillScreen(ST7735_BLACK);
  sine1.frequency(2);
  sine1.amplitude(1.0);

  sine2.frequency(2);
  sine2.amplitude(1.0);

  sine3.frequency(2);
  sine3.amplitude(1.0);

  sine4.frequency(2);
  sine4.amplitude(1.0);

  sine5.frequency(2);
  sine5.amplitude(1.0);

  sine6.frequency(2);
  sine6.amplitude(1.0);

  sine7.frequency(2);
  sine7.amplitude(1.0);

  sine8.frequency(2);
  sine8.amplitude(1.0);

  audioRecordQueue1.begin();
  audioRecordQueue2.begin();
  audioRecordQueue3.begin();
  audioRecordQueue4.begin();
  audioRecordQueue5.begin();
  audioRecordQueue6.begin();
  audioRecordQueue7.begin();
  audioRecordQueue8.begin();
}

void loop() {
  
  for (int i=0; i<8; i++) {
    cvscopes[i]->checkForUpdateBuffer();
    cvscopes[i]->undrawScope();
  }
    
  for (int i=0; i<8; i++) {
    cvscopes[i]->drawScope();
  }
}

int main() {
    setup();
    while (true) {
        loop();
    }
}
