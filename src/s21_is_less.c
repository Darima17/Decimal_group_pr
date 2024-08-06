#include "s21_decimal.h"

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int response = FALSE;
  INIT_EXTENDED(ext1);
  INIT_EXTENDED(ext2);
  s21_convert_to_ext(&num1, &ext1);
  s21_convert_to_ext(&num2, &ext2);
  s21_set_same_scale(&ext1, &ext2);
  if (ext1.sign == 0) {
    if (ext2.sign == 1) {
      response = FALSE;
    } else {
      for (int i = 7; i > -1; i--) {
        if (ext1.bits[i] < ext2.bits[i]) {
          response = TRUE;
          break;
        } else if (ext1.bits[i] > ext2.bits[i]) {
          response = FALSE;
          break;
        }
      }
    }
  } else {
    if (ext2.sign == 0) {
      response = TRUE;
    } else {
      for (int i = 7; i > -1; i--) {
        if (ext1.bits[i] > ext2.bits[i]) {
          response = TRUE;
          break;
        } else if (ext1.bits[i] < ext2.bits[i]) {
          response = FALSE;
          break;
        }
      }
    }
  }
  return response;
}