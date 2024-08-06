#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  int sign = (src.bits[3] & SIGN_MASK) >> SIGN_BIT;
  int scale = (src.bits[3] & SCALE_MASK) >> SCALE_BIT;
  if (src.bits[1] || src.bits[2]) {
    result = 1;
  } else {
    *dst = src.bits[0];
    if (scale > 0 && scale <= 28) {
      *dst /= pow(10, scale);
    }
  }
  if (sign) {
    *dst *= (-1);
  }
  return result;
}
