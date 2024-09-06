#include "s21_calc.h"

int parsing(const char *src, double x, operators **ListOper,
            ready **ListReady) {
  int status = src ? OK : Err;
  int len = 0;
  double number = 0.0;
  char *sym = calloc(1, 3 * sizeof(char));
  status = sym ? OK : Err;
  if (status == OK) {
    for (len = 0; src[len]; len++) {
    }
    for (int i = 0; i < len; i++) {
      if (digit_check(src[i])) {
        status = pars_digit(src, &number, len, &i);
        status = add_element_REnumber(number, ListReady);
        number = 0.0;
        if ((*ListOper) != NULL &&
            ((*ListOper)->symb[0] == '~' || (*ListOper)->symb[0] == '#')) {
          status = add_element_REoper((*ListOper)->symb, ListReady);
          status = delete_first_oper(ListOper);
        }
      } else if (operators_check(src[i])) {
        status = pars_operators(src, &sym, len, &i, ListOper, ListReady);
      } else if (src[i] == 'x') {
        status = add_element_REnumber(x, ListReady);
      }
      if (status == Err) return status;
    }
    while ((*ListOper) != NULL) {
      status = add_element_REoper((*ListOper)->symb, ListReady);
      status = delete_first_oper(ListOper);
    }
    free(sym);
  }
  return status;
}

int pars_operators(const char *src, char **sym, int len, int *st,
                   operators **ListOper, ready **ListReady) {
  int status = src ? OK : Err;
  int priority = 0;
  int flag = 0;

  for (int i = *st; operators_check(src[i]) && *st < len && !flag; ++i) {
    if (func_check(src[i])) {
      *sym[0] = src[i];
      (*sym)[1] = src[i + 1];
      priority = FUN;
      for (; src[i + 1] != '(' && !digit_check(src[i + 1]); i++) {
      }
      flag = 1;
    } else if (src[i] == '+' || src[i] == '-') {
      if (unary_check(src, i)) {
        *sym[0] = src[i] == '+' ? '#' : '~';
      } else {
        *sym[0] = src[i];
      }
      (*sym)[1] = '\0';
      priority = PLUS;
      flag = 1;
    } else if (src[i] == '*' || src[i] == '/' || src[i] == 'm') {
      *sym[0] = src[i];
      (*sym)[1] = '\0';
      priority = DELEN;
      flag = 1;
    } else if (src[i] == '^') {
      *sym[0] = src[i];
      (*sym)[1] = '\0';
      priority = STEPEN;
      flag = 1;
    } else if (src[i] == '(' || src[i] == ')') {
      *sym[0] = src[i];
      (*sym)[1] = '\0';
      priority = SKOB;
      flag = 1;
    }
    *st = i;
    status = push_oper(*sym, priority, ListReady, ListOper);
  }
  return status;
}
int push_oper(char *symb, int priority, ready **ListReady,
              operators **ListOper) {
  int status = symb ? OK : Err;
  int flag = 0;

  if (*ListOper == NULL) {
    status = add_element_oper(symb, priority, ListOper);
  } else if (priority > (*ListOper)->priority && priority != SKOB) {
    status = add_element_oper(symb, priority, ListOper);
  } else if (priority <= (*ListOper)->priority && priority != SKOB) {
    while (*ListOper != NULL && priority <= (*ListOper)->priority &&
           flag == 0) {
      if ((*ListOper)->priority == SKOB) {
        status = add_element_oper(symb, priority, ListOper);
        flag = 1;
      } else {
        status = add_element_REoper((*ListOper)->symb, ListReady);
        status = delete_first_oper(ListOper);
      }
    }
    if (flag == 0) {
      status = add_element_oper(symb, priority, ListOper);
    }
  } else if (symb[0] == '(') {
    status = add_element_oper(symb, priority, ListOper);
  } else if (symb[0] == ')') {
    while ((*ListOper)->symb[0] != '(') {
      char *symb2 = (*ListOper)->symb;
      status = add_element_REoper(symb2, ListReady);
      status = delete_first_oper(ListOper);
    }
    status = delete_first_oper(ListOper);
  }

  return status;
}

//парсинг числа
int pars_digit(const char *src, double *result, int len, int *st) {
  int status = src ? OK : Err;
  double num_dec = 0.0;
  int kol_dec = 0;
  int i = 0;

  for (i = *st; operators_check(src[i]) != 1 && *st < len; i++) {
    if (digit_check(src[i])) {
      status = pars_num(src[i], result);
    } else if (src[i] == '.') {
      for (int j = i + 1; digit_check(src[j]) == 1; j++) {
        status = pars_num(src[j], &num_dec);
        kol_dec++;
        i = j;
      }
    }
    *st = i;
  }
  *result = *result + (num_dec / pow(10, kol_dec));
  return status;
}

//парсинг цифры
int pars_num(char src, double *result) {
  int status = src ? OK : Err;
  if (*result == 0.0) {
    *result = src - '0';
  } else {
    *result = *result * 10.0 + src - '0';
  }
  status = result ? OK : Err;
  return status;
}
