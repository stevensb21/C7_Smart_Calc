#include <check.h>
#include <math.h>
#include <string.h>

#include "../Back/s21_calc.h"

START_TEST(calculate_1) {
  char *infix = "cos(sin(tan(0.5)))";
  double result;
  s21_simple_calc(infix, &result, 0);
  double exp_result = 0.86805191;
  ck_assert_double_eq_tol(result, exp_result, 7);
}

START_TEST(calculate_2) {
  char *infix = "-8/(2+3)*(7-2)+6";
  double result;
  s21_simple_calc(infix, &result, 0);
  double exp_result = -2.00000001;
  ck_assert_double_eq_tol(result, exp_result, 7);
}

START_TEST(calculate_3) {
  char *infix = "(10.5-2.2)*(4.8+2.3)-1.7/3";
  double result = 0.0;
  s21_simple_calc(infix, &result, 0);
  double exp_result = 58.3630000;
  ck_assert_double_eq_tol(result, exp_result, 7);
}

START_TEST(calculate_4) {
  char *infix =
      "((5.5^3 + 3^2) * (2.7^2 - 6^3)) / (2^4 + 10^2) * (4.2^5 - 1.2^6)";
  double result;
  s21_simple_calc(infix, &result, 0);
  double exp_result = -411439.52501933;
  ck_assert_double_eq_tol(result, exp_result, 7);
}

START_TEST(calculate_5) {
  char *infix = "sqrt(16)+ln(1)*log(10)/sqrt(25)";
  double result;
  s21_simple_calc(infix, &result, 0);
  double exp_result = 4;
  ck_assert_double_eq_tol(result, exp_result, 7);
}

START_TEST(calculate_6) {
  char *infix = "(sqrt(16)+sin(1)*cos(2)/"
                "tan(0.5)-asin(0.5)^acos(0.3)mod2*atan(0.8)*ln(2)*log(100))/"
                "cos(sin(tan(0.5)))";
  double result;
  s21_simple_calc(infix, &result, 0);
  double exp_result = 2.7801183;
  ck_assert_double_eq_tol(result, exp_result, 7);
}

START_TEST(calculate_7) {
  char *infix = "(4.3.4+54.23)";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0);
  ck_assert_int_eq(2, exit_status);
}

START_TEST(calculate_8) {
  char *infix =
      "(4 + sin(x) * cos(2) / 0 - asin(x)^acos(0.3) mod 2 * atan(x) * "
      "ln(2) * log10(100)) / cos(sin(tan(x)))";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0.49879);
  ck_assert_int_eq(2, exit_status);
}

START_TEST(calculate_9) {
  char *infix =
      "(4 + sin(x) * cohs(2) / tan(0.5)) - asin(x)^acos(((0.3) mod 2 * "
      "atan(x) * ln(2) * log10(100)) / cos(sin(tan(x)))";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0.49879);
  ck_assert_int_eq(2, exit_status);
}

START_TEST(calculate_10) {
  char *infix = "((10.5-2.2)*(4.8+2.3)-1.7/3)^9";
  double result;
  s21_simple_calc(infix, &result, 0);
  result = (long double)result;
  long double exp_result = 7857073069077921;
  ck_assert_double_eq(result, exp_result);
}
START_TEST(calculate_11) {
  char *infix = "(arccos(4)+54.23)";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0.49879);
  ck_assert_int_eq(2, exit_status);
}

START_TEST(calculate_12) {
  char *infix = "/54.23+7";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0.49879);
  ck_assert_int_eq(2, exit_status);
}

START_TEST(calculate_13) {
  char *infix = "*54.23+5";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0.49879);
  ck_assert_int_eq(2, exit_status);
}

START_TEST(calculate_14) {
  char *infix = ".54.23+3";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0.49879);
  ck_assert_int_eq(2, exit_status);
}

START_TEST(calculate_15) {
  char *infix = "54.23++3";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0.49879);
  ck_assert_int_eq(2, exit_status);
}

START_TEST(calculate_16) {
  char *infix = "54./23+3";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0.49879);
  ck_assert_int_eq(2, exit_status);
}
START_TEST(calculate_17) {
  char *infix = "54(/23)+3";
  double result;
  int exit_status = s21_simple_calc(infix, &result, 0.49879);
  ck_assert_int_eq(2, exit_status);
}

START_TEST(calculate_18) {
  char *infix = "10mod4-(+5)";
  double result;
  s21_simple_calc(infix, &result, 0.49879);
  double exp_result = -3.00000001;
  ck_assert_double_eq_tol(result, exp_result, 7);
}

START_TEST(calculate_credit_1) {
  double MounPayments = 0.0;
  double Overpayment = 0.0;
  double Total = 0.0;
  credit_amu(1000000, 13, 23.13, &MounPayments, &Overpayment, &Total);

  ck_assert_double_eq_tol(87697.81, MounPayments, 2);
  ck_assert_double_eq_tol(140072, Overpayment, 2);
  ck_assert_double_eq_tol(1140071.55, Total, 2);
}

START_TEST(calculate_credit_2) {
  double MounPayments = 0.0;
  double Overpayment = 0.0;
  double Total = 0.0;
  double last = 0.0;
  credit_dif(1000000, 13, 23.13, &MounPayments, &Overpayment, &Total, &last);

  ck_assert_double_eq_tol(96198.1, MounPayments, 2);
  ck_assert_double_eq_tol(134925.00, Overpayment, 2);
  ck_assert_double_eq_tol(1134925.00, Total, 2);
  ck_assert_double_eq_tol(78405.77, last, 2);
}

START_TEST(number_check_1) {
  char *str = "-1000";
  int status = 0;
  int statusPlMI = 0;
  status = number_check(str);
  statusPlMI = plus_minus_check(str[0]);

  ck_assert_int_eq(2, status);
  ck_assert_int_eq(1, statusPlMI);
}

START_TEST(int_check_1) {
  char *str = "10.43";
  int status = 0;
  status = int_check(str);

  ck_assert_int_eq(2, status);
}

int main(void) {
  Suite *s = suite_create("SmartCalc");
  TCase *smart_calc = tcase_create("smart_calc");
  SRunner *sr = srunner_create(s);

  int count_failed;
  suite_add_tcase(s, smart_calc);

  tcase_add_test(smart_calc, calculate_1);
  tcase_add_test(smart_calc, calculate_2);
  tcase_add_test(smart_calc, calculate_3);
  tcase_add_test(smart_calc, calculate_4);
  tcase_add_test(smart_calc, calculate_5);
  tcase_add_test(smart_calc, calculate_6);
  tcase_add_test(smart_calc, calculate_7);
  tcase_add_test(smart_calc, calculate_8);
  tcase_add_test(smart_calc, calculate_9);
  tcase_add_test(smart_calc, calculate_10);
  tcase_add_test(smart_calc, calculate_11);
  tcase_add_test(smart_calc, calculate_12);
  tcase_add_test(smart_calc, calculate_13);
  tcase_add_test(smart_calc, calculate_14);
  tcase_add_test(smart_calc, calculate_15);
  tcase_add_test(smart_calc, calculate_16);
  tcase_add_test(smart_calc, calculate_17);
  tcase_add_test(smart_calc, calculate_18);
  tcase_add_test(smart_calc, calculate_credit_1);
  tcase_add_test(smart_calc, calculate_credit_2);
  tcase_add_test(smart_calc, number_check_1);
  tcase_add_test(smart_calc, int_check_1);

  srunner_run_all(sr, CK_VERBOSE);
  count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (count_failed == 0) ? 0 : 1;
}
