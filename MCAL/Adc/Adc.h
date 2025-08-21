/***************************************************************************
 * @file    ADC_h
 * @brief   file này cung cấp các API để Mô phỏng đọc các tín hiệu analog từ cảm biến
 * @version 1.0
 * @date    2024-09-11
 * @author  HALA Academy
 * @website https://hala.edu.vn/
 ***************************************************************************/
#ifndef ADC_H
#define ADC_H
#include <stdint.h>
/*
 * @brief   Khởi tạo ADC để đọc dữ liệu của các cảm biến
 * @return  void
 */
void Adc_Init(void);
/*
 * @brief   đọc giá trị ADC từ cảm biến
 * details  dùng để  Đọc giá trị từ các key input ("temp", "voltage", "current", "torque", "rpm") trên csv.
 *          Ví dụ: uint16 rpm = Adc_ReadChannel(4); sẽ đọc từ key "rpm"
 *          ⇒ csv_setInt("direction", 1);
 * @param   channelID   ID của channel cần đọc dữ liệu
 * @return  uint16_t    giá trị adc thô từ cảm biến trả về
 */
uint16_t Adc_ReadChannel(uint8_t channelId); 

#endif // ADC_H
