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
  int (*write)(FILE*, char*);
};

FILE* blocklist_get(struct blocklist*);
char* blocklist_path(struct blocklist*);
int blocklist_write(FILE*, char*);

#define	NULL_BLOCKLIST                                     \
        (struct blocklist) { NULL, NULL, NULL, NULL, NULL, \
                             NULL, NULL, NULL, NULL, NULL }
