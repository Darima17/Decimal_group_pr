#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  INIT_EXTENDED(tmp);
  s21_convert_to_ext(&value, &tmp);
  int remainder = 0;
  int prev_remainders = s21_remove_tail(&tmp, &remainder);
  if (remainder > 5) {
    tmp.bits[0]++;
  } else if (remainder == 5) {
    if (prev_remainders) {
      tmp.bits[0]++;
    } else if (tmp.bits[0] % 2 == 1) {
      tmp.bits[0]++;
    }
  }
  if (!s21_normalize_extended(&tmp, 0)) {
    s21_convert_to_decimal(&tmp, result);
    return OK;
  } else {
    return CALCULATION_ERROR;
  }
}