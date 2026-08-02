
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fa.h"

/**
 * @returns 1 is @s is among accepting states of @fa, 0 otherwise
 */
char is_accepting(struct FA *fa, state_t s);

/**
  * satisfies_fa
  * @param *fa
  * @returns 
  *   1 if str[0:len) satisfies finite automat fa,
  *   0 otherwise
  */
char satisfies_fa(struct FA *fa, char *str, int len) {
  state_t s = fa->start_state;
  for (size_t i = 0; i < len; i++) {
    s = fa->transition_func(s, str[i]);
  }

  return is_accepting(fa, s);
}

char is_accepting(struct FA *fa, state_t s) {
  for (size_t i = 0; i < fa->accepting_states_len; i++) {
    if (fa->accepting_states[i] == s) {
      return 1;
    }
  }
  return 0;
}

