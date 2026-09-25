#include <Arduino.h>
#include <DHT.h>
#include "devices/dht11.h"

#define DHT_PIN 23
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);  // Tạo obj đại diện dht (nằm ở đâu, loại gì)

unsigned long thoiGianDocDHTTruoc = 0;

void khoiTaoDHT11() {
    dht.begin();
}

float docNhietDo() {
    float nhietDo = dht.readTemperature();
    return nhietDo;
}

float docDoAm() {
    float doAm = dht.readHumidity();
    return doAm;
}

void chayDHT11() {
    unsigned long thoiGianHienTai = millis();

    if (thoiGianHienTai - thoiGianDocDHTTruoc >= 2000) {
        Serial.println("Chay DHT11: ");

        float nhietDo = docNhietDo();
        float doAm = docDoAm();

        if (isnan(nhietDo) || isnan(doAm)) {
            Serial.println("DHT doc nhiet do va do am that bai.");
        }
        else {
            Serial.print("Nhiet do: ");
            Serial.println(nhietDo);

            Serial.print("Do am: ");
            Serial.println(doAm);
        }

        thoiGianDocDHTTruoc = thoiGianHienTai;
    }
}
