#include <Arduino.h>
#include "devices/ldr.h"

#define LDR_PIN 34
#define NGUONG_TOI 3200

unsigned long thoiGianDocLDRTruoc = 0;
int giaTriLDRTruoc = 0;
int giaTriLDRHienTai;

int docDoSang() {
    return analogRead(LDR_PIN);
}

int layDoSang() {
    return giaTriLDRHienTai;
}

void chayLDR() {
    unsigned long thoiGianHienTai = millis();
    
    if (thoiGianHienTai - thoiGianDocLDRTruoc >= 500) {
        thoiGianDocLDRTruoc = thoiGianHienTai;
        giaTriLDRHienTai = docDoSang();

        if (abs(giaTriLDRHienTai - giaTriLDRTruoc) >= 50) {
            Serial.print("Do sang hien tai: ");
            Serial.println(giaTriLDRHienTai);

            giaTriLDRTruoc = giaTriLDRHienTai;
        }
    }
}