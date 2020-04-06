/*
 *	scalc - (c) sarah 2020
 *	simple calculator
 *	this has struct defs and prototypes
 *	for expression eval stuff
 */
#ifndef SCALC_EXPR_H
#define SCALC_EXPR_H

/* the possible calculation operators */
enum expr_ops_ {
	EXPROP_ADD,
	EXPROP_SUB,
	EXPROP_MUL,
	EXPROP_DIV,
	
	EXPROP_MAX
};

/* an expression */
struct expr_ {
	double lvalue;
	double rvalue;
	int op;
};
typedef struct expr_ expr_t;

/* evaluates an expression */
double expr_eval(expr_t *expr);

#endif /* SCALC_EXPR_H */
