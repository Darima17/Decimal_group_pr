#include "s21_utils.h"

/*
Копирует s21_decimal src в dst

Входные данные:
s21_decimal *src - указатель на исходный s21_decimal
s21_decimal *dst - указатель на s21_decimal, в который копируются данные
*/
void s21_copy_decimal(s21_decimal *src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src->bits[i];
  }
}