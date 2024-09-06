#include "s21_calc.h"

/*----------Stack for number-----------*/

int add_element_REnumber(double data, ready **head) {
  int status = head ? OK : Err;
  if (status == OK) {
    ready *next_op = calloc(1, sizeof(ready));
    status = next_op ? OK : Err;

    if (status == OK) {
      next_op->num = data;
      next_op->type_t = 0;
      next_op->next = NULL;

      if ((*head) == NULL) {
        *head = next_op;
      } else {
        ready *p = *head;
        while (p->next != NULL) p = p->next;
        p->next = next_op;
      }
    }
  }
  return status;
}

double get_num_ready_rm(ready **head, int n) {
  int status = head ? OK : Err;
  double result;
  ready *p = *head;
  int count = 0;

  if (status == 0) {
    while (count != n && p->next != NULL) {
      // tmp = p;
      p = p->next;
      count++;
    }
    status = p ? OK : Err;
    result = p->num;
  }

  return result;
}

int set_num_ready(ready **head, int n, double result) {
  int status = head ? OK : Err;
  ready *p = *head;
  int count = 0;

  if (status == 0) {
    while (count != n && p->next != NULL) {
      p = p->next;
      count++;
    }
    status = p ? OK : Err;
    p->num = result;
  }

  return status;
}

int delete_n_oper(ready **head, int n) {
  int status = head ? OK : Err;

  if (status == OK) {
    ready *p = *head;
    ready *tmp = NULL;
    int count = 0;
    while (count != n && p->next != NULL) {
      tmp = p;
      p = p->next;
      count++;
    }
    status = p ? OK : Err;
    if (p == (*head)) {
      status = delete_first_number(head);
    } else {
      tmp->next = p->next;
      free(p->symb);
      free(p);
    }
  }
  return status;
}

int delete_first_number(ready **head) {
  int status = head ? OK : Err;

  if (*head) {
    ready *temp = *head;
    *head = (*head)->next;

    free(temp->symb);
    free(temp);
  }

  return status;
}

int delete_stack_number(ready **head) {
  int status = head ? OK : Err;
  while (*head) {
    status = delete_first_number(head);
  }
  return status;
}

/*----------Stack for operators-----------*/

int add_element_oper(char *data, int pr, operators **head) {
  int status = head ? OK : Err;
  char *symb = calloc(1, 3 * sizeof(char));
  strcpy(symb, data);
  // status = symb ? OK: Err;
  if (status == OK) {
    operators *next_op = (operators *)malloc(sizeof(operators));
    status = next_op ? OK : Err;
    if (status == OK) {
      next_op->symb = symb;
      next_op->priority = pr;
      next_op->next = *head;
      (*head) = next_op;
    }
  }
  return status;
}

int add_element_REoper(char *data, ready **head) {
  int status = 0;
  char *sym2 = calloc(1, 3 * sizeof(char));
  strcpy(sym2, data);
  ready *next_op = calloc(1, sizeof(ready));
  status = next_op ? OK : Err;
  if (status == OK) {
    status = next_op ? OK : Err;

    if (status == OK) {
      next_op->symb = sym2;
      next_op->type_t = 1;
      next_op->next = NULL;

      if ((*head) == NULL) {
        *head = next_op;
      } else {
        ready *p = *head;
        while (p->next != NULL) p = p->next;
        p->next = next_op;
      }
    }
  }
  return 0;
}

int delete_first_oper(operators **head) {
  int status = head ? OK : Err;

  if (*head) {
    operators *temp = *head;
    *head = (*head)->next;

    free(temp->symb);
    free(temp);
  }

  return status;
}

int delete_stack_oper(operators **head) {
  int status = head ? OK : Err;
  while (*head) {
    status = delete_first_oper(head);
  }
  return status;
}
