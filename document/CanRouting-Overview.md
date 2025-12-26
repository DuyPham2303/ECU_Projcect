# CAN Data Routing Flow (AUTOSAR Communication Stack)

## 1. Giới thiệu

Tài liệu này mô tả **luồng điều phối dữ liệu CAN (CAN Routing Flow)** trong hệ thống ECU theo kiến trúc **AUTOSAR Classic**.  
Mục tiêu là làm rõ cách một thông điệp CAN được:
- Nhận từ bus vật lý
- Giải mã (decode)
- Đóng gói theo chuẩn PDU
- Điều phối đến đúng mô-đun chức năng để xử lý

Nội dung phù hợp cho:
- Giảng dạy Communication Stack
- Phân tích luồng dữ liệu CAN trong ECU
- Hiểu vai trò của CAN Driver, CanIf, PduR, COM, DCM

---

## 2. Vấn đề cần giải quyết trong giao tiếp CAN

### 2.1 Giải mã thông điệp CAN

Khi một ECU nhận được CAN message:
- Message cần được **decode** để trích xuất:
  - CAN ID
  - Payload (ví dụ: tốc độ xe, trạng thái động cơ, tín hiệu cảm biến)
- Mỗi ECU chỉ quan tâm đến **một tập CAN ID cụ thể**

### 2.2 Xử lý đồng thời trên bus CAN

Trên bus CAN:
- Nhiều ECU có thể gửi message cùng lúc
- CAN sử dụng **cơ chế phân xử (arbitration)**:
  - Message có CAN ID nhỏ hơn sẽ có độ ưu tiên cao hơn
  - Được truyền trước trên bus

---

## 3. Bối cảnh hệ thống

Trong hệ thống xe hơi:
- Nhiều giao thức truyền thông cùng tồn tại:
  - CAN
  - LIN
  - FlexRay
- ECU khi nhận dữ liệu cần:
  - Xác định **protocol nguồn**
  - Gọi đúng hàm xử lý và decode tương ứng

### 3.1 Cơ chế Interrupt

- Việc truyền/nhận dữ liệu sử dụng **Interrupt**
- ECU chỉ xử lý khi:
  - Có dữ liệu mới
  - Tránh polling liên tục gây lãng phí CPU

---

## 4. Quy trình điều phối dữ liệu CAN

### 4.1 Đọc dữ liệu từ bus (Lower Layer)

- Sau mỗi chu kỳ T (ví dụ 1s):
  - Các task đọc dữ liệu được kích hoạt độc lập
  - Ví dụ:
    - `Can_ReadMainFunction()`
    - `Lin_ReadMainFunction()`
    - `FlexRay_ReadMainFunction()`

Các task này thường chạy trong:
- OS Task
- Hoặc thread riêng (tuỳ kiến trúc)

---

### 4.2 Đóng gói dữ liệu (PDU Abstraction)

#### Vai trò của PduR

- `PduR` đóng vai trò:
  - Chuẩn hóa dữ liệu nhận được từ các protocol khác nhau
  - Đóng gói dữ liệu thành **PDU (Protocol Data Unit)**

Quy trình:
1. Dữ liệu đã được xử lý sơ bộ bởi:
   - `CanIf`
   - `LinIf`
   - `FlexRayIf`
2. PduR:
   - Lưu trữ dữ liệu dưới dạng PDU tổng quát
   - Chuyển lên tầng trên mà **không phụ thuộc protocol vật lý**

---

### 4.3 Xử lý tại CanIf

- `CanIf`:
  - Nhận dữ liệu CAN frame
  - Gọi callback:
    - `Rx_Indication()`
- Hàm này dùng để:
  - Thông báo có dữ liệu mới
  - Kích hoạt luồng xử lý tiếp theo

---

### 4.4 Rx Indication và ánh xạ module đích

Trong `Rx_Indication`:
- Xác định:
  - **Source Protocol** (CAN, LIN, FlexRay)
  - **Destination Module** (module sẽ xử lý dữ liệu)

#### Các module đích phổ biến

- **COM**
  - Điều khiển trạng thái xe:
    - Set tốc độ
    - Dừng động cơ
    - Xi nhan
    - Đọc dữ liệu cảm biến

- **DCM**
  - Chuẩn đoán lỗi
  - Gửi phản hồi trạng thái lỗi (Diagnostic Response)

- **FIM**
  - Kiểm tra điều kiện cho phép thực thi lệnh
  - Đảm bảo an toàn và logic hệ thống

> Lưu ý:  
> Mỗi chức năng cụ thể được phân biệt thông qua **CAN ID** hoặc **Signal ID**.

---

### 4.5 Điều phối đến module chức năng

- `PduR_Indication()` được gọi để:
  - Điều hướng PDU đến module đích
- Ví dụ:
  - `Com_Indication()`

Tại COM:
- Decode CAN ID
- Xác định chức năng cụ thể:
  - Set speed → decode value → cập nhật trạng thái
  - Stop motor → cập nhật trạng thái động cơ

---

## 5. Tóm tắt luồng gửi và nhận dữ liệu CAN

### 5.1 Luồng gửi (Transmit Path)

```
Application
   ↓
RTE
   ↓
COM
   ↓
PduR
   ↓
CanIf
   ↓
CAN Driver
   ↓
CAN Bus
```

### 5.2 Luồng nhận (Receive Path)

```
CAN Bus
   ↓
CAN Driver
   ↓
CanIf (Rx_Indication)
   ↓
PduR
   ↓
COM / DCM / FIM
   ↓
Application
```

---

## 6. Tổng kết

Luồng điều phối dữ liệu CAN trong AUTOSAR đảm bảo:
- Phân tách rõ ràng giữa phần cứng và ứng dụng
- Hỗ trợ nhiều protocol truyền thông
- Dễ mở rộng và bảo trì
- Đáp ứng yêu cầu an toàn và thời gian thực của hệ thống xe

---

📌 Tài liệu phù hợp cho:
- Sinh viên / kỹ sư học AUTOSAR
- Phân tích Communication Stack
- Làm tài liệu README cho repository Automotive / Embedded
