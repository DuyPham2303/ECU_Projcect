/***************************************************************************
 * @file    ADC_h
 * @brief   file này cung cấp các API để Mô phỏng truyền/nhận frame CAN qua chuỗi ở file csv
 * @version 1.0
 * @date    2024-09-11
 * @author  HALA Academy
 * @website https://hala.edu.vn/
 ***************************************************************************/
#ifndef CAN_H
#define CAN_H
#include <stdint.h>
typedef enum{
    E_OK,
    E_NOT_OK
}Std_ReturnType;
/*
 * @brief   Khởi tạo giao thức CAN 
 * @return  void
 */
void Can_Init(void);
/*
 * @brief   đọc can frame qua chuỗi ờ file.csv
 * details  đọc và parse key "can" trên csv
 * @param  canID ID của CAN
 * @param  data  con trỏ đến dữ liệu đọc về
 * @param  dlc   con trỏ đến 
 * @return Std_ReturnType trả về E_OK hoặc E_NOT_OK
 */
Std_ReturnType Can_Receive(uint32_t* canId, uint8_t* data, uint8_t* dlc); 

#endif // CAN_H
