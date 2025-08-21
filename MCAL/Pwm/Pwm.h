/***************************************************************************
 * @file    PWM_h
 * @brief   Cung cấp API để mô phỏng thay đổi tốc độ (duty cycle) của động cơ
 * @version 1.0
 * @date    2024-09-11
 * @author  HALA Academy
 * @website https://hala.edu.vn/
 ***************************************************************************/
#ifndef PWM_H
#define PWM_H

#include <stdint.h>
/*
 * @brief   Khởi tạo PWM
 * @param   key   chuỗi key cần ghi value
 * @param   value giá trị số nguyên ghi vào key
 * @return  void
 */
void Pwm_Init(void);
/*
 * @brief   Ghi giá trị duty cycle
 * details  đổi giá trị key "duty" trên csv, 
 *          ví dụ: Pwm_SetDutyCycle(0, 70); ⇒ csv_setInt("duty", 70);
 * @param   channelID   ID của chân dio
 * @param   duty        giá trị duty cycle
 * @return  void
 */
void Pwm_SetDutyCycle(uint8_t channelId, uint16_t duty);

#endif // PWM_H
