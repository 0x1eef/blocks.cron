#pragma once
#include <stdbool.h>
#include <stdio.h>

struct blocklist {
  const char *name;
  const char *desc;
  const char *table;
  const char *url;
  const char *about_url;
  const char *filename;
  const char *format;
  bool enabled;
  FILE* (*get)(const char*);
  char* (*path)(const char*);
  int (*write)(FILE*, char*);
};

FILE* blocklist_get(const char*);
char* blocklist_path(const char*);
int blocklist_write(FILE*, char*);

#define	NULL_BLOCKLIST                                     \
        (struct blocklist) { NULL, NULL, NULL, NULL, NULL, \
                             NULL, NULL, NULL, NULL, NULL, \
            NULL }
