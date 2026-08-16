#ifndef _RE_H
#define _RE_H

#include "fa.h"
#include <unistd.h>

/**
 * As described by Cooper and Torczon, a regular expression (RE) supports
 * three basic operations:
 *
 * - concatenation;
 * - alternation;
 * - Kleene closure.
 *
 * More advanced operations can be defined in terms of these three operations.
 */

struct RE;
struct RE_sequence;
struct RE_operation;

enum RE_type {
  RE_SEQ,
  RE_OPN,
};

enum RE_operation_kind {
  RE_NOOP,
  RE_CONCAT,
  RE_ALTERN,
  RE_CLOSUR,
};

typedef char re_symbol_t;

typedef struct RE re_t;
typedef enum RE_type re_type_enum;

typedef struct RE_sequence re_seq_t;
typedef struct RE_operation re_opn_t;
typedef enum RE_operation_kind re_opn_enum;

struct RE_sequence {
  re_symbol_t *str;
  size_t size;
};

struct RE_operation {
  re_t *re01;
  re_t *re02; /* Not used for unary operations. */
  re_opn_enum op;
};

struct RE {
  re_type_enum kind;
  union {
    re_seq_t *seq;
    re_opn_t *opn;
  };
};

#define ERR_UNKNOWN_ESCAPE_SEQ  1
#define ERR_INCORRECT_OPERAND   2

/**
 * Parses a string into a regular expression.
 *
 * @param str      The input string to parse.
 * @param len      The length of the input string.
 * @param err_code A pointer to an integer where the error code is stored.
 * @param err_inddx An index of character where error detected
 * @return A pointer to the resulting regular expression, or NULL if parsing
 *         fails.
 */
re_t *re_from_str(char *str, size_t len, int *err_code, int *err_indx);

re_t *re_from_symbol(symbol_t s);

re_t *re_from_re(re_t *re1, re_t *re2, re_opn_enum opn_kind);

#endif
