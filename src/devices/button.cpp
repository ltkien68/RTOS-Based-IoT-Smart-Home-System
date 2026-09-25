#include <Arduino.h>
#include "devices/button.h"

#define BUTTON_PIN 4

bool trangThaiDocTruoc = HIGH;
bool trangThaiOnDinh = HIGH;

unsigned long thoiGianThayDoi = 0;
const unsigned long DEBOUNCE_DELAY = 50;

void khoiTaoButton() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool buttonDuocNhan() {
    bool trangThaiDoc = digitalRead(BUTTON_PIN);
    if (trangThaiDoc != trangThaiDocTruoc) {
        thoiGianThayDoi = millis();
    }
    
    bool vuaNhan = false;
    if (millis() - thoiGianThayDoi >= DEBOUNCE_DELAY) {
        if (trangThaiDoc != trangThaiOnDinh) {
            trangThaiOnDinh = trangThaiDoc;

            if (trangThaiOnDinh == LOW) {
                vuaNhan = true;
            }
        }
    }

    trangThaiDocTruoc = trangThaiDoc;

    return vuaNhan;
}