#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../re.h"

void print_seq();
void print_reg();

int main(int argc, char **argv) {
  // printf("re from str\n");
  // printf("enter string with re:\n");
  //
  // char str[1024];
  // size_t str_len;
  //
  // fgets(str, sizeof str, stdin);
  //
  // // drop the '\n'
  // str_len = strlen(str ) - 1;
  // str[str_len] = 0;
  //
  // printf("you entered:\n%s\nlength=%zu\n", str, str_len);

  print_seq();
  print_reg();

  return 0;
}

void print_seq() { 
  char str[] = "abc";
  size_t str_len = strlen(str);

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

  printf("str from re (seq):\n%s\n", str_from_re);
  free(str_from_re);
}

void print_reg() { 
  re_opn_t re_opn = {
    .op = RE_ALTERN,
    .re01 = NULL,
    .re02 = NULL,
  };

  re_t re = {
    .kind = RE_OPN,
    .opn = &re_opn, 
  };

  size_t n;
  char *str_from_re = re_to_str(&re, &n);
  
  char *str_from_re_tmp = (char *) malloc(n+1 * sizeof(char));
  strncpy(str_from_re_tmp, str_from_re, n);
  str_from_re_tmp[n] = 0;

  printf("str from re (opn):\n%s\n", str_from_re_tmp);
  free(str_from_re);
  free(str_from_re_tmp);
}
