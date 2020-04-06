/*
 *	scalc - (c) sarah 2020
 *	simple calculator
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "expr.h"

static const char opchars[] = {'+', '-', '*', '/'};

void safe_free(void *ptr) {
	if(ptr == NULL)
		return;
	free(ptr);
}

/* looks for the first occurance of an opcode */
int look_for_opcode(const char *expr) {
	int oploc;
	int len;
	int i, j;
	
	oploc = -1;
	len = strlen(expr);
	
	/* search through the string for an opcode */
	for(i = 0;i < EXPROP_MAX;i++) {
		for(j = 0;j < len;j++) {
			if(expr[j] == opchars[i])
				oploc = j;
		}
	}
	
	return oploc;
}

/* gets opcode index from char */
int opcode_from_char(char c) {
	int i;
	for(i = 0;i<EXPROP_MAX;i++) {
		if(opchars[i] == c)
			return i;
	}
	return -1;
}

/*
 *	modified from https://gist.github.com/kenkam/790090
 */
#define isdec(x) (isspace(x) || !(isdigit(x) || x == '.'))
char *trim_space(char *str) {
    char *end;
    /* skip leading whitespace */
    while(isdec(*str))
        str = str + 1;

    /* remove trailing whitespace */
    end = str + strlen(str) - 1;
    while(end > str && isdec(*end)) {
        end = end - 1;
    }
    /* write null character */
    *(end+1) = '\0';
    return str;
}

/* parses text into an expression and evals it */
double parse_and_eval(const char *expr) {
	double result;
	expr_t *eval_val;
	int oploc;
	int len;
	int opcode;
	/* chopped off parts */
	char *lvalue;
	char *rvalue;
	char *lvalue2;
	char *rvalue2;
	int i;
	
	result = 0.0;
	eval_val = malloc(sizeof(expr_t));
	oploc = look_for_opcode(expr);
	len = strlen(expr);
	opcode = -1;
	lvalue = malloc(sizeof(char) * 17);
	rvalue = malloc(sizeof(char) * 17);
	
	/* something went really wrong */
	if(eval_val == NULL || lvalue == NULL || rvalue == NULL) {
		/* free what's left */
		safe_free(lvalue); safe_free(rvalue); safe_free(eval_val);
		printf("%s\n", "[parse_and_eval]: Memory allocation error");
		return 0.0;
	}

	/* the opcode or rvalue is probably missing */
	if(oploc < 1 || expr[oploc] == 0 || expr[oploc + 1] == 0) {
		printf("%d\n", oploc);
		printf("%s%s%s\n", "[parse_and_eval]: (", expr, ") is not a valid expression");
		return 0.0;
	}
	
	/* get the opcode id */
	opcode = opcode_from_char(expr[oploc]);
	
	if(opcode < 0) {
		printf("%s\n", "[parse_and_eval]: Invalid opcode");
		return 0.0;
	}
	
	/* copy the numbers to their own buffers */
	for(i = 0;i<oploc;i++)
		lvalue[i] = expr[i];

	for(i = (oploc + 1);i<len;i++)
		rvalue[i - (oploc + 1)] = expr[i];
	
	/* make sure they have nulled ends */
	lvalue[16] = 0;
	rvalue[16] = 0;
	
	/* snip out any spaces */
	lvalue2 = trim_space(lvalue);
	rvalue2 = trim_space(rvalue);
	
	eval_val->lvalue = strtod(lvalue2, NULL);
	eval_val->rvalue = strtod(rvalue2, NULL);
	eval_val->op = opcode;
	result = expr_eval(eval_val);
	
	/* free the buffers, we no longer need them */
	safe_free(lvalue);
	safe_free(rvalue);
	safe_free(eval_val);
	
	return result;
}
