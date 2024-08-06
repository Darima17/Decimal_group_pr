#include "s21_decimal.h"
#include "utils/s21_utils.h"

/*
DONE
Суммирует value_1 и value_2

Входные данные:
s21_decimal value_1 - первое слагаемое
s21_decimal value_2 - второе слагаемое
s21_decimal *result - указатель на переменную, в которую будет сохранен
результат

Возвращаемые значения:
OK - операция прошла успешно
TOO_BIG - число слишком большое
TOO_SMALL - число слишком мало
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int response = OK;
  if (s21_is_zero(value_1)) {
    s21_copy_decimal(&value_2, result);
    response = OK;
  } else if (s21_is_zero(value_2)) {
    s21_copy_decimal(&value_1, result);
    response = OK;
  } else {
    INIT_EXTENDED(ext_val1);
    INIT_EXTENDED(ext_val2);
    INIT_EXTENDED(ext_result);
    s21_convert_to_ext(&value_1, &ext_val1);
    s21_convert_to_ext(&value_2, &ext_val2);
    s21_set_same_scale(&ext_val1, &ext_val2);
    ext_result.scale = ext_val1.scale;

    if (ext_val1.sign == ext_val2.sign) {
      int overflow = 0;
      for (int i = 0; i <= 6; i++) {
        ext_result.bits[i] = overflow + ext_val1.bits[i] + ext_val2.bits[i];
        overflow = s21_get_overflow(&ext_result.bits[i]);
      }
      ext_result.sign = ext_val1.sign;
      response = s21_convert_to_decimal(&ext_result, result);
      if (response == TOO_BIG && ext_result.sign == 1) {
        response = TOO_SMALL;
      }
    } else {
      if (ext_val1.sign == 1) {
        INIT_DECIMAL(negate_val1);
        INIT_DECIMAL(negate_result);
        s21_negate(value_1, &negate_val1);
        response = s21_sub(negate_val1, value_2, &negate_result);
        s21_negate(negate_result, result);
      } else {
        INIT_DECIMAL(negate_val2);
        s21_negate(value_2, &negate_val2);
        response = s21_sub(value_1, negate_val2, result);
      }
    }
  }
  return response;
}
