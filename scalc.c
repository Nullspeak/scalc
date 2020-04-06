/*
 *	scalc - (c) sarah 2020
 *	simple calculator
 *	NOTE: i can't guarantee this thing's accuracy
 *	or efficacy, it's just a toy for now
 */
#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

int main() {
	/* until interrupted */
	char *buf;
	buf = malloc(sizeof(char) * 65);
	while(fgets(buf, 64, stdin)) {
		double result;
		result = parse_and_eval(buf);
		printf("%s%f\n", "> ", result);
	}
	free(buf);

	return 0;
}
