#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

typedef struct {
  int bits[4];
} s21_decimal;

#include <math.h>

#include "utils/s21_utils.h"

#define INIT_DECIMAL(X) s21_decimal X = {.bits = {0, 0, 0, 0}}

#define OK 0
#define TOO_BIG 1
#define TOO_SMALL 2
#define ZERO_DIVISION 3
#define FALSE 0
#define TRUE 1
#define CONVERTATION_ERROR 1
#define CALCULATION_ERROR 1

#define MAX_SCALE 28
#define MAX_UINT 4294967296
#define MINUS 0b10000000000000000000000000000000

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
/*
Функции возвращают код ошибки:

0 - OK
1 - число слишком велико или равно бесконечности
2 - число слишком мало или равно отрицательной бесконечности
3 - деление на 0
*/

int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);      //+
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);  //+
/*
Возвращаемое значение:

0 - FALSE
1 - TRUE
*/

int s21_from_int_to_decimal(int src, s21_decimal *dst);  //+
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
/*Возвращаемое значение - код ошибки:

0 - OK
1 - ошибка конвертации
*/

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);  //+
/*
Возвращаемое значение - код ошибки:

0 - OK
1 - ошибка вычисления
*/
#endif