#include <Audio.h>
#include "ScopeView.h"

void ScopeView::drawScope() {
    if (oscilliscope_x > 127) {
        return;
    }
    _tft->drawLine(oscilliscope_x, _yOffset + (buffer[oscilliscope_x-1] >> 8),     oscilliscope_x + 1, _yOffset + (buffer[oscilliscope_x] >> 8),      _color);
}

void ScopeView::undrawScope() {
    oscilliscope_x = oscilliscope_x + 1;
    if (oscilliscope_x > 127) {
        return;
    }
    _tft->drawLine(oscilliscope_x, _yOffset + (lastbuffer[oscilliscope_x-1] >> 8), oscilliscope_x + 1, _yOffset + (lastbuffer[oscilliscope_x] >> 8),  _backgroundColor);
}

void ScopeView::checkForUpdateBuffer() {
    if (_recordQueue->available() > 0) {
      memcpy(lastbuffer, buffer, 256);
      memcpy(buffer, _recordQueue->readBuffer(), 256);
      _recordQueue->freeBuffer();
      oscilliscope_x = 0;
    }
}