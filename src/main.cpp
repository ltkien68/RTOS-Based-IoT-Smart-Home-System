#include <Arduino.h>

#define LED_PIN 18
#define BUTTON_PIN 23

bool trangThaiLed = false;
// Trạng thái đọc trực tiếp ở vòng lặp trước
int trangThaiNutTruoc = HIGH;
// Trạng thái nút đã được xác nhận sau debounce
int trangThaiNut = HIGH;
// Thời điểm tín hiệu gần nhất thay đổi
unsigned long thoiGianThayDoi = 0;
// Nút phải ổn định ít nhất 50ms
const unsigned long DEBOUNCE_DELAY = 50;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {

  int trangThaiNutHienTai = digitalRead(BUTTON_PIN);
  if (trangThaiNutHienTai != trangThaiNutTruoc) {
    thoiGianThayDoi = millis(); // Số mili-giây trôi qua kể từ khi ESP32 bắt đầu chạy chương trình
  }

  if (millis() - thoiGianThayDoi >= DEBOUNCE_DELAY) {

    if (trangThaiNutHienTai != trangThaiNut) {
      trangThaiNut = trangThaiNutHienTai;

      if (trangThaiNut == LOW) {
        trangThaiLed = !trangThaiLed;
        digitalWrite(LED_PIN, trangThaiLed ? HIGH : LOW);
      }
    } 
  }

  trangThaiNutTruoc = trangThaiNutHienTai;
}