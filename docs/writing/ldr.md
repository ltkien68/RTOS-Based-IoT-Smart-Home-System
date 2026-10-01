# LDR + ADC --- Quick Notes

## 1. LDR là gì?

**LDR = Light Dependent Resistor** → quang trở.

-   Ánh sáng thay đổi → điện trở LDR thay đổi.
-   Thường: **càng sáng → điện trở LDR càng giảm**.
-   LDR không tự trả về số `0–4095`; ESP32 đọc điện áp từ mạch rồi dùng
    **ADC** để chuyển thành số.

------------------------------------------------------------------------

## 2. ADC là gì?

**ADC = Analog-to-Digital Converter**

> Chuyển tín hiệu analog liên tục → giá trị digital rời rạc.

ESP32 thường đọc ADC bằng:

``` cpp
int giaTri = analogRead(LDR_PIN);
```

Với độ phân giải 12-bit:

``` text
2^12 = 4096 mức → 0 ... 4095
```

**Lưu ý:** ADC có thể dao động/nhiễu dù ánh sáng nhìn bằng mắt gần như
không đổi.

------------------------------------------------------------------------

## 3. AO và DO trên module LDR

### AO --- Analog Output

``` text
LDR → AO → ADC ESP32 → 0...4095
```

-   Biết được **mức sáng tương đối**.
-   Có thể tự đặt nhiều ngưỡng bằng software.
-   Phù hợp Smart Light.

Ví dụ:

``` text
Sáng       → tắt hết đèn
Hơi tối    → bật 2 đèn
Tối        → bật tất cả
```

### DO --- Digital Output

``` text
LDR → LM393 comparator → DO → HIGH/LOW
```

-   **LM393 không phải ADC**, mà là comparator (bộ so sánh).
-   Biến trở trên module dùng để chỉnh ngưỡng.
-   ESP32 chỉ nhận `HIGH` hoặc `LOW`.
-   Đọc bằng:

``` cpp
digitalRead(LDR_DO_PIN);
```

### Nhớ nhanh

``` text
AO + ADC  → "Sáng bao nhiêu?"
DO + LM393 → "Đã vượt ngưỡng chưa?"
```

------------------------------------------------------------------------

## 4. Kết quả đo thực tế của project

Module đang dùng cho kết quả:

``` text
Càng sáng → ADC càng nhỏ
Càng tối  → ADC càng lớn
```

Ví dụ đã đo:

``` text
Đèn phòng bật: ~2448–2727
Đèn phòng tắt: ~3500–3760
```

Có thể thử:

``` cpp
#define NGUONG_TOI 3200
```

> Chiều tăng/giảm của ADC phụ thuộc cách mắc mạch chia áp, không được
> mặc định mọi module LDR đều giống nhau.

------------------------------------------------------------------------

## 5. Đọc LDR non-blocking

Không cần đọc/in liên tục. Có thể lấy mẫu mỗi `500 ms` bằng `millis()`.

``` text
millis()
  ↓ đủ 500 ms
đọc ADC
  ↓
cập nhật giá trị hiện tại
```

Không dùng `delay(500)` để tránh chặn button, DHT11 và các chức năng
khác.

------------------------------------------------------------------------

## 6. Lọc thay đổi nhỏ

ADC có nhiễu, nên không nên:

``` cpp
if (hienTai != truoc)
```

Có thể kiểm tra độ chênh:

``` cpp
if (abs(hienTai - truoc) >= 50)
```

`abs()` → trị tuyệt đối.

Nhớ cập nhật mốc:

``` cpp
giaTriLDRTruoc = giaTriLDRHienTai;
```

------------------------------------------------------------------------

## 7. `docDoSang()` và `layDoSang()`

``` cpp
int docDoSang() {
    return analogRead(LDR_PIN);
}
```

→ **đọc ADC thật**.

``` cpp
int layDoSang() {
    return giaTriLDRHienTai;
}
```

→ **trả giá trị gần nhất đã lưu**, không đọc ADC lần nữa.

------------------------------------------------------------------------

## 8. Tách trách nhiệm

``` text
devices/ldr       → đọc ánh sáng
devices/light     → bật/tắt đèn

services/autoLightControl
                   → LDR → quyết định → Light

main.cpp           → update devices + gọi services
```

`ldr.cpp` không nên tự `batDen()` vì sensor chỉ nên cung cấp dữ liệu.

`NGUONG_TOI` thuộc logic `autoLightControl`, không nhất thiết thuộc LDR.

------------------------------------------------------------------------

## 9. `#pragma once`

Header có thể viết ngắn:

``` cpp
#pragma once

void manualLightControl();
```

Thay cho:

``` cpp
#ifndef MANUALLIGHTCONTROL_H
#define MANUALLIGHTCONTROL_H

void manualLightControl();

#endif
```

Mục đích: **ngăn một header bị include nhiều lần trong cùng translation
unit**.

------------------------------------------------------------------------

## 10. Nhớ nhanh cả buổi

``` text
LDR = quang trở
ADC = Analog → Digital
AO = giá trị analog → analogRead()
DO = HIGH/LOW → digitalRead()
LM393 = comparator, KHÔNG phải ADC

Sáng/tối thực tế → đo trước → mới chọn threshold
ADC có nhiễu → không so sánh bằng ==
millis() → đọc sensor theo chu kỳ mà không blocking

Device = đọc/điều khiển phần cứng
Service = logic phối hợp các device

#pragma once = chống include header lặp
```
