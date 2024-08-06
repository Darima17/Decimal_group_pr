#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
  if (src < 0) {
    dst->bits[3] = dst->bits[3] | 1u << 31;
    src = (-1) * src;
  }
  if (src > INT_MAX)
    result = 1;
  else
    dst->bits[0] = src;
  return result;
}
