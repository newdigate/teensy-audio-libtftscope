#include <Audio.h>
#include "ScopeView.h"

void ScopeView::drawScope() {
    if (oscilliscope_x > 127) {
        return;
    }
    _tft->drawLine(oscilliscope_x, _yOffset + (buffer[oscilliscope_x-1] >> 9),     oscilliscope_x + 1, _yOffset + (buffer[oscilliscope_x] >> 9),      _color);
}

void ScopeView::undrawScope() {
    if (oscilliscope_x > 127) {
        return;
    }
    oscilliscope_x = oscilliscope_x + 1;
    _tft->drawLine(oscilliscope_x, _yOffset + (lastbuffer[oscilliscope_x-1] >> 9), oscilliscope_x + 1, _yOffset + (lastbuffer[oscilliscope_x] >> 9),  _backgroundColor);
}

void ScopeView::checkForUpdateBuffer() {
    if (oscilliscope_x >= 127 && _recordQueue->available() > 0) {
      noInterrupts();
      memcpy(lastbuffer, buffer, 256);
      memcpy(buffer, _recordQueue->readBuffer(), 256);

      _recordQueue->freeBuffer();
      oscilliscope_x = 0;
        interrupts();
    } else
    {
        while (_recordQueue->available() > 0) {
            _recordQueue->readBuffer();
            _recordQueue->freeBuffer();
        }
    }
}