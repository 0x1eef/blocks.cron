#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <blocklist.pf/string.h>
#include <blocklist.pf/set.h>

#define MAXROWS 100000
#define MAXCOLS 1000

typedef struct {
  int size;
  char **strings;
} buffer;

buffer* new_buffer(FILE *f, int maxl, int maxw);
buffer* filter_buffer(buffer *buf, struct Set *set);
char* format_buffer(buffer *buf, int per_line);
void free_buffer(buffer *buf);
