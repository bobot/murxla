#ifndef __SMTMBT__CONFIG_H
#define __SMTMBT__CONFIG_H

#define SMTMBT_BW_MIN 1
#define SMTMBT_BW_MAX 128

#define SMTMBT_INT_LEN_MAX 50
#define SMTMBT_REAL_LEN_MAX 50
#define SMTMBT_STR_LEN_MAX 100

#define SMTMBT_SYMBOL_LEN_MAX 128

#define SMTMBT_MAX_N_ASSUMPTIONS_CHECK_SAT 5
#define SMTMBT_MAX_N_PUSH_LEVELS 5
#define SMTMBT_MAX_N_TERMS_GET_VALUE 5

/* mk_term: at least one argument */
#define SMTMBT_MK_TERM_N_ARGS -1
/* mk_term: at least two arguemtns */
#define SMTMBT_MK_TERM_N_ARGS_BIN -2
/* mk_term: min number of arguments */
#define SMTMBT_MK_TERM_N_ARGS_MIN(arity) ((arity) < 0 ? -(arity) : (arity))
/* mk_term: max number of arguments */
#define SMTMBT_MK_TERM_N_ARGS_MAX 11

#endif
