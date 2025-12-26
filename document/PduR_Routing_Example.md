# PduR Routing Mechanism – Downstreaming & Upstreaming

Tài liệu này bổ sung phần **giải thích trực quan (theo ví dụ đời thực)** cho cơ chế định tuyến của **PDU Router (PduR)** trong AUTOSAR Classic, nhằm giúp người học dễ hình dung vai trò của PduR trong hệ thống ECU.

---

## 1. Downstreaming (Định tuyến xuống) – Từ “Não bộ” ra “Hành động”

### Tình huống thực tế
Người lái xe nhấn **nút tăng âm lượng** trên vô lăng.

### PDU (Kiện hàng)
Một gói tin chứa lệnh:
```
Tăng âm lượng +1
```

### Quá trình xử lý

#### Lớp trên – Ứng dụng (Application / COM)
- Máy tính trung tâm của xe (Head Unit / ECU trung tâm) tạo ra một PDU chứa lệnh **“Tăng âm lượng”**.
- Ứng dụng **không quan tâm** lệnh này sẽ được gửi qua CAN hay Ethernet.

#### PduR – “Nhân viên bưu tá”
- PduR nhận PDU từ lớp trên.
- Dựa vào **bảng định tuyến (Routing Table)** đã cấu hình:
  - PduR biết rằng **hệ thống âm thanh** nằm trên **mạng Ethernet**.

#### Định tuyến xuống (Downstream Routing)
- PduR chuyển tiếp PDU xuống:
  - `Ethernet Interface`

#### Lớp dưới – Network / Hardware
- Gói tin được truyền qua Ethernet đến ECU điều khiển loa.
- Loa nhận lệnh và **âm lượng tăng lên**.

### Kết quả
- Âm thanh lớn hơn ngay lập tức.

### Ý nghĩa
PduR đảm bảo rằng:
- Lệnh từ “não bộ” được gửi **đúng nơi**
- Không bị gửi nhầm sang:
  - Hệ thống phanh
  - Hệ thống điều hòa
  - Hay ECU không liên quan

➡️ **PduR đóng vai trò quyết định luồng dữ liệu từ logic điều khiển → hành động vật lý.**

---

## 2. Upstreaming (Định tuyến lên) – Từ “Cảm biến” về “Não bộ”

### Tình huống thực tế
Cảm biến áp suất lốp phát hiện:
```
Lốp xe bị xì hơi (áp suất thấp)
```

### PDU (Kiện hàng)
Một gói tin chứa dữ liệu:
```
Áp suất = 1.5 bar (mức nguy hiểm)
```

### Quá trình xử lý

#### Lớp dưới – Cảm biến / Network (CAN)
- Cảm biến áp suất lốp gửi dữ liệu qua **CAN bus**.
- CAN là:
  - Tốc độ không cao
  - Nhưng rất bền và ổn định
  - Phù hợp cho dữ liệu an toàn

#### PduR – “Nhân viên bưu tá”
- PduR nhận PDU từ **CAN Interface**.
- Kiểm tra bảng định tuyến và xác định:
  - Thông tin này cần gửi đến:
    - **COM** (hiển thị cảnh báo)
    - **Hệ thống quản lý an toàn**

#### Định tuyến lên (Upstream Routing)
- PduR chuyển PDU lên các mô-đun lớp trên tương ứng.

#### Lớp trên – Xử lý & Hiển thị
- COM giải mã dữ liệu.
- Kích hoạt hiển thị cảnh báo.

### Kết quả
- Đèn cảnh báo màu đỏ hình lốp xe xuất hiện trên màn hình trước mặt tài xế.

### Ý nghĩa
PduR:
- Thu thập dữ liệu từ các “giác quan” (cảm biến)
- Đưa dữ liệu đó lên **đúng bộ phận xử lý cấp cao**
- Giúp hệ thống:
  - Ra quyết định
  - Cảnh báo kịp thời cho con người

➡️ **PduR là cầu nối giữa thế giới vật lý (sensor) và trí tuệ xử lý (application).**

---

## 3. Tóm tắt vai trò của PduR qua ví dụ

| Hướng định tuyến | Nguồn dữ liệu | Đích đến | Vai trò của PduR |
|------------------|--------------|----------|------------------|
| Downstreaming | Ứng dụng / COM | Ethernet / CAN / LIN IF | Gửi lệnh điều khiển đúng mạng |
| Upstreaming | Cảm biến / Bus | COM / DCM / Safety | Đưa dữ liệu cảm biến lên xử lý |

---

📌 **Ghi chú cho giảng dạy**
- Có thể ví PduR như **nhân viên bưu tá thông minh**
- Không tạo dữ liệu
- Không xử lý logic nghiệp vụ
- Chỉ **định tuyến chính xác và an toàn**
