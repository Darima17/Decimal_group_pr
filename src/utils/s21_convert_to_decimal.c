#include "s21_utils.h"
/*
Конвертирует расширенный decimal в обычный

Входные данные:
ext_decimal *src - указатель на переменную, которую надо конвертировать
s21_decimal *dst - указатель на переменную, в которую будет записан результат

Возвращаемые значения:
TOO_BIG - слишком большое число
OK - конвертация прошла успешно
*/
int s21_convert_to_decimal(ext_decimal *src, s21_decimal *dst) {
  int response = OK;
  response = s21_normalize_extended(src, 0);
  for (int i = 2; i >= 0; i--) {
    dst->bits[i] = src->bits[i] & INT_MASK;
  }
  dst->bits[3] = (src->scale << SCALE_BIT);
  dst->bits[3] = (src->sign << SIGN_BIT) | dst->bits[3];
  // if (response) {
  //   return response;
  // } else {
  //   return OK;
  // }
  return response;
}