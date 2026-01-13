#include "csv_io.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define DATA_BASE "./UI/data.csv"

typedef struct
{
    char *key;
    char *value;
} DataPairs;
static DataPairs *pairs = NULL;
static int total_pairs = 8;
static void skip_WhiteSpace(char *c)
{
    while (isspace(*c))
    {
        c++;
    }
}
static void Load_Csv(FILE *file)
{
    char line[50];
    for (int i = 0; i < total_pairs; i++)
    {
        fgets(line, sizeof(line), file);
        // cấp phát mem để lưu cặp key-value hiện tại
        pairs = (DataPairs *)realloc(pairs, sizeof(DataPairs) * (i + 1));
        if (pairs == NULL)
        {
            perror("cấp phát heap thất bại");
            return;
        }

        // phân tách từng trường -> realloc heap cho từng cặp key-value
        skip_WhiteSpace(line);
        // parse key
        char *token = strtok(line, ",");
        pairs[i].key = (char *)malloc(strlen(token) + 1);
        strcpy(pairs[i].key, token);

        skip_WhiteSpace(line);
        // parse value
        token = strtok(NULL, "\n");
        pairs[i].value = (char *)malloc(strlen(token) + 1);
        strcpy(pairs[i].value, token);
    }

    /* test log*/
    // for(int i = 0 ; i < total_pairs ; i++){
    //     printf("%s\t%s\n",pairs[i].key,pairs[i].value);
    // }
}
static void FreeMem()
{
    if (pairs == NULL)
    {
        return;
    }
    for (int i = 0; i < total_pairs; i++)
    {
        free(pairs[i].key);
        free(pairs[i].value);
        pairs[i].key = NULL;
        pairs[i].value = NULL;
    }
    free(pairs);
    pairs = NULL;
}
/*
 * @brief   Trả về giá trị số nguyên ứng với key (ví dụ "temp" → 512).
 * @param   key   chuỗi key cần đọc về value
 * @return  int   trả về giá trị value tương ứng với key
 */
int csv_getInt(const char *key)
{
    // đọc vê csv
    FILE *file = fopen(DATA_BASE, "r");
    if (file == NULL)
    {
        perror("Mở file thất bại");
        return -1;
    }
    // Tiến hành đọc và xử lý phân tách dữ liệu từng dòng -> lưu vào struct DataPairs
    Load_Csv(file);

    // so sánh dữ liệu trong DataPairs với key -> đọc về value tương ứng
    int value = 0;
    for (int i = 0; i < total_pairs; i++)
    {
        if (strcmp(pairs[i].key, key) == 0)
        {
            value = atoi(pairs[i].value);
            break;
        }
    }
    fclose(file);
    FreeMem();
    return value;
}
/*
 * @brief   Ghi giá trị số nguyên vào key (ví dụ: "duty", "direction").
 * @param   key   chuỗi key cần ghi value
 * @param   value giá trị số nguyên ghi vào key
 * @return  void
 */
void csv_setInt(const char *key, int value)
{
    // đọc vê csv -> lưu vào mảng
    FILE *file = fopen(DATA_BASE, "r");
    if (file == NULL)
    {
        perror("Mở file thất bại");
        return;
    }

    // xử lý phân tách dữ liệu từng dòng -> lưu vào struct DataPairs
    Load_Csv(file);

    // tìm kiếm key cần update value
    for (int i = 0; i < total_pairs; i++)
    {
        if (strcmp(pairs[i].key, key) == 0)
        {
            char temp[10];
            // copy value vào temp
            snprintf(temp, sizeof(temp), "%d", value);

            // điều chỉnh lại kích thước chuỗi value
            pairs[i].value = (char *)realloc(pairs[i].value, strlen(temp) + 1);

            // copy value mới vào mem đã điều chỉnh
            strcpy(pairs[i].value, temp);
            break;
        }
    }
    fclose(file);
    file = fopen(DATA_BASE, "w");
    if (file == NULL)
    {
        perror("Mở file thất bại");
        return;
    }

    // ghi lại csv -> ghi từng dòng
    for (int i = 0; i < total_pairs; i++)
    {
        fprintf(file, "%s,%s\n", pairs[i].key, pairs[i].value);
    }
    fclose(file);
    FreeMem();
}
/*
 * @brief   Đọc chuỗi (dùng cho CAN frame
 * @param   key         chuỗi key "can"
 * @return  const char* chuỗi CAN frame, ví dụ: "can,0x3F0 8 03 80 25 00 00 00 00 00").
 */
const char *csv_getString(const char *key)
{
    // đọc vê csv -> lưu vào mảng
    FILE *file = fopen(DATA_BASE, "r");
    if (file == NULL)
    {
        perror("Mở file thất bại");
        return NULL;
    }
    // cấp phát heap lưu dữ liệu đọc về từ csv
    pairs = (DataPairs *)malloc(sizeof(DataPairs));
    if (pairs == NULL)
    {
        perror("cấp phát heap thất bại");
        return NULL;
    }
    // xử lý phân tách dữ liệu từng dòng -> lưu vào struct DataPairs
    Load_Csv(file);

    // so sánh dữ liệu trong DataPairs với key -> đọc về value tương ứng
    for (int i = 0; i < total_pairs; i++)
    {
        if (strcmp(pairs[i].key, key) == 0)
        {
            key = pairs[i].value;
            break;
        }
    }
    fclose(file);
    FreeMem();
    return key;
}

// void csv_getChar(const char *key, char *frame_str, size_t FrameSize)
// {
//     // đọc vê csv -> lưu vào mảng
//     FILE *file = fopen(DATA_BASE, "r");
//     if (file == NULL)
//     {
//         perror("Mở file thất bại");
//         return;
//     }
//     // cấp phát heap lưu dữ liệu đọc về từ csv
//     pairs = (DataPairs *)malloc(sizeof(DataPairs));
//     if (pairs == NULL)
//     {
//         perror("cấp phát heap thất bại");
//         return;
//     }
//     // xử lý phân tách dữ liệu từng dòng -> lưu vào struct DataPairs
//     Load_Csv(file);

//     // so sánh dữ liệu trong DataPairs với key -> đọc về value tương ứng
//     for (int i = 0; i < total_pairs; i++)
//     {
//         if (strcmp(pairs[i].key, key) == 0)
//         {
//             strncpy(frame_str,pairs[i].value,FrameSize);
//             break;
//         }
//     }
//     fclose(file);
//     FreeMem();
// }