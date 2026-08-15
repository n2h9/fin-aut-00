
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// FA 
// for a identifier of alphabetic haracter followed by up to 5 alphanumeric characters
// examples 
// "a" - not an identifier
// "A2", "aa", "bZ" - identifiers
char is_identifier(char * str, size_t len);

int main() {
  pid_t pid = getpid();
  printf("pid %d\n", pid);

  char str[1024];

  fgets(str, sizeof str, stdin);
  printf("you entered:\n%s\n", str);
  // -1 from strlen to drop the '\n'
  if (is_identifier(str, strlen(str) - 1)) {
    printf("this is an identifier\n");
  } else {
    printf("this is not an identifier\n");
  }

  return 0;
}

typedef char state;

const state s_start = 0;
const state s1      = 1;  // 1st char 
const state s2      = 2;  // 2nd char
const state s3      = 3;  // 3rd char
const state s4      = 4;  // 4th char
const state s5      = 5;  // 5th char
const state s_error = 10;

state transition(state s, char c) {
  state next = s_error;
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

const state init = s_start;
const state accepted[] = {s2, s3, s4, s5}; 

char is_accepted(state s) {
  const static size_t len = sizeof(accepted) / sizeof(accepted[0]);
  for (size_t i = 0; i < len; i++) {
    if (accepted[i] == s) {
      return 1;
    }
  }
  return 0;
}

char is_identifier(char *str, size_t len) {
  state s = init;
  for (size_t i = 0; i < len; i++) {
    s = transition(s, str[i]);
  }

  return is_accepted(s);
}
