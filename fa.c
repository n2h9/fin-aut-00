
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fa.h"

state_t transition_func(fa_t *fa, state_t from, symbol_t s) {
  // TODO check state is within the bound of transition table size
  return fa->transition_table[from][s];
}

/**
 * @returns 1 is @s is among accepting states of @fa, 0 otherwise
 */
char is_accepting(fa_t *fa, state_t s);

/**
  * satisfies_fa
  * @param *fa
  * @returns
  *   1 if str[0:len) satisfies finite automat fa,
  *   0 otherwise
  */
char satisfies_fa(fa_t *fa, symbol_t *input_seq, size_t len) {
  state_t s = fa->start_state;
  for (size_t i = 0; i < len; i++) {
    s = transition_func(fa, s, input_seq[i]);
  }

  return is_accepting(fa, s);
}

char is_accepting(fa_t *fa, state_t s) {
  for (size_t i = 0; i < fa->accepting_states_len; i++) {
    if (fa->accepting_states[i] == s) {
      return 1;
    }
  }
  return 0;
}

