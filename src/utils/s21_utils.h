#ifndef SRC_UTILS_S21_UTILS_H_
#define SRC_UTILS_S21_UTILS_H_

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#include "../s21_decimal.h"

/*
Расширенный decimal

uint64_t bits[7] - 7 64-х битных числа для хранения мантиссы
int scale - степень мантиссы
int sign - знак числа
*/
typedef struct {
  uint64_t bits[7];
  int scale;
  int sign;
} ext_decimal;

#define INIT_EXTENDED(X) \
  ext_decimal X = {.bits = {0, 0, 0, 0, 0, 0, 0}, .scale = 0, .sign = 0}

#define SIGN_MASK 0x80000000
#define SCALE_MASK 0x00ff0000
#define INT_MASK 0xFFFFFFFF
#define INT32_TOTAL_BITS 32

#define SCALE_BIT 16
#define SIGN_BIT 31

void s21_convert_to_ext(s21_decimal *src, ext_decimal *dst);
int s21_convert_to_decimal(ext_decimal *src, s21_decimal *dst);
int s21_get_overflow(uint64_t *number);
void s21_increase(ext_decimal *number);
uint64_t s21_decrease(ext_decimal *number);
void s21_increase_to_certain_value(ext_decimal *number, int dst_scale);
int s21_normalize_extended(ext_decimal *A, int prev_reminders);
void s21_copy_decimal(s21_decimal *src, s21_decimal *dst);
int s21_is_zero(s21_decimal src);
void s21_set_bit(ext_decimal *dst, int index, int bit);
void s21_nuller_ext(ext_decimal *num);
int s21_check_ext_zero(ext_decimal *A);
int s21_remove_tail(ext_decimal *A, int *remainder);
void s21_set_same_scale(ext_decimal *A, ext_decimal *B);
int s21_take_credit(ext_decimal *A, int pos);
#endif