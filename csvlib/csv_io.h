/***************************************************************************
 * @file    CSV_IO_h
 * @brief   Cung cấp API đọc/ghi file CSV dạng key-value dùng cho tất cả các module MCAL.
 * @version 1.0
 * @author  HALA Academy
 * @website https://hala.edu.vn/
 ***************************************************************************/
#ifndef CSV_IO_H
#define CSV_IO_H
#include <stddef.h>

/*
 * @brief   Trả về giá trị số nguyên ứng với key (ví dụ "temp" → 512).
 * @param   key   chuỗi key cần đọc về value
 * @return  int   trả về giá trị value tương ứng với key
 */
int csv_getInt(const char* key);
/*
 * @brief   Ghi giá trị số nguyên vào key (ví dụ: "duty", "direction").
 * @param   key   chuỗi key cần ghi value
 * @param   value giá trị số nguyên ghi vào key
 * @return  void
 */
void csv_setInt(const char* key, int value);
/*
 * @brief   Đọc chuỗi (dùng cho CAN frame, ví dụ: "can,0x3F0 8 03 80 25 00 00 00 00 00").
 * @param   key         chuỗi key 
 * @return  const char* chuỗi CAN frame
 */
const char* csv_getString(const char* key);

/*
 * @brief  Đọc chuỗi và parse vào từng byte dữ liệu tổ chức ở dạng mảng
 * @param  key   chuỗi key xác định đối tượng sẽ parse dữ liệu
 * @param  frame con trỏ tới mảng dữ liệu đã parse vào từng byte
 * @param  size_t kích thước của frame
 */
//void csv_getChar(const char* key,char* frame,size_t FrameSize);
#endif // CSV_IO_H
