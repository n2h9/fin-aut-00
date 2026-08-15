
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../fa.h"


// start and error states defined inn fa.h
const state_t s_error     = 0;
const state_t s_start     = 1;
const state_t s1          = 2;  // 1st cha
const state_t s2          = 3;  // 2nd char
const state_t s3          = 4;  // 3rd char
const state_t s4          = 5;  // 4th char
const state_t s5          = 6;  // 5th char
const state_t s_sentinel  = 7;

struct FA fa = {
  .start_state = s_start,
  .transition_table_size = s_sentinel,
  .transition_table = NULL, // is populated by calling prepare_transition_table bellow
  .accepting_states_len = 4,
  .accepting_states = {s2, s3, s4, s5},
};

void prepare_transition_table();
void delete_transition_table();

int main() {
  pid_t pid = getpid();
  printf("pid %d\n", pid);

  prepare_transition_table();

  char str[1024];

  fgets(str, sizeof str, stdin);
  printf("you entered:\n%s\n", str);
  // -1 from strlen to drop the '\n'
  if (satisfies_fa(&fa, str, strlen(str) - 1)) {
    printf("this is an identifier\n");
  } else {
    printf("this is not an identifier\n");
  }

  delete_transition_table();

  return 0;
}

// populates transition table of fa defined above
void prepare_transition_table() {
  transition_table_t tt = (transition_table_t) malloc(fa.transition_table_size * sizeof(state_t *));
  for (size_t i = 0; i < fa.transition_table_size; i++) {
    tt[i] = (state_t *) malloc(INPUT_ALPHABET_SIZE * sizeof(state_t));
    for (size_t j = 0; j < INPUT_ALPHABET_SIZE; j++) {
      tt[i][j] = s_error;
    }
  }

  for (symbol_t s = 'a'; s <= 'z'; s++) {
    tt[s_start][s] = s1;
  }

  for (symbol_t s = 'A'; s <= 'Z'; s++) {
    tt[s_start][s] = s1;
  }

  for (state_t  st = s1; st <= s4; st++) {
    state_t next = st + 1;
    for (symbol_t s = 'a'; s <= 'z'; s++) {
      tt[st][s] =next;
    }

    for (symbol_t s = 'A'; s <= 'Z'; s++) {
      tt[st][s] = next;
    }

    for (symbol_t s = '0'; s <= '9'; s++) {
      tt[st][s] = next;
    }
  }

  fa.transition_table = tt;
}

void delete_transition_table() {
  transition_table_t tt = fa.transition_table;
  for (size_t i = 0; i < fa.transition_table_size; i++) {
    free(tt[i]);
  }

  free(tt);
  fa.transition_table = NULL;
}
