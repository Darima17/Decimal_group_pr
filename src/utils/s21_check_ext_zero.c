#include "s21_utils.h"
/*
Проверяет, является ли ext_decilal нулем.

Входлные данные:
ext_decimal *A - указатель на исследуемое число

Возвращаемые значения:
1 - A == 0
0 - A != 0
*/
int s21_check_ext_zero(ext_decimal *A) {
  int flag = 0;
  for (int i = 0; i < 7; i++) {
    if (A->bits[i] != 0) {
      flag++;
    }
  }
  if (flag == 0) {
    return 1;
  } else {
    return 0;
  }
}