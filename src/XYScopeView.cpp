#include <Audio.h>
#include "XYScopeView.h"

void XYScopeView::drawScope() {
    if (oscilliscope_x > 127) {
        return;
    }

    if (oscilliscope_x2 > 127) {
        return;
    }
    bool positionDidChange  =   (snake_length == 0)
                                || ((oscilliscope_x > 1 && oscilliscope_x2 > 1 && oscilliscope_x < 128 && oscilliscope_x2 < 128) &&
                                    (buffer_y[oscilliscope_x] >> 9 != buffer_y[oscilliscope_x-1] >> 9
                                    || buffer[oscilliscope_x2] >> 9 != buffer[oscilliscope_x2-1] >> 9));
    if (!positionDidChange) {

        oscilliscope_x++;
        oscilliscope_x2++;
        return;
    }

    if (oscilliscope_x > 127) {
        return;
    }

    if (oscilliscope_x2 > 127) {
        return;
    }

    snake_x[snake_head] = _xOffset - (buffer_y[oscilliscope_x] >> 9);
    snake_y[snake_head] = _yOffset - (buffer[oscilliscope_x2] >> 9);

    _tft->drawPixel(
            snake_x[snake_head],
            snake_y[snake_head],
            _color);

    snake_head+=1;
    snake_head%=SNAKE_SIZE;
    snake_length+=1;

    while (snake_length >= SNAKE_SIZE)
        undrawScope();

    oscilliscope_x++;
    oscilliscope_x2++;
}

void XYScopeView::undrawScope() {

    _tft->drawPixel(
                snake_x[snake_tail],
                snake_y[snake_tail],
                _backgroundColor);
    snake_tail += 1;
    snake_tail %= SNAKE_SIZE;
    snake_length -= 1;
}

void XYScopeView::checkForUpdateBuffer() {
    if (oscilliscope_x >= 127 && _recordQueue->available() > 1)
    {
      noInterrupts();
      memcpy(buffer, _recordQueue->readBuffer(), 256);
      _recordQueue->freeBuffer();
      oscilliscope_x = 0;
        interrupts();
    }

    if (oscilliscope_x2 >= 127 && _recordQueue2->available() > 1) {
        noInterrupts();
        memcpy(buffer_y, _recordQueue2->readBuffer(), 256);
        _recordQueue2->freeBuffer();
        oscilliscope_x2 = 0;
        interrupts();
    }

    if (_recordQueue->available() > 4) {
        _recordQueue->readBuffer();
        _recordQueue->freeBuffer();
    }

    if (_recordQueue2->available() > 4) {
        _recordQueue2->readBuffer();
        _recordQueue2->freeBuffer();
    }

}