/*
 *	scalc - (c) sarah 2020
 *	simple calculator
 */
#include <stdio.h>
#include "expr.h"

/* evaluates an expression */
double expr_eval(expr_t *expr) {
	if(expr == (void *)0) {
		printf("%s\n", "[expr_eval]: Null expression pointer");
		return 0.0;
	}
	
	switch(expr->op) {
		case EXPROP_ADD:
		return (expr->lvalue + expr->rvalue);
		case EXPROP_SUB:
		return (expr->lvalue - expr->rvalue);
		case EXPROP_MUL:
		return (expr->lvalue * expr->rvalue);
		case EXPROP_DIV:
		if(expr->rvalue == 0.0) {
			printf("%s\n", "[expr_eval]: division by zero");
			return 0.0;
		}
		return (expr->lvalue / expr->rvalue);
		
		default:
		printf("%s%d%s\n", "[expr_eval]: ", expr->op, " is an invalid opcode");
		return 0.0;
	}
}
