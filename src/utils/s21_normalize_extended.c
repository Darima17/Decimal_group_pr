#include "s21_utils.h"

/*
Нормализует ext_decimal

Входные данные:
ext_decimal *A - указатель на переменную, которую нужно нормализовать
int prev_reminders - остатки от деления при предыдущих нормализациях.
Используются ТОЛЬКО для рекурсивного вызова функции. В остальных вызовах в
качестве аргумента использовать 0

Возвращаемые значения:
TOO_BIG - слишком большое значение, невозможно привести к обычному decimal
OK - Нормализация прошла успешно.
*/
int s21_normalize_extended(ext_decimal *A, int prev_reminders) {
  int reminder = 0;
  // int elder_bits = 0;

  /*
  Убираем возможные переполнения
  */
  int overflow = 0;
  for (int i = 0; i < 7; i++) {
    A->bits[i] += overflow;
    overflow = s21_get_overflow(&A->bits[i]);
  }

  /*
  Избавляемся от отрицательных степеней
  */
  while (A->scale < 0) {
    s21_increase(A);
    A->scale -= 2;
  }

  /*
  Делим на 10, пока есть что-то в старших битах и scale > 0 или пока scale
  больше MAX_SCALE
  */
  while (((A->bits[6] || A->bits[5] || A->bits[4] || A->bits[3]) &&
          A->scale > 0) ||
         A->scale > MAX_SCALE) {
    prev_reminders += reminder;
    reminder = s21_decrease(A);
  }

  /*
  Округляем
  */
  int round_flag = 0;
  if (reminder > 5) {
    A->bits[0]++;
    round_flag = 1;
  } else if (reminder == 5) {
    if (prev_reminders) {
      A->bits[0]++;
      round_flag = 1;
    } else if (A->bits[0] % 2 == 1) {
      A->bits[0]++;
      round_flag = 1;
    }
  }

  /*
  Убираем возможные переполнения после округления
  */
  overflow = 0;
  for (int i = 0; i < 4; i++) {
    A->bits[i] += overflow;
    overflow = s21_get_overflow(&A->bits[i]);
  }

  /*Если дробная часть очень мала и значимые числа не влезают в мантиссу*/
  int counter = 0;
  for (int i = 6; i >= 0; i--) {
    if (A->bits[i] != 0) counter++;
  }
  if (counter == 0 && reminder + prev_reminders != 0) return TOO_SMALL;
  /*
  Проверяем старшие биты после сдвига переполнений. Если в старших битах что-то
  есть, и scale > 0, то отменяем округление и запускаем функцию еще раз.
  */
  if (A->bits[6] || A->bits[5] || A->bits[4] || A->bits[3]) {
    if (A->scale == 0) {
      if (A->sign == 0) {
        return TOO_BIG;
      } else {
        return TOO_SMALL;
      }
    } else if (A->scale > 0) {
      A->bits[0] -= round_flag;
      prev_reminders += reminder;
      return s21_normalize_extended(A, prev_reminders);
    }
  } else {
    return OK;
  }
}
