
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fa.h"

state_t transition_func(state_t s, char c);

const state_t s_start = 0;
const state_t s1      = 1;  // 1st char 
const state_t s2      = 2;  // 2nd char
const state_t s3      = 3;  // 3rd char
const state_t s4      = 4;  // 4th char
const state_t s5      = 5;  // 5th char
const state_t s_error = 10;

struct FA fa = {
  .start_state = s_start,
  .transition_func = transition_func,
  .accepting_states_len = 4,
  .accepting_states = {s2, s3, s4, s5},
};

int main() {
  pid_t pid = getpid();
  printf("pid %d\n", pid);

  char str[1024];

  fgets(str, sizeof str, stdin);
  printf("you entered:\n%s\n", str);
  // -1 from strlen to drop the '\n'
  if (satisfies_fa(&fa, str, strlen(str) - 1)) {
    printf("this is an identifier\n");
  } else {
    printf("this is not an identifier\n");
  }

  return 0;
}

state_t transition_func(state_t s, char c) {
  state_t next = s_error;
  if (s == s_start) {
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
      next = s1;
    } else {
      next = s_error;
    }
  } else if (s >= s1 && s <= s4) {
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9') {
      next = s + 1;
    } else {
      next = s_error;
    }
  } else if (s == s5) {
    next = s_error;
  } else if (s == s_error) {
    next = s_error;
  } else {
    next = s_error;
  }
  return next;
}

