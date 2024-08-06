#include "s21_decimal.h"
#include "utils/s21_utils.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 1;
  double temp = (double)*dst;
  INIT_EXTENDED(ext_src);
  s21_convert_to_ext(&src, &ext_src);
  if (dst != NULL) {
    double temp = 0;
    for (int i = 0; i < 96; i++) {
      if ((ext_src.bits[i / 32] & (1 << i % 32)) != 0) {
        temp += pow(2, i);
      }
    }
    if (ext_src.scale > 0) {
      for (int i = ext_src.scale; i > 0; i--) {
        temp /= 10.0;
      }
    }
    *dst = (float)temp;

    if (ext_src.sign) {
      *dst *= -1;
    }
    result = 0;
  }
  return result;
}
