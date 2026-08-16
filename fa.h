#ifndef _FA_H
#define _FA_H

#include <stddef.h>
#include <unistd.h>

struct FA;

typedef struct FA fa_t;

typedef unsigned int state_t;
typedef char symbol_t;

/*
 * transition_table_t represents the transition table as a two-dimensional
 * array. The entry [state_from][s] -> state_to represents a transition
 * from state_from to state_to on input symbol "s".
 *
 * The transition table type relies on both state_t and symbol_t being
 * compatible with the types used for indexing the table.
 */
typedef state_t** transition_table_t;

#define INPUT_ALPHABET_SIZE 256

struct FA {
  state_t start_state;
  size_t transition_table_size;
  transition_table_t transition_table;
  size_t accepting_states_len;
  state_t accepting_states[];
};

state_t transition_func(fa_t *fa, state_t from, symbol_t s);

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
char satisfies_fa(fa_t *fa, symbol_t *input_seq, size_t len);

#endif // !_FA_H
