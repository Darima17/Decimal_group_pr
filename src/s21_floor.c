#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int response = OK;
  INIT_EXTENDED(ext_val);
  s21_convert_to_ext(&value, &ext_val);
  if (!s21_is_zero(value)) {
    response = s21_truncate(value, result);
    if (ext_val.sign == 1) {
      INIT_DECIMAL(one);
      one.bits[0] = 1;
      response = s21_sub(*result, one, result);
    }
  } else {
    s21_copy_decimal(&value, result);
    if (ext_val.sign == 0) {
      result->bits[3] = 0;
    } else {
      result->bits[3] = MINUS;
    }
  }
  if (response != OK) response = CALCULATION_ERROR;
  return response;
}