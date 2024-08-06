#include "s21_utils.h"
/*
Функция приводит расширенный decimal на один десятичный порядок

Входные данные:
    ext_decimal *number - указатель на расширенный decimal

Возвращаемые значения отсутствуют
*/
void s21_increase(ext_decimal *number) {
  int overflow = 0;
  for (int i = 0; i < 7; i++) {
    number->bits[i] *= 10;
    number->bits[i] = number->bits[i] + overflow;
    overflow = s21_get_overflow(&number->bits[i]);
  }
  number->scale++;
}