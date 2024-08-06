#include "s21_decimal.h"
int s21_negate(s21_decimal value, s21_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  int sign = (value.bits[3] & SIGN_MASK) >> SIGN_BIT;
  if (sign == 0) {
    result->bits[3] = result->bits[3] | MINUS;
  } else {
    result->bits[3] = result->bits[3] & ~MINUS;
  }
  return OK;
}