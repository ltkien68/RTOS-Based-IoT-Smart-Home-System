#include <Arduino.h>
#include "devices/light.h"
#include "devices/ldr.h"

#define NGUONG_TOI 3200

void autoLightControl() {
    int doSang = layDoSang();

    if (doSang >= NGUONG_TOI) {
        batDen();
    }
    else {
        tatDen();
    }
}