#include "s21_utils.h"

void s21_normalize_decimal(s21_decimal *A) {
  while ((A->bits[0] % 10 == 0) &&
         ((A->bits[3] & SCALE_MASK) >> SCALE_BIT) > 0) {
  }
}