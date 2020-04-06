#
#	scalc - (c) sarah 2020
#	simple calculator
#
CFLAGS=-std=c89 -pedantic -Wall -Wextra -o scalc
FILES=scalc.c parse.c expr.c
default:
	cc	$(CFLAGS) $(FILES)
