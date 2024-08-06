#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int response = OK;
  INIT_EXTENDED(ext1);
  INIT_EXTENDED(ext2);
  INIT_EXTENDED(ext_result);
  s21_convert_to_ext(&value_1, &ext1);
  s21_convert_to_ext(&value_2, &ext2);
  ext_result.sign = (ext1.sign + ext2.sign) % 2;
  ext_result.scale = 0;
  if (s21_is_zero(value_2)) {
    return ZERO_DIVISION;
  }
  if (s21_is_zero(value_1)) {
    s21_convert_to_decimal(&ext_result, result);
  }
  INIT_DECIMAL(copy1);
  INIT_DECIMAL(copy2);
  INIT_DECIMAL(ten);
  ext1.sign = ext2.sign = 0;
  s21_convert_to_decimal(&ext1, &copy1);
  s21_convert_to_decimal(&ext2, &copy2);
  ten.bits[0] = 10;

  // for (int i = 0; i < ext1.scale; i++) {
  //   s21_mul(copy1, ten, &copy1);
  //   s21_mul(copy2, ten, &copy2);
  // }

  while (s21_is_less_or_equal(copy2, copy1)) {
    INIT_DECIMAL(temp);
    s21_sub(copy1, copy2, &temp);
    s21_copy_decimal(&temp, &copy1);
    ext_result.bits[0]++;
  }

  for (int i = 0; i < 30; i++) {
    if (s21_is_zero(copy1)) break;
    int tail = 0;
    s21_increase(&ext_result);
    s21_mul(copy1, ten, &copy1);
    while (s21_is_less_or_equal(copy2, copy1)) {
      INIT_DECIMAL(temp);
      s21_sub(copy1, copy2, &temp);
      s21_copy_decimal(&temp, &copy1);
      tail++;
    }
    ext_result.bits[0] += tail;
  }

  response = s21_convert_to_decimal(&ext_result, result);

  return response;
}
