#include "s21_utils.h"

/*
Приводит два ext_decimal к одинаковому scale в большую сторону
*/
void s21_set_same_scale(ext_decimal *A, ext_decimal *B) {
  ext_decimal *tmp = NULL;
  int target_scale = 0;

  if (A->scale > B->scale) {
    target_scale = A->scale;
    tmp = B;
  } else if (B->scale > A->scale) {
    target_scale = B->scale;
    tmp = A;
  }

  if (NULL != tmp) {
    s21_increase_to_certain_value(tmp, target_scale);
  }
}