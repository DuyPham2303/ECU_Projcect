Nội dung chính Giai đoạn 2
- Giải thích phần giao diện UI
- Giải thích lý thuyết phần IoHwAb, Can routing, và PdU 
- Giải thích demo code 
Luồng diễn giải 
- **Trình bày giải thích lại mục tiêu dự án** 
    + UI -> build server giao tiếp giữa code + giao diện mô phỏng
    + UI mô phỏng bằng cách nào -> thông số thực tế + công thức vật lý -> mô phỏng hành vi động cơ
    + Mục tiêu : 
        - thiết lập công thức + logic điều khiển output speed  
        - Duy trì ổn định động cơ bằng cách kiểm soát momen,tải,nhiệt độ,dòng,áp 
- **Cách thức sử dụng UI ?**
    + thay đổi setpoint qua UI bar hoặc terminal
    + chiều quay động cơ có thể nhận qua byte thứ 3 sau tốc độ, và lệnh set speed từ can frame 
- **Mô tả sơ lược phản hời từ động cơ**
    + giới hạn tốc độ lớn nhất set được ? -> output speed và rpm không tải max ? giải thích công thức mô phỏng sơ lược -> file script.js
- **Giải thích phần IoHwAb và demo code**
    + trình bày phàn code -> đã bổ sung phần testing 
    + Chạy thử kết hợp UI -> Đưa ra nhận xét mà bắt đầu kết hợp mcal + IoHwAb
    + mục tiêu của mcal -> chỉ cần đọc về raw data từ csv (mô phỏng hardware) -> chưa phải data thực tế 
    + Mục tiêu của IoHwAb ? -> trừu tượng phần xử lý raw data -> convert về đơn vị vật lý 
    + Trình bày theo slide + tài liệu hướng dẫn quy trình triển khai
- **Giải thích Can và pdu router**
    + Trình bày muc tiêu trong slide -> dẫn dắt từ vấn đề các xử lý đọc về CAN FRAME để bóc tách setpoinr,direction,set speed cmd 
    + Trình bày về COM Stack 
    -> Sơ lược về ý nghĩa và vai trò của pdu trong automotive network protocol
    -> trình bày luồng xử lý can routing 
    -> Tóm tắt lại các ý chính qua file md
- **Triển khai code mô tả CAN routing**
    + Giải thích code theo tài liệu hướng dẫn
    + Hẹn giải thích routing table ở phần lý thuyết autosar
