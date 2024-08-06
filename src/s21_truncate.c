#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int response = OK;
  int zero = 0;
  INIT_EXTENDED(ext_val);
  s21_convert_to_ext(&value, &ext_val);
  while (ext_val.scale > 0) {
    s21_decrease(&ext_val);
  }

  if (!s21_normalize_extended(&ext_val, 0)) {
    s21_convert_to_decimal(&ext_val, result);
  } else {
    response = CALCULATION_ERROR;
  }
  return response;
}