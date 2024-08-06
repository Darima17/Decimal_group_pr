#include "s21_utils.h"
/*
Конвертирует decimal в расширенный decimal

Входные данные:
s21_decimal *src - указатель на переменную, которую надо конвертировать
ext_decimal *dst - указатель на переменную, в которую будет записан результат
*/
void s21_convert_to_ext(s21_decimal *src, ext_decimal *dst) {
  for (int i = 2; i >= 0; i--) {
    dst->bits[i] = src->bits[i] & INT_MASK;
  }
  dst->scale = (src->bits[3] & SCALE_MASK) >> SCALE_BIT;
  dst->sign = (src->bits[3] & SIGN_MASK) >> SIGN_BIT;
  // if (s21_is_zero(*src)) {
  //   dst->scale = 0;
  //   dst->sign = 0; так нужно для деления и умножения
  // }
}