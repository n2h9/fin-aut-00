#ifndef _FA_H
#define _FA_H

#include <unistd.h>

typedef int state_t;

struct FA {
  state_t start_state;
  state_t (* transition_func)(state_t, char);
  size_t accepting_states_len;
  state_t accepting_states[];
};


/**
  * satisfies_fa
  * @param *fa
  * @returns 
  *   1 if str[0:len) satisfies finite automat fa,
  *   0 otherwise
  */
char satisfies_fa(struct FA *fa, char *str, int len);

#endif // ! _FA_H
