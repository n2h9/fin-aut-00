#include "re.h"
#include "fa.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct stack_node;
struct node_item;

struct node_item {
  bool is_re; /* TRUE if union contains re */
  union {
    re_t *re;
    char ch;
  };
};

struct stack_node {
  struct stack_node *next;
  struct node_item elem;
};

bool stack_is_empty(struct stack_node *stack);
struct node_item stack_top(struct stack_node *stack);
struct stack_node *stack_pop(struct stack_node *stack);
struct stack_node *stack_push(struct stack_node *stack, struct node_item item);

re_t *re_from_str(char *str, size_t len, int *err_code, int *err_indx) {
  *err_code = 0;
  *err_indx = -1;
  struct stack_node *stack;
  for (size_t i = 0; i < len; i++) {
    if (str[i] == '(') {
    } else if (str[i] == ')') {
    } else if (str[i] == '|') {
    } else if (str[i] == '*') {
    } else if (str[i] == '\\') {
    } else {
      re_t *re = re_from_symbol(str[i]);
      if (!stack_is_empty(stack)) {
        struct node_item prev = stack_top(stack);
        if (!prev.is_re) {
          if (prev.ch == '\\') {
            *err_code = ERR_UNKNOWN_ESCAPE_SEQ;
            *err_indx = i;
            break;
          } else if (prev.ch == '|') {
            stack = stack_pop(stack); // remove '|' from stack
            // expect next element to be re because '|'' requires two
            if (stack_is_empty(stack) || !stack_top(stack).is_re) {
              *err_code = ERR_INCORRECT_OPERAND;
              *err_indx = i;
              break;
            }
            prev = stack_top(stack);
            stack = stack_pop(stack);

            re_t *new_re = re_from_re(prev.re, re, RE_ALTERN);
            struct node_item new_item = {
                .is_re = true,
                .re = new_re,
            };

            stack = stack_push(stack, new_item);
          } else if (prev.ch == '(') {
            struct node_item new_item = {
                .is_re = true,
                .re = re,
            };
            stack = stack_push(stack, new_item);
          } else {
            *err_code = ERR_UNKNOWN_CONTROL_CHAR;
            *err_indx = i;
            break;
          }
        } else {
          // concatenation (prev is re)
          re_t *new_re = re_from_re(prev.re, re, RE_CONCAT);
          struct node_item new_item = {
              .is_re = true,
              .re = new_re,
          };

          stack = stack_push(stack, new_item);
        }
      } else {
        struct node_item new_item = {
            .is_re = true,
            .re = re,
        };
        stack = stack_push(stack, new_item);
      }
    }
    struct stack_node *node =
        (struct stack_node *)malloc(sizeof(struct stack_node));
  }
  // clean up stack
  while (stack != NULL) {
    struct stack_node *node = stack;
    stack = stack->next;
    node->next = NULL;
    free(node);
  }
  return NULL;
}

re_t *re_from_symbol(symbol_t s) {
  re_t *re = (re_t *)malloc(sizeof(re_t));
  re->kind = RE_SEQ;
  re->seq->size = 1;
  re->seq->str = (symbol_t *)malloc(re->seq->size);
  re->seq->str[0] = s;

  return re;
}

re_t *re_from_re(re_t *re1, re_t *re2, re_opn_enum opn_kind) {
  re_t *re = (re_t *)malloc(sizeof(re_t));
  re->kind = RE_OPN;
  re->opn->re01 = re1;
  re->opn->re02 = re2;
  re->opn->op = opn_kind;

  return re;
}

bool stack_is_empty(struct stack_node *stack) { return stack == NULL; }

struct node_item stack_top(struct stack_node *stack) { return stack->elem; }

struct stack_node *stack_pop(struct stack_node *stack) {
  struct stack_node *node = stack;
  stack = stack->next;
  node->next = NULL;
  free(node);
  return stack;
}

struct stack_node *stack_push(struct stack_node *stack, struct node_item item) {
  struct stack_node *node =
      (struct stack_node *)malloc(sizeof(struct stack_node));
  node->elem = item;
  node->next = stack;
  return node;
}
