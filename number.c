#include <stdio.h>
#include <string.h>
#include <unistd.h>

char is_number(char * str, size_t len);

int main() {
  pid_t pid = getpid();
  printf("pid %d\n", pid);

  char str[1024];

  fgets(str, sizeof str, stdin);
  printf("you entered:\n%s\n", str);
  // -1 from strlen to drop the '\n'
  if (is_number(str, strlen(str) - 1)) {
    printf("this is a number\n");
  } else {
    printf("this is not a number\n");
  }

  return 0;
}

typedef char state;

const state s0 = 0;
const state s1 = 1;
const state s2 = 2;
const state se = 10;

state transition(state s, char c) {
  state next = se;
  if (s == s0) {
    if (c == '0') {
      next = s1;
    } else if (c >= '1' && c <= '9') {
      next = s2;
    } else {
      next = se;
    }
  } else if (s == s1) {
    next = se;
  } else if (s == s2) {
    if (c >= '0' && c <= '9') {
      next = s2;
    } else {
      next = se;
    }
  } else if (s == se) {
    next = se;
  } else {
    next = se;
  }
  return next;
}

const state init = s0;
const state accepted[] = {s1, s2}; 

char is_accepted(state s) {
  const static size_t len = sizeof(accepted) / sizeof(accepted[0]);
  for (size_t i = 0; i < len; i++) {
    if (accepted[i] == s) {
      return 1;
    }
  }
  return 0;
}

char is_number(char *str, size_t len) {
  state s = init;
  for (size_t i = 0; i < len; i++) {
    s = transition(s, str[i]);
  }

  return is_accepted(s);
}
