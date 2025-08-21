/***************************************************************************
 * @file    CSV_IO_h
 * @brief   Cung cấp API đọc/ghi file CSV dạng key-value dùng cho tất cả các module MCAL.
 * @version 1.0
 * @date    2024-09-11
 * @author  HALA Academy
 * @website https://hala.edu.vn/
 ***************************************************************************/
#ifndef DIO_H
#define DIO_H
#include <stdint.h>

/*
 * @brief   Khởi tạo các chân I/O
 * details  Khởi tạo các channel điều khiển digital (có thể chỉ in log).
 * @return  void
 */
void Dio_Init(void);
/*
 * @brief   Ghi mức điện áp ra các chân I/O
 * details  dùng để đối chiều quay motor, ví dụ
 *          gọi Dio_WriteChannel(0, 1); // 1 là thuận, 0 là nghịch 
 *          ⇒ csv_setInt("direction", 1);
 * @param   channelID   giá trị các chân I/O 
 * @param   level       mức điện áp xuất ra là 1 hoặc 0
 * @return  void
 */
void Dio_WriteChannel(uint8_t channelId, uint8_t level);


#endif // DIO_H
