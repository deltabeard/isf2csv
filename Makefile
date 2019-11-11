OPT ?= -Og -g3
CFLAGS ?= -std=gnu99 -Wall -Wextra $(OPT)

isf2csv: isf2csv.c
