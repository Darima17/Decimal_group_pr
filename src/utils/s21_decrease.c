#include "s21_utils.h"

uint64_t s21_decrease(ext_decimal *number) {
  uint64_t remainder = 0;
  for (int i = 6; i >= 0; i--) {
    number->bits[i] += remainder << 32;
    remainder = number->bits[i] % 10;
    number->bits[i] /= 10;
  }
  number->scale--;
  return remainder;
}