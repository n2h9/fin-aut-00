#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fa.h"

state_t transition_func(fa_t *fa, state_t from, symbol_t s) {
  // TODO: Check that `from` is within the bounds of the transition table.
  return fa->transition_table[from][s];
}

/**
 * Checks whether a given state is an accepting state of the finite automaton.
 *
 * @param fa The finite automaton.
 * @param s  The state to check.
 *
 * @return 1 if `s` is an accepting state of `fa`, 0 otherwise.
 */
char is_accepting(fa_t *fa, state_t s);

/**
 * Determines whether the given input sequence is accepted by the finite
 * automaton.
 *
 * @param fa        The finite automaton.
 * @param input_seq The input sequence to evaluate.
 * @param len       The length of the input sequence.
 *
 * @return 1 if the input sequence is accepted by the finite automaton,
 *         0 otherwise.
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
