#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../re.h"

int main(int argc, char **argv) {
  printf("re from str\n");
  printf("enter string with re:\n");

  char str[1024];
  size_t str_len;

  fgets(str, sizeof str, stdin);

  // drop the '\n'
  str_len = strlen(str ) - 1;
  str[str_len] = 0;

  printf("you entered:\n%s\nlength=%zu\n", str, str_len);

  re_seq_t re_seq = {
    .str = str,
    .size = str_len,  
  };

  re_t re = {
    .kind = RE_SEQ,
    .seq = &re_seq,
  };

  size_t n;
  char *str_from_re = re_to_str(&re, &n);

  printf("str from re:\n%s\n", str_from_re);
  free(str_from_re);
  return 0;
}
