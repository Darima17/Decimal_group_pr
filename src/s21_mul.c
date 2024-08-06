#include "s21_decimal.h"
/*
Умножение*/
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  INIT_EXTENDED(ext1);
  INIT_EXTENDED(ext2);
  INIT_EXTENDED(ext_res);
  s21_convert_to_ext(&value_1, &ext1);
  s21_convert_to_ext(&value_2, &ext2);
  ext_res.bits[0] = ext1.bits[0] * ext2.bits[0];
  ext_res.bits[1] = ext1.bits[1] * ext2.bits[0] + ext1.bits[0] * ext2.bits[1];
  ext_res.bits[2] = ext1.bits[0] * ext2.bits[2] + ext1.bits[1] * ext2.bits[1] +
                    ext1.bits[2] * ext2.bits[0];
  ext_res.bits[3] = ext1.bits[1] * ext2.bits[2] + ext1.bits[2] * ext2.bits[1];
  ext_res.bits[4] = ext1.bits[2] * ext2.bits[2];
  ext_res.scale = ext1.scale + ext2.scale;
  ext_res.sign = (ext1.sign + ext2.sign) % 2;

  return s21_convert_to_decimal(&ext_res, result);
}