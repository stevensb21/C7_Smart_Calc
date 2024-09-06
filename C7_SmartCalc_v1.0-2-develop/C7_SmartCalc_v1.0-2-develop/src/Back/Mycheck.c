#include "s21_calc.h"

int digit_check(char c) { return (c >= '0' && c <= '9') ? 1 : 0; }

int func_check(char c) {
  return (c == 'c' || c == 's' || c == 'a' || c == 'l' || c == 't') ? 1 : 0;
}

int operators_check(char c) {
  return (c == '*' || c == '/' || c == '-' || c == '+' || c == 'm' ||
          c == '^' || c == 'c' || c == 's' || c == 'a' || c == 'l' ||
          c == 't' || c == '(' || c == ')')
             ? 1
             : 0;
}

int unary_check(const char *src, int i) {
  return i == 0 || src[i - 1] == '(' ? 1 : 0;
}

int simple_operators_check(char c) {
  return (c == '*' || c == '/' || c == '-' || c == '+' || c == '^' || c == 'm')
             ? 1
             : 0;
}

int plus_minus_check(char c) { return (c == '-' || c == '+') ? 1 : 0; }

int number_check(char *str) {
  int status = str ? OK : Err;
  for (int i = 0; str[i]; i++) {
    if (!digit_check(str[i]) && str[i] != '.') status = ErrInput;
  }

  return status;
}
int int_check(char *str) {
  int status = str ? OK : Err;
  for (int i = 0; str[i]; i++) {
    if (!digit_check(str[i])) status = ErrInput;
  }

  return status;
}

int str_check(const char *src) {
  int status = src ? OK : ErrInput;
  int len = 0;
  for (len = 0; src[len]; len++) {
  }
  if (len > 256) return ErrInput;
  if (src[0] == '*' || src[0] == '/' || src[0] == '^' || src[0] == ')' ||
      src[0] == 'm')
    status = ErrInput;
  for (int i = 0; i < len; i++) {
    if (operators_check(src[i])) {
      if (simple_operators_check(src[i])) {
        if (simple_operators_check(src[i + 1]) || src[i + 1] == ')' ||
            src[i + 1] == 'm')
          status = ErrInput;
      }
      if (func_check(src[i])) {
        if (src[i] == 'c' || (src[i] == 's' && src[i + 1] == 'i') ||
            (src[i] == 'l' && src[i + 1] == 'o') || src[i] == 't') {
          if (src[i + 3] != '(') status = ErrInput;
          i += 2;
        } else if (src[i] == 'a' || (src[i] == 's' && src[i + 1] == 'q')) {
          if (src[i + 4] != '(') status = ErrInput;
          i += 3;
        } else if (src[i] == 'l' && src[i + 1] == 'n') {
          if (src[i + 2] != '(') status = ErrInput;
          i++;
        }
      } else if (src[i] == 'm') {
        if (src[i + 3] != '(' && !digit_check(src[i + 3])) status = ErrInput;
      } else if (src[i] == '(') {
        if (src[i + 1] == 'm' || src[i + 1] == '/' || src[i + 1] == '*' ||
            src[i + 1] == '^')
          status = ErrInput;
      } else if (src[i] == ')') {
        if (src[i + 1] == '(' || digit_check(src[i + 1])) status = ErrInput;
      }
    } else if (digit_check(src[i])) {
      if (src[i + 1] == '(' || func_check(src[i])) status = ErrInput;
    } else if (src[i] == '.') {
      if (digit_check(src[i + 1])) {
        int j = 0;
        for (j = i + 1; digit_check(src[j]); j++) {
        }
        if (src[j] == '.') status = ErrInput;
      } else
        status = ErrInput;
    }
  }
  return status;
}
