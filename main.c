#include "Dio.h"
#include "Adc.h"
#include "pwm.h"
#include "can.h"
#include "IoHwAb_Adc.h"
#include <stdio.h>
#include <unistd.h>

#define CHANNEL_DIO 0
#define CHANNEL_TEMP 1
#define CHANNEL_VOLTAGE 2
#define CHANNEL_CURRENT 3
#define CHANNEL_TORQUE 4
#define CHANNEL_RPM 5

void test_MCAL()
{
    int direction = -1, duty = 0;
    char buf[128];
    uint32_t canId = 0;
    uint8_t data[8];
    uint8_t dlc = 0;
    Dio_Init();
    Pwm_Init();
    Adc_Init();
    while (1)
    {
        //đọc từ file csv
        int temp = Adc_ReadChannel(CHANNEL_TEMP);
        int current = Adc_ReadChannel(CHANNEL_CURRENT);
        int torque = Adc_ReadChannel(CHANNEL_TORQUE);
        int rpm = Adc_ReadChannel(CHANNEL_RPM);
        int voltage = Adc_ReadChannel(CHANNEL_VOLTAGE);
        if (Can_Receive(buf, &canId, data, &dlc) == E_OK)
        {
            printf("--------------\n[CAN] CSV: %s\n", buf);
        }
        else
        {
            printf("Failed to receive CAN Frame\n");
        }
        
        //in log ra terminal
        printf("Nhiệt độ:\t%d độ c\n"
               "dòng điện:\t%d A\n"
               "điện áp:\t%d Vol\n"
               "rpm:\t\t%d rpm\n"
               "moment xoắn:\t%d N.m\n--------------\n",
               temp, current, voltage, rpm, torque);

        //ghi lên file csv
        if(duty == 5 || duty == 10 || duty == 15){
            direction = direction == 1 ? -1 : 1;    //đổi chiều quay động cơ
            Dio_WriteChannel(CHANNEL_DIO, direction);
        }

        //ghi tín hiệu pwm xuống driver 
        duty += 1;    
        Pwm_SetDutyCycle(CHANNEL_DIO, duty);
        printf("Ghi duty = %d %%\n", duty);  
        //mô phỏng tgian đọc/ghi tín hiệu từ file csv
        sleep(1);    
    }
}
void test_IoHwAb()
{
    uint16_t adc_voltage, adc_current, adc_torque, adc_count, rpm;
    float voltage_V, current_A, torque_Nm, temp_C;
    while (1)
    {
        printf("----Đọc giá trị cảm biến từ IoHwAb_Adc----\n");
        if (IoHwAb_ReadTemp(&adc_count, &temp_C) == E_OK)
        {
            printf("ADC = %u, Nhiệt độ = %.2f°C\n", adc_count, temp_C);
        }
        else
        {
            printf("Lỗi khi đọc giá trị cảm biến Temp\n");
        }
        if (IoHwAb_ReadVoltage(&adc_voltage, &voltage_V) == E_OK)
        {
            printf("Vcc = %.2f V\n", voltage_V);
        }
        else
        {
            printf("Lỗi khi đọc giá trị cảm biến voltage\n");
        }
        if (IoHwAb_ReadCurrent(&adc_current, &current_A) == E_OK)
        {
            printf("I = %.2f A\n", current_A);
        }
        else
        {
            printf("Lỗi khi đọc giá trị cảm biến current\n");
        }
        if (IoHwAb_ReadTorque(&adc_torque, &torque_Nm) == E_OK)
        {
            printf("Torque = %.2f Nm\n", torque_Nm);
        }
        else
        {
            printf("Lỗi khi đọc giá trị moment xoắn\n");
        }
        if (IoHwAb_ReadRpm(&rpm) == E_OK)
        {
            printf("RPM = %u\n", rpm);
        }
        else
        {
            printf("Lỗi khi đọc cảm biến encoder\n");
        }
        sleep(1);
    }
}

int main()
{
    test_MCAL();
    //test_IoHwAb();
    // while (1)
    // {
    //     // Loop liên tục để lấy tốc độ đặt (Mô phỏng ngắt CAN)
    //     Can_MainFunction_Read();

    //     uint16_t engineRpm;
    //     if (Com_EngineSpeed(&engineRpm) == E_OK)
    //     {
    //         printf("Tốc độ mong muốn = %u vòng/phút\n", engineRpm);
    //     }
    //     else
    //     {
    //         printf("Tốc độ không hợp lệ\n", engineRpm);
    //     }
    //     uint16_t rpm;
    //     if (IoHwAb_ReadRpm(&rpm) == E_OK)
    //     {
    //         printf("RPM = %u\n", rpm);
    //     }
    //     else
    //     {
    //         printf("Lỗi khi đọc cảm biến encoder\n");
    //     }

    //     // delay mô phỏng -> ví dụ 10ms đọc 1 lần
    // }
    return 0;
}