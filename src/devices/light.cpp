#include <Arduino.h>
#include "devices/light.h"

#define LED_PIN 26

bool trangThaiDen = LOW;

void khoiTaoDen() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void batDen() {
    trangThaiDen = HIGH;
    digitalWrite(LED_PIN, HIGH);
}

void tatDen() {
    trangThaiDen = LOW;
    digitalWrite(LED_PIN, LOW);
}

void daoTrangThaiDen() {
    trangThaiDen = !trangThaiDen;
    digitalWrite(LED_PIN, trangThaiDen ? HIGH : LOW);
}

bool layTrangThaiDen() {
    return trangThaiDen;
}