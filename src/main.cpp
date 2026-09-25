#include <Arduino.h>
#include "devices/button.h"
#include "devices/light.h"
#include "devices/dht11.h"



void setup() {
    Serial.begin(115200);

    khoiTaoDen();
    khoiTaoButton();
    khoiTaoDHT11();
}

void loop() {
    if (buttonDuocNhan()) {
        daoTrangThaiDen();

        if (layTrangThaiDen() == HIGH) {
            Serial.print("Den bat\n");
        }
        else {
            Serial.print("Den tat\n");
        }
    }

    chayDHT11();
    
}