#ifndef _RE_H
#define _RE_H

#include <unistd.h>

/**
  * As per Cooper & Torczon
  * Regular Expression (RE)) supports 3 opeerations:
  * - concatenation;
  * - alternation;
  * - Kleene closure
  * (more advanced opeartions could be defined from this 3 operations)
  */

struct RE;
struct RE_sequence;
struct RE_operation;

enum RE_type {
  SEQ,
  OPN,
};

enum RE_operation_kind {
  NOOP,
  CONCAT,
  ALTERN,
  CLOSUR,
};

typedef char re_symbol_t;

typedef struct RE re_t;
typedef enum RE_type re_type_enum;

typedef struct RE_sequence re_seq_t;
typedef struct RE_operation re_opn_t;
typedef enum RE_operation_kind re_opn_enum;

struct RE_sequence {
  re_symbol_t *str; 
};

struct RE_operation {
  re_t *re01;
  re_t *reo2; /* not used for unary operations */
  re_opn_enum op;
};

struct RE {
  re_type_enum kind;
  union {
    re_seq_t *seq;
    re_opn_t *opn;
  };
};

/**
 * parse string into re_t * typpe
*/
re_t * re_from(char *str, size_t len, int * err_code);

#endif
