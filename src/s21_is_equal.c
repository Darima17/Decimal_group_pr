#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int result = 1;
  INIT_EXTENDED(ext_num1);
  INIT_EXTENDED(ext_num2);
  s21_convert_to_ext(&num1, &ext_num1);
  s21_convert_to_ext(&num2, &ext_num2);

  if (s21_is_zero(num1) && s21_is_zero(num2)) {
    result = 1;
  } else if (ext_num1.sign != ext_num2.sign) {
    result = 0;
  } else if (ext_num1.scale > ext_num2.scale) {
    s21_increase_to_certain_value(&ext_num2, ext_num1.scale);
  } else if (ext_num1.scale < ext_num2.scale) {
    s21_increase_to_certain_value(&ext_num1, ext_num2.scale);
  }
  for (int i = 2; i > -1; i--) {
    if (ext_num1.bits[i] != ext_num2.bits[i]) result = 0;
  }
  return result;
}