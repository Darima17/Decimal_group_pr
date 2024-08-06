#include "s21_utils.h"

void s21_set_bit(ext_decimal* dst, int index, int bit) {
  unsigned int i = 0;
  if ((index < 96) && (index > 63)) {
    i = 2;
    index -= 64;
  } else if ((index < 64) && (index > 31)) {
    i = 1;
    index -= 32;
  }
  unsigned int mask = 1 << index;
  if (bit) {
    dst->bits[i] |= mask;
  } else {
    mask = ~mask;
    dst->bits[i] &= mask;
  }
}

void s21_nuller_ext(ext_decimal* num) {
  for (int i = 7; i >= 0; i--) {
    num->bits[i] = 0;
  }
  num->scale = 0;
  num->sign = 0;
}