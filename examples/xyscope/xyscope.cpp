#include <Audio.h>
#include <Wire.h>

//https://github.com/newdigate/teensy-audio-libtftscope/tree/st7735_t3
#include "XYScopeView.h"
#include <ST7735_t3.h> // Hardware-specific library

#define TFT_SCLK 13  // SCLK can also use pin 14
#define TFT_MOSI 11  // MOSI can also use pin 7
#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   -1 // RST can use any pin

ST7735_t3 TFT = ST7735_t3(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=272,218
AudioSynthWaveformSine   sine2;          //xy=272,218
AudioSynthWaveformSine   sine3;          //xy=272,218
AudioSynthWaveformSine   sine4;          //xy=272,218
AudioSynthWaveformSine   sine5;          //xy=272,218
AudioSynthWaveformSine   sine6;          //xy=272,218
AudioSynthWaveformSine   sine7;          //xy=272,218
AudioSynthWaveformSine   sine8;          //xy=272,218
AudioOutputTDM                  tdm_out;           //xy=514,291
AudioInputTDM               tdm_in;           //xy=514,291
AudioRecordQueue         audioRecordQueue1;
AudioRecordQueue         audioRecordQueue2;
AudioRecordQueue         audioRecordQueue3;
AudioRecordQueue         audioRecordQueue4;
AudioRecordQueue         audioRecordQueue5;
AudioRecordQueue         audioRecordQueue6;
AudioRecordQueue         audioRecordQueue7;
AudioRecordQueue         audioRecordQueue8;

AudioConnection          patchCord1(sine1, 0, tdm_out, 0);
AudioConnection          patchCord2(sine2, 0, tdm_out, 2);
AudioConnection          patchCord3(sine3, 0, tdm_out, 4);
AudioConnection          patchCord4(sine4, 0, tdm_out, 6);
AudioConnection          patchCord5(sine5, 0, tdm_out, 8);
AudioConnection          patchCord6(sine6, 0, tdm_out, 10);
AudioConnection          patchCord7(sine7, 0, tdm_out, 12);
AudioConnection          patchCord8(sine8, 0, tdm_out, 14);

AudioConnection          patchCord9(tdm_in, 0, audioRecordQueue1, 0);
AudioConnection          patchCord10(tdm_in, 2, audioRecordQueue2, 0);
AudioConnection          patchCord11(tdm_in, 4, audioRecordQueue3, 0);
AudioConnection          patchCord12(tdm_in, 6, audioRecordQueue4, 0);
AudioConnection          patchCord13(tdm_in, 8, audioRecordQueue5, 0);
AudioConnection          patchCord14(tdm_in, 10, audioRecordQueue6, 0);
AudioConnection          patchCord15(tdm_in, 12, audioRecordQueue7, 0);
AudioConnection          patchCord16(tdm_in, 14, audioRecordQueue8, 0);

// GUItool: end automatically generated code
uint16_t colors[8] = {ST7735_GREEN,ST7735_RED,ST7735_BLUE,ST7735_CYAN,ST7735_MAGENTA,ST7735_YELLOW,0xffAA,ST7735_WHITE};
XYScopeView scopeViewCV1 = XYScopeView(TFT, audioRecordQueue1, audioRecordQueue2, colors[0], (int16_t)ST7735_BLACK, 64, 64);
XYScopeView scopeViewCV2 = XYScopeView(TFT, audioRecordQueue3, audioRecordQueue4, colors[1], (int16_t)ST7735_BLACK, 64, 64);
XYScopeView scopeViewCV3 = XYScopeView(TFT, audioRecordQueue5, audioRecordQueue6, colors[2], (int16_t)ST7735_BLACK, 64, 64);
XYScopeView scopeViewCV4 = XYScopeView(TFT, audioRecordQueue7, audioRecordQueue8, colors[3], (int16_t)ST7735_BLACK, 64, 64);

XYScopeView* cvscopes[] = {&scopeViewCV1, &scopeViewCV2, &scopeViewCV3, &scopeViewCV4};

void setup() {
    Serial.begin(9600);
    AudioMemory(100);

    sine1.frequency(2.5);
    sine1.amplitude(0.8);

    sine2.frequency(5);
    sine2.amplitude(0.8);

    sine3.frequency(10);
    sine3.amplitude(0.8);

    sine4.frequency(20);
    sine4.amplitude(0.8);

    sine5.frequency(40);
    sine5.amplitude(0.8);

    sine6.frequency(80);
    sine6.amplitude(0.8);

    sine7.frequency(160);
    sine7.amplitude(0.8);

    sine8.frequency(320);
    sine8.amplitude(0.8);

    TFT.initR(INITR_144GREENTAB);
    TFT.setRotation(3);
    TFT.fillScreen(ST7735_BLACK);
    audioRecordQueue1.begin();
    audioRecordQueue2.begin();
    audioRecordQueue3.begin();
    audioRecordQueue4.begin();
    audioRecordQueue5.begin();
    audioRecordQueue6.begin();
    audioRecordQueue7.begin();
    audioRecordQueue8.begin();
}
bool updateDisplay = true, toggleUpdateWhenDisplayReachesEnd = false;

void loop() {
    delayMicroseconds(100);
    if ((cvscopes[0]->oscilliscope_x >= 127 && toggleUpdateWhenDisplayReachesEnd)
        || (toggleUpdateWhenDisplayReachesEnd && !updateDisplay)) {
        updateDisplay = !updateDisplay;
        toggleUpdateWhenDisplayReachesEnd = false;
    }
    for (int i=0;i<4;i++) {
        cvscopes[i]->checkForUpdateBuffer();
    }

    if (updateDisplay)
    {
        for (int i=0;i<4;i++)
            cvscopes[i]->undrawScope();

        for (int i=0;i<4;i++)
            cvscopes[i]->drawScope();
    }

    while (Serial.available()) {
        char ch = Serial.read();
        //Serial.print(ch, DEC);
        if (ch == 10)
            toggleUpdateWhenDisplayReachesEnd = true;
    }

    // Get the update value
    int value = digitalRead(14);
    if ( value == HIGH) {
        toggleUpdateWhenDisplayReachesEnd = true;
    }
}
