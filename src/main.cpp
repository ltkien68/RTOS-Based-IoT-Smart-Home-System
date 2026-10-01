#include <Arduino.h>
#include "devices/button.h"
#include "devices/light.h"
#include "devices/dht11.h"
#include "devices/ldr.h"
#include "services/manualLightControl.h"
#include "services/autoLightControl.h"



void setup() {
    Serial.begin(115200);

    khoiTaoDen();
    khoiTaoButton();
    khoiTaoDHT11();
}

void loop() {
    
    manualLightControl();
    
    chayDHT11();
    
    chayLDR();
    autoLightControl();
}