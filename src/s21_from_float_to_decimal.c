#include "s21_decimal.h"
#include "utils/s21_utils.h"

typedef union {
  float f;
  unsigned int i;
  struct {
    unsigned int mntsa : 23;
    unsigned int exp : 8;
    unsigned int sign : 1;
  };
} s21_float;

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0, scale = 0;
  INIT_EXTENDED(ext_dst);
  s21_convert_to_ext(dst, &ext_dst);
  s21_nuller_ext(&ext_dst);
  if (isinf(src) || isnan(src) || (0 < fabs(src) && fabs(src) < 1e-28) ||
      (fabs(src) > 79228162514264333195497439231.0)) {
    result = 1;
  } else if (src != 0) {
    s21_float floatDigit = {0};
    floatDigit.f = src;
    if ((ext_dst.sign = floatDigit.sign)) {
      floatDigit.f = -floatDigit.f;
    }
    int expFloat = floatDigit.exp - 127;
    double dbl = floatDigit.f;
    while (scale < 28 && (int)dbl / (int)pow(2, 21) == 0) {
      dbl *= 10;
      scale++;
    }
    dbl = roundf(dbl);
    if (scale <= 28 && (expFloat > -94 && expFloat < 96)) {
      while (fmod(dbl, 10) == 0 && scale > 0) {
        dbl /= 10;
        scale--;
      }
      floatDigit.f = dbl;
      expFloat = floatDigit.exp - 127;
      s21_set_bit(&ext_dst, expFloat, 1);
      int bitFloat = 0;
      for (int mantis = 22; mantis >= 0; mantis--) {
        bitFloat = (floatDigit.i >> mantis) & 1;
        s21_set_bit(&ext_dst, --expFloat, bitFloat);
      }
      ext_dst.scale = scale;
    }
  }
  s21_convert_to_decimal(&ext_dst, dst);
  return result;
}
