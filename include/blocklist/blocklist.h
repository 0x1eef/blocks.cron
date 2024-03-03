#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct blocklist {
  const char *name;
  const char *desc;
  const char *table;
  const char *url;
  const char *filename;
  const char *format;
  bool enabled;
  FILE* (*get)(struct blocklist*);
  char* (*path)(struct blocklist*);
  int (*write)(struct blocklist*, FILE *stream);
};

extern const char* TABLES[];
extern struct blocklist BLOCKLISTS[];

#define	NULL_BLOCKLIST                                     \
        (struct blocklist) { NULL, NULL, NULL, NULL, NULL, \
                             NULL, NULL, NULL, NULL, NULL }
