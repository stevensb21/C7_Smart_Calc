#include "s21_calc.h"

int s21_simple_calc(const char *src, double *result, double x) {
  ready *ListReady = NULL;
  operators *ListOper = NULL;

  int status = 0;

  status = str_check(src);
  if (status == 2) {
    delete_stack_number(&ListReady);
    delete_stack_oper(&ListOper);
    return status;
  } else {
    status = parsing(src, x, &ListOper, &ListReady);
    status = calc(&ListReady, result);
  }

  delete_stack_number(&ListReady);
  delete_stack_oper(&ListOper);

  return status;
}

int calc(ready **ListReady, double *result) {
  int status = *ListReady ? OK : Err;
  int n = 0;
  ready *p = *ListReady;
  status = p ? OK : Err;

  while (p != NULL) {
    if (p->type_t == OPER) {
      if (func_check(*p->symb)) {
        status = calc_func(&p, ListReady, n);
        n = n - 1;
      } else if (*p->symb == '~' || *p->symb == '#') {
        status = calc_unary(&p, ListReady, n);
        n = n - 1;
      } else if (simple_operators_check(*p->symb)) {
        status = calc_simple_oper(&p, ListReady, n);
        n = n - 2;
      }
    } else {
      p = p->next;
    }
    if (status != OK) return status;
    n++;
  }
  *result = (*ListReady)->num;

  return status;
}

int calc_simple_oper(ready **p, ready **ListReady, int n) {
  int status = p ? OK : Err;
  double num1 = get_num_ready_rm(ListReady, n - 1);
  double num2 = get_num_ready_rm(ListReady, n - 2);
  long double res = 0.0;

  if (*(*p)->symb == '+') {
    res = num2 + num1;
  } else if (*(*p)->symb == '-') {
    res = num2 - num1;
  } else if (*(*p)->symb == '*') {
    res = num2 * num1;
  } else if (*(*p)->symb == '/') {
    if (num1 == 0) return ErrInput;
    res = num2 / num1;
  } else if (*(*p)->symb == '^') {
    res = pow(num2, num1);
  } else if ((*p)->symb[0] == 'm') {
    res = fmodf(num2, num1);
  }

  if (res == INFINITY) return Err;
  (*p) = (*p)->next;
  status = set_num_ready(ListReady, n - 2, res);
  status = delete_n_oper(ListReady, n - 1);
  status = delete_n_oper(ListReady, n - 1);

  return status;
}

int calc_unary(ready **p, ready **ListReady, int n) {
  int status = p ? OK : Err;
  double num = get_num_ready_rm(ListReady, n - 1);
  if (*(*p)->symb == '~') {
    num = num * (-1);
    status = set_num_ready(ListReady, n - 1, num);
  } else if (*(*p)->symb == '#') {
    if (num < 0.0) num = num * (-1);
    status = set_num_ready(ListReady, n - 1, num);
  }
  (*p) = (*p)->next;
  status = delete_n_oper(ListReady, n);

  return status;
}

int calc_func(ready **p, ready **ListReady, int n) {
  int status = p ? OK : Err;
  double num = get_num_ready_rm(ListReady, n - 1);

  if ((*p)->symb[0] == 'c' && (*p)->symb[1] == 'o') {
    num = cos(num /** (PI/180)*/);
  } else if ((*p)->symb[1] == 'i') {
    num = sin(num /** (PI/180)*/);
  } else if ((*p)->symb[1] == 'a') {
    num = tan(num /** (PI/180)*/);
  } else if ((*p)->symb[1] == 'c') {
    if (num >= 1.0 && num <= -1.0) return ErrInput;
    num = acos(num);
  } else if ((*p)->symb[1] == 's') {
    if (num >= 1.0 && num <= -1.0) return ErrInput;
    num = asin(num);
  } else if ((*p)->symb[1] == 't') {
    if (num >= 1.0 && num <= -1.0) return ErrInput;
    num = atan(num);
  } else if ((*p)->symb[1] == 'n') {
    num = log(num);
  } else if ((*p)->symb[1] == 'q') {
    num = sqrt(num);
  } else if ((*p)->symb[1] == 'o') {
    num = log10(num);
  }

  (*p) = (*p)->next;
  status = set_num_ready(ListReady, n - 1, num);
  status = delete_n_oper(ListReady, n);

  return status;
}
