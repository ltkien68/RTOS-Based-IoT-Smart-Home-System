## Development Progress

### v0.1 - Smart Light Controller 🚧
- [x] Create PlatformIO project
- [x] Configure ESP32
- [x] GPIO output
- [x] Button input
- [ ] Button debounce
- [ ] Non-blocking control

## v0.1 — GPIO Fundamentals

### 🎯 Mục tiêu

Làm quen với GPIO trên ESP32 và cách xử lý tín hiệu digital input/output trước khi chuyển sang các nội dung nâng cao hơn như sensor, interrupt và FreeRTOS.

---

### 🛠 Chức năng đã thực hiện

* Điều khiển LED bằng GPIO Output.
* Nháy LED cơ bản.
* Đọc trạng thái Push Button bằng GPIO Input.
* Sử dụng `INPUT_PULLUP` cho button.
* Điều khiển LED bằng button.
* Toggle LED:

  * Nhấn lần 1 → LED ON.
  * Nhấn lần 2 → LED OFF.
* Phát hiện cạnh nhấn `HIGH → LOW`.
* Xử lý Button Bounce bằng Software Debounce.
* Sử dụng `millis()` để đo thời gian mà không block chương trình.

---

### 📚 Kiến thức đã học

#### 1. GPIO Input / Output

Cấu hình GPIO bằng:

```cpp
pinMode(pin, OUTPUT);
pinMode(pin, INPUT);
pinMode(pin, INPUT_PULLUP);
```

Điều khiển Digital Output:

```cpp
digitalWrite(pin, HIGH);
digitalWrite(pin, LOW);
```

Đọc Digital Input:

```cpp
digitalRead(pin);
```

---

#### 2. Floating Input

Nếu GPIO được cấu hình `INPUT` nhưng không được kéo về một mức điện áp xác định, chân GPIO có thể rơi vào trạng thái **floating**.

Điều này khiến giá trị đọc được không ổn định và có thể thay đổi do nhiễu.

**Lưu ý:** Không nên để Digital Input ở trạng thái floating.

Có thể giải quyết bằng:

* Pull-up resistor.
* Pull-down resistor.
* `INPUT_PULLUP`.
* `INPUT_PULLDOWN` nếu GPIO hỗ trợ.

---

#### 3. INPUT_PULLUP

`INPUT_PULLUP` sử dụng điện trở pull-up nội bộ của ESP32.

Với button nối giữa GPIO và GND:

```text
Không nhấn → HIGH
Nhấn       → LOW
```

Do đó logic của button là **Active-Low**.

---

#### 4. Active-Low

Active-Low nghĩa là thiết bị hoặc tín hiệu được xem là **đang kích hoạt khi mức logic bằng LOW**.

Ví dụ button sử dụng `INPUT_PULLUP`:

```cpp
if (digitalRead(BUTTON_PIN) == LOW) {
    // Button đang được nhấn
}
```

**Lưu ý:** `INPUT_PULLUP` và Active-Low không phải cùng một khái niệm.

* `INPUT_PULLUP`: cách cấu hình điện cho GPIO.
* Active-Low: LOW đại diện cho trạng thái kích hoạt.

---

#### 5. Lưu trạng thái

Để chương trình nhớ trạng thái giữa các vòng `loop()`, biến trạng thái không được khai báo lại bên trong `loop()` nếu cần giữ giá trị.

Ví dụ:

```cpp
bool trangThaiLed = false;
```

Có thể đảo trạng thái bằng:

```cpp
trangThaiLed = !trangThaiLed;
```

---

#### 6. Edge Detection

Không chỉ kiểm tra button đang HIGH hay LOW mà còn có thể phát hiện **thời điểm tín hiệu thay đổi**.

Ví dụ phát hiện Falling Edge:

```text
HIGH → LOW
```

Với button Active-Low, đây có thể được sử dụng để phát hiện thời điểm button vừa được nhấn.

Ý tưởng:

```cpp
if (trangThaiNutTruoc == HIGH &&
    trangThaiNutHienTai == LOW) {

    // Button vừa được nhấn
}
```

---

#### 7. Button Bounce

Push Button là linh kiện cơ khí nên khi nhấn hoặc thả, tiếp điểm không chuyển trạng thái hoàn toàn sạch.

