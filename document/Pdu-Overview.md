# AUTOSAR PDU Router (PduR)

## 1. Giới thiệu

Trong AUTOSAR Classic Platform, **PDU Router (PduR)** là một mô-đun cốt lõi thuộc **Communication Stack**, đóng vai trò như một **bộ định tuyến dữ liệu**.  
Nhiệm vụ chính của PduR là **chuyển tiếp các Protocol Data Unit (PDU)** giữa các mô-đun giao tiếp khác nhau, cả ở phía trên và phía dưới của ngăn xếp truyền thông.

PduR giúp hệ thống:
- Giảm sự phụ thuộc giữa các mô-đun
- Tăng khả năng tái sử dụng phần mềm
- Hỗ trợ gateway giữa nhiều bus truyền thông trong xe

---

## 2. Vai trò của PDU trong AUTOSAR

### 2.1 Trừu tượng hóa tín hiệu
PDU giúp ẩn chi tiết công nghệ truyền dẫn, cho phép ứng dụng làm việc với dữ liệu logic mà không cần biết dữ liệu được truyền qua CAN, LIN hay Ethernet.

### 2.2 Độc lập với công nghệ truyền thông
Một PDU có thể được truyền qua nhiều công nghệ mạng khác nhau như CAN/CAN FD, LIN, FlexRay hoặc Automotive Ethernet mà không cần thay đổi cấu trúc.

### 2.3 Tích hợp và đóng gói tín hiệu
Nhiều tín hiệu từ các nguồn khác nhau có thể được gom lại vào một PDU khi truyền và được giải nén ở phía nhận.

---

## 3. Chức năng chính của PduR

### 3.1 Định tuyến PDU
Chuyển tiếp PDU đến đúng mô-đun đích dựa trên PDU ID và bảng định tuyến đã được cấu hình.

### 3.2 Gateway giữa các bus
Cho phép truyền dữ liệu giữa các giao thức khác nhau, ví dụ CAN ↔ LIN hoặc CAN ↔ Ethernet.

### 3.3 Trừu tượng hóa giao tiếp
Các mô-đun lớp trên như COM hoặc DCM không phụ thuộc vào công nghệ truyền thông cụ thể.

---

## 4. Cơ chế hoạt động

PduR hoạt động như lớp trung gian giữa:
- Lớp trên: COM, DCM
- Lớp dưới: CAN IF, LIN IF, CAN TP, FlexRay IF

### 4.1 Upstream Routing
PDU nhận từ lớp dưới sẽ được định tuyến lên mô-đun lớp trên phù hợp.

### 4.2 Downstream Routing
PDU từ lớp trên được định tuyến xuống mô-đun lớp dưới tương ứng.

---

## 5. Các loại PDU

### 5.1 I-PDU
Chứa dữ liệu ứng dụng (signal), được xử lý bởi mô-đun COM.

### 5.2 N-PDU
Được sử dụng trong Transport Protocol (ví dụ CAN TP) để truyền dữ liệu kích thước lớn.

### 5.3 L-PDU
Dùng cho các mô-đun giao diện phần cứng như CAN IF, LIN IF.

---

## 6. Vai trò trong giao tiếp liên ECU

### 6.1 Nội bộ ECU
Định tuyến dữ liệu giữa các mô-đun trong cùng ECU.

### 6.2 Giữa các ECU
Đóng vai trò trung tâm của ECU Gateway, cho phép chuyển tiếp dữ liệu giữa các bus khác nhau.

---

## 7. Mối quan hệ giữa COM và PDU

### 7.1 Đóng gói / Giải nén
COM đóng gói signal thành I-PDU khi truyền và giải nén khi nhận.

### 7.2 Khởi tạo
Trong Com_Init, các PDU và signal được khởi tạo với giá trị cấu hình.

### 7.3 Lọc tín hiệu
COM có thể áp dụng bộ lọc để loại bỏ signal không cần thiết, giảm tải xử lý.

---

## 8. Tổng kết

PduR là mô-đun trung tâm của Communication Stack trong AUTOSAR Classic, đảm bảo khả năng định tuyến linh hoạt, hỗ trợ gateway đa bus và tăng tính tái sử dụng phần mềm.

---
