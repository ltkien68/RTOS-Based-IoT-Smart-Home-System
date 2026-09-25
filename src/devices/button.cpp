#include <Arduino.h>
#include "devices/button.h"

#define BUTTON_PIN 4

bool trangThaiDocTruoc = HIGH;
bool trangThaiOnDinh = HIGH;

unsigned long thoiGianButtonThayDoi = 0;
const unsigned long DEBOUNCE_DELAY = 50;

void khoiTaoButton() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool buttonDuocNhan() {
    unsigned long thoiGianHienTai = millis();

    bool trangThaiDoc = digitalRead(BUTTON_PIN);
    if (trangThaiDoc != trangThaiDocTruoc) {
        thoiGianButtonThayDoi = thoiGianHienTai;
    }
        
    bool vuaNhan = false;
    if (thoiGianHienTai - thoiGianButtonThayDoi >= DEBOUNCE_DELAY) {
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