Một lần nhấn thực tế có thể tạo tín hiệu:

```text
HIGH → LOW → HIGH → LOW → LOW
```

ESP32 chạy rất nhanh nên có thể đọc những thay đổi này thành nhiều lần nhấn.

Hậu quả:

* LED toggle nhiều lần.
* Một lần nhấn có thể không tạo ra kết quả mong muốn.
* Trạng thái button không ổn định.

---

#### 8. Software Debounce

Software Debounce được sử dụng để loại bỏ những thay đổi nhanh do Button Bounce.

Ý tưởng:

1. Phát hiện tín hiệu button thay đổi.
2. Ghi lại thời điểm thay đổi.
3. Chờ tín hiệu giữ ổn định trong một khoảng thời gian.
4. Chỉ sau đó mới xác nhận trạng thái button.

Ví dụ khoảng debounce:

```cpp
const unsigned long DEBOUNCE_DELAY = 50;
```

Khoảng `30–50 ms` thường có thể dùng làm giá trị khởi đầu cho push button thông thường, sau đó điều chỉnh theo phần cứng thực tế.

---

#### 9. millis()

`millis()` trả về số mili-giây đã trôi qua kể từ khi ESP32 bắt đầu chạy chương trình.

Ví dụ:

```cpp
unsigned long thoiGianHienTai = millis();
```

Có thể kiểm tra thời gian đã trôi qua:

```cpp
if (millis() - thoiGianTruoc >= khoangThoiGian) {
    // Thực hiện công việc
}
```

---

#### 10. Blocking vs Non-Blocking

`delay()` làm chương trình dừng tại vị trí đó trong một khoảng thời gian.

```cpp
delay(1000);
```

Trong thời gian chờ, luồng thực thi hiện tại không tiếp tục xử lý công việc phía sau.

Với `millis()`, chương trình có thể liên tục chạy `loop()` và chỉ thực hiện hành động khi đủ thời gian.

```cpp
if (millis() - thoiGianTruoc >= 1000) {
    // Thực hiện công việc
}
```

Đây là nền tảng của **non-blocking timing**, rất hữu ích khi một hệ thống phải xử lý nhiều công việc.

---

### ⚠️ Lưu ý quan trọng

* Không để GPIO Input bị floating.
* Khi dùng `INPUT_PULLUP` với button nối GND, nhớ:

  * Không nhấn = `HIGH`.
  * Nhấn = `LOW`.
* Không nhầm `=` và `==`:

  * `=` → gán giá trị.
  * `==` → so sánh.
* Không đọc `digitalRead()` nhiều lần không cần thiết trong cùng một vòng xử lý. Có thể đọc một lần rồi lưu vào biến.
* Button cơ khí có thể bị bounce, vì vậy edge detection đơn thuần chưa chắc đủ.
* Không dùng `delay()` cho debounce nếu mục tiêu là xây dựng chương trình non-blocking.
* Với các biến thời gian từ `millis()`, nên dùng `unsigned long`.
* Nên kiểm tra khoảng thời gian theo dạng:

```cpp
millis() - thoiGianTruoc >= khoangThoiGian
```

thay vì so sánh một mốc thời gian tuyệt đối.

* Tách rõ:

  * **Raw state**: trạng thái đọc trực tiếp từ GPIO.
  * **Previous raw state**: trạng thái raw của vòng trước.
  * **Debounced state**: trạng thái đã ổn định và được chương trình xác nhận.

---

### 🧠 Tổng kết v0.1

Sau version này đã nắm được luồng xử lý Digital I/O cơ bản:

```text
GPIO Input
    ↓
Read Signal
    ↓
Detect Change
    ↓
Debounce
    ↓
Confirm State
    ↓
Process Logic
    ↓
GPIO Output
```

Đây là nền tảng để tiếp tục xây dựng các chức năng phức tạp hơn của **RTOS-Based IoT Smart Home System**.


### v0.2 - Sensor System
- [ ] DHT11
- [ ] PIR
- [ ] LDR
- [ ] OLED

### v0.3 - FreeRTOS
- [ ] Tasks
- [ ] Task priorities
- [ ] Queue
- [ ] Mutex / Semaphore

### v0.4 - IoT Connectivity
- [ ] Wi-Fi
- [ ] MQTT
- [ ] JSON communication
