#include "s21_utils.h"
/*
Функция приводит расширенный decimal к определенному порядку

Входные данные:
    ext_decimal *number - указатель на расширенный decimal
    int dst_scale - целое число, в котором указан конечный порядок

Возвращаемые значения отсутствуют
*/
void s21_increase_to_certain_value(ext_decimal *number, int dst_scale) {
  int overflow = 0;
  for (int i = 0; i < 7; i++) {
    for (int j = number->scale; j < dst_scale; j++) {
      number->bits[i] *= 10;
    }
    number->bits[i] = number->bits[i] + overflow;
    overflow = s21_get_overflow(&number->bits[i]);
  }
  number->scale = dst_scale;
}