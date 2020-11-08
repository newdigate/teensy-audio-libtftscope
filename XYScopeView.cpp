#include <Audio.h>
#include "XYScopeView.h"

void XYScopeView::drawScope() {
    if (oscilliscope_x > 127) {
        return;
    }
    //if(oscilliscope_x > 0)
    /*    _tft->drawLine(
                _xOffset + (buffer_y[oscilliscope_x-1] >> 9),
                _yOffset + (buffer[oscilliscope_x-1] >> 9),
                _xOffset + (buffer_y[oscilliscope_x] >> 9),
                _yOffset + (buffer[oscilliscope_x] >> 9),
                _color);
                */
        _tft->drawPixel(
                _xOffset + (buffer_y[oscilliscope_x] >> 9),
                _yOffset + (buffer[oscilliscope_x2] >> 9),
                _color);
}

void XYScopeView::undrawScope() {
    if (oscilliscope_x > 127) {
        return;
    }
    if (oscilliscope_x2 > 127) {
        return;
    }
    oscilliscope_x = oscilliscope_x + 1;
    oscilliscope_x2 = oscilliscope_x2 + 1;

    if (oscilliscope_x < 128 && oscilliscope_x2 < 128)
        _tft->drawPixel(
                _xOffset + (lastbuffer_y[oscilliscope_x] >> 9),
                _yOffset + (lastbuffer[oscilliscope_x2] >> 9),
                _backgroundColor);
        /*
        _tft->drawLine(
                _xOffset + (lastbuffer_y[oscilliscope_x] >> 9),
                _yOffset + (lastbuffer[oscilliscope_x] >> 9),
                _xOffset + (lastbuffer_y[oscilliscope_x+1] >> 9),
                _yOffset + (lastbuffer[oscilliscope_x+1] >> 9),
                _backgroundColor);
*/



}

void XYScopeView::checkForUpdateBuffer() {
    if (oscilliscope_x >= 127 && _recordQueue->available() > 0)
    {
/*
      for (int i=0;i<128;i++){
          _tft->drawPixel(
                  _xOffset + (lastbuffer_y[(i+oscilliscope_x) % 128] >> 9),
                  _yOffset + (lastbuffer[(i+oscilliscope_x2) % 128] >> 9),
                  _backgroundColor);
      }
*/
      noInterrupts();
      memcpy(lastbuffer, buffer, 256);
      memcpy(buffer, _recordQueue->readBuffer(), 256);
      _recordQueue->freeBuffer();
      oscilliscope_x = 0;
        interrupts();
    }

    if (oscilliscope_x2 >= 127 && _recordQueue2->available() > 0) {
        noInterrupts();
        memcpy(lastbuffer_y, buffer_y, 256);
        memcpy(buffer_y, _recordQueue2->readBuffer(), 256);
        _recordQueue2->freeBuffer();
        oscilliscope_x2 = 0;
        interrupts();
    }

    while (_recordQueue->available() > 2) {
        _recordQueue->readBuffer();
        _recordQueue->freeBuffer();
    }

    while (_recordQueue2->available() > 2) {
        _recordQueue2->readBuffer();
        _recordQueue2->freeBuffer();
    }
}