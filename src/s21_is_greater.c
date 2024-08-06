#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int is_less_or_equal = s21_is_less_or_equal(num1, num2);
  return is_less_or_equal == 0 ? 1 : 0;
}
