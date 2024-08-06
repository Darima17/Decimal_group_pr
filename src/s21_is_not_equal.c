#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return (!s21_is_equal(num1, num2));
}
