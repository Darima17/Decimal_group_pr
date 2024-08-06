#include "s21_utils.h"

/*
Проверяет на ноль

result = 1 ноль
result = 0 число не ноль
*/
int s21_is_zero(s21_decimal src) {
  int result = 1;
  for (int i = 0; i < 3; i++) {
    if (src.bits[i] != 0) {
      result = 0;
    }
  }
  return result;
}