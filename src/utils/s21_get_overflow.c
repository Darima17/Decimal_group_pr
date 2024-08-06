#include "s21_utils.h"
/*
Убирает переполнение во всех разрядах, старше 31

Входные данные:
uint64_t *number - число, в котором нужно убрать переполнение

Возвращаемые значения:
int - старшие 32 разряда исходного числа
*/
int s21_get_overflow(uint64_t *number) {
  int result = *number >> INT32_TOTAL_BITS;
  *number = *number & INT_MASK;
  return result;
}