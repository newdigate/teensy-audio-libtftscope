#include <Audio.h>
#include <ST7735_t3.h> // Hardware-specific library for ST7735
#include "ScopeView.h"

#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   -1 // RST can use any pin
ST7735_t3 TFT = ST7735_t3(TFT_CS, TFT_DC, TFT_RST);

// GUItool: begin automatically generated code
AudioInputI2S            tdm_in;           //xy=514,291
AudioOutputI2S           tdm_out;           //xy=544,281
AudioControlSGTL5000     cs42448;
AudioRecordQueue         audioRecordQueue1; 
AudioSynthWaveformSine   sine1;          //xy=272,218
AudioConnection          patchCord1(tdm_in, 0, audioRecordQueue1, 0);
AudioConnection          patchCord9(sine1, 0, tdm_out, 0);
// GUItool: end automatically generated code

ScopeView scopeViewCV1 = ScopeView(TFT, audioRecordQueue1, ST7735_CYAN, (int16_t)ST7735_BLACK, 64);

void setup() {
  Serial.begin(9600);
  AudioMemory(120);

  TFT.initR(INITR_144GREENTAB);
  TFT.setRotation(3);
  TFT.fillScreen(ST7735_BLACK);
  sine1.frequency(2);
  sine1.amplitude(1.0);

  audioRecordQueue1.begin();
}

void loop() {
    scopeViewCV1.checkForUpdateBuffer();
    scopeViewCV1.undrawScope();
    scopeViewCV1.drawScope();
}

int main() {
    setup();
    while (true) {
        loop();
    }
}