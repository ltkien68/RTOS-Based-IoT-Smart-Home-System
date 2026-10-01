#include <Arduino.h>
#include "devices/button.h"
#include "devices/light.h"
#include "services/manualLightControl.h"

void manualLightControl() {
    if (buttonDuocNhan()) {
        daoTrangThaiDen();

        if (layTrangThaiDen() == HIGH) {
            Serial.println("Den bat\n");
        }
        else {
            Serial.println("Den tat\n");
        }
    }
}