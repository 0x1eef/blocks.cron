#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "smalloc.h"

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

FILE* blocklist_get(struct blocklist*);
char* blocklist_path(struct blocklist*);
int blocklist_write(struct blocklist*, FILE *stream);

#define	NULL_BLOCKLIST                                     \
        (struct blocklist) { NULL, NULL, NULL, NULL, NULL, \
                             NULL, NULL, NULL, NULL, NULL }
