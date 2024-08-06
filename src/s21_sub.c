#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int response = OK;
  INIT_EXTENDED(ext1);
  INIT_EXTENDED(ext2);
  INIT_EXTENDED(ext_result);
  s21_convert_to_ext(&value_1, &ext1);
  s21_convert_to_ext(&value_2, &ext2);
  s21_set_same_scale(&ext1, &ext2);
  ext_result.scale = ext1.scale;
  if (s21_is_equal(value_1, value_2)) {
    INIT_EXTENDED(ext_tmp);
    s21_set_same_scale(&ext1, &ext_tmp);
    ext_tmp.sign = ext1.sign;
    response = s21_convert_to_decimal(&ext_tmp, result);
    // INIT_DECIMAL(tmp);
    // s21_copy_decimal(&tmp, result);
  } else if (s21_is_zero(value_1)) {
    s21_negate(value_2, result);
  } else if (s21_is_zero(value_2)) {
    s21_copy_decimal(&value_1, result);
  } else {
    if (ext1.sign == 0) {
      if (ext2.sign == 0) {
        if (s21_is_greater(value_1, value_2)) {
          int credit = 0;
          for (int i = 0; i < 7; i++) {
            if (ext1.bits[i] < ext2.bits[i]) {
              s21_take_credit(&ext1, i);
            }
            ext_result.bits[i] = ext1.bits[i] - ext2.bits[i];
          }
          response = s21_convert_to_decimal(&ext_result, result);
        } else {
          INIT_DECIMAL(negate_result);
          response = s21_sub(value_2, value_1, &negate_result);
          s21_negate(negate_result, result);
        }
      } else {
        INIT_DECIMAL(negate2);
        s21_negate(value_2, &negate2);
        response = s21_add(value_1, negate2, result);
      }
    } else {
      if (ext2.sign == 0) {
        INIT_DECIMAL(negate_2);
        s21_negate(value_2, &negate_2);
        response = s21_add(value_1, negate_2, result);
      } else {
        INIT_DECIMAL(negate_1);
        INIT_DECIMAL(negate_2);
        INIT_DECIMAL(negate_result);
        s21_negate(value_1, &negate_1);
        s21_negate(value_2, &negate_2);
        response = s21_sub(negate_1, negate_2, &negate_result);
        s21_negate(negate_result, result);
      }
    }
  }
  return response;
}
/*ИСПОЛЬЗОВАТЬ ТОЛЬКО ЕСЛИ УВЕРЕН, ЧТО УМЕНЬШАЕМОЕ ЧИСЛО БОЛЬШЕ!*/
int s21_take_credit(ext_decimal *A, int pos) {
  if (pos <= 5) {
    if (A->bits[pos + 1] == 0) {
      s21_take_credit(A, pos + 1);
    }
    A->bits[pos] += 1ul << 32;
    A->bits[pos + 1]--;
    return 1;
  }
  return 0;
}
