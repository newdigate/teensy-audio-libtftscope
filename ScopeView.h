//
// Created by Nicholas Newdigate on 13/04/2020.
//

#ifndef ARDUINO_MIDI_WRITER_SCOPEVIEW_H
#define ARDUINO_MIDI_WRITER_SCOPEVIEW_H

#include "Arduino.h"
#include <ST7735_t3.h> // Hardware-specific library

#undef swap
#include <functional>
using namespace std;
#undef swap
#define swap(a, b) { typeof(a) t = a; a = b; b = t; }

class ScopeView {
public:
    inline ScopeView(
            ST7735_t3 &tft,
            AudioRecordQueue &recordQueue,
            int16_t color,
            int16_t backgroundColor,
            int8_t yOffset) :
            _tft(&tft),
            _recordQueue(&recordQueue),
            _backgroundColor(backgroundColor),
            _color(color),
            _yOffset(yOffset){
    };

    void undrawScope();
    void drawScope();
    void checkForUpdateBuffer();

    
private:
    ST7735_t3 *_tft;
    AudioRecordQueue *_recordQueue;

    int16_t buffer[128];
    int16_t lastbuffer[128];
    int16_t _backgroundColor;
    int16_t _color;
    int8_t _yOffset;
    uint16_t oscilliscope_x = 0;
};

#endif //ARDUINO_MIDI_WRITER_SCOPEVIEW_H
