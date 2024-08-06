#include "s21_utils.h"

/*
Удаляет всю дрлбныю часть в ext_decimal

Входные данные:
ext_decimal *A - указатель на изменяемый ext_decimal
int *remainder - указатель на переменную, куда будет возвращет последний остаток

Возвращаемые значения:
0 - предыдущих остатков от деления не было
!0 - были
*/
int s21_remove_tail(ext_decimal *A, int *remainder) {
  int prev_reminders = 0;
  while (A->scale > 0) {
    prev_reminders += *remainder;
    *remainder = s21_decrease(A);
  }
  return prev_reminders;
}