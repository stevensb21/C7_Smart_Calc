#ifndef SRC_BACK_S21_CALC_H_
#define SRC_BACK_S21_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { NUM, OPER };

enum { OK, Err, ErrInput };

enum { X, PLUS, DELEN, STEPEN, FUN, SKOB };

#define PI 3.1415926535

typedef struct operators {
  char *symb;
  int priority;
  struct operators *next;
} operators;

typedef struct ready {
  double num;
  char *symb;
  int type_t;
  struct ready *next;
} ready;

void credit_dif(double AmoCredit, int Term, double Interest, double *first,
                double *Overpayments, double *Total, double *last);
void credit_amu(double AmoCredit, int Term, double Interest,
                double *MounPayments, double *Overpayments, double *Total);

int s21_simple_calc(const char *src, double *result, double x);
int calc(ready **ListNum, double *result);
int calc_simple_oper(ready **p, ready **ListReady, int n);
int calc_unary(ready **p, ready **ListReady, int n);
int calc_func(ready **p, ready **ListReady, int n);

int add_element_REoper(char *data, ready **head);
int delete_first_oper(operators **head);
int delete_stack_oper(operators **head);
int add_element_oper(char *data, int pr, operators **head);
double get_num_ready_rm(ready **head, int n);
int delete_n_oper(ready **head, int n);
int set_num_ready(ready **head, int n, double result);

int add_element_REnumber(double data, ready **head);
int delete_first_number(ready **head);
int delete_stack_number(ready **head);

int parsing(const char *src, double x, operators **ListOper, ready **ListReady);
int pars_num(char src, double *result);
int pars_digit(const char *src, double *result, int len, int *st);
int pars_operators(const char *src, char **symb, int len, int *st,
                   operators **ListOper, ready **ListReady);
int push_oper(char *symb, int priority, ready **ListReady,
              operators **ListOper);

int digit_check(char c);
int operators_check(char c);
int func_check(char c);
int unary_check(const char *src, int i);
int operators_check(char c);
int simple_operators_check(char c);
int str_check(const char *src);
int plus_minus_check(char c);
int number_check(char *str);
int int_check(char *str);

#endif  // SRC_BACK_S21_CALC_H_
