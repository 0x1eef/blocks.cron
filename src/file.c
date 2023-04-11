#include <blocklist.pf/dyn_array.h>
#include <blocklist.pf/string.h>
#include <blocklist.pf/set.h>
#include <blocklist.pf/malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

static int is_space(char *str);

char*
format_file(dyn_array *file, int per_line) {
  char *str;
  size_t buf;
  buf = 0;
  str = safe_malloc(sizeof(char[1]));
  strcpy(str, "\0");
  for (int i = 1; i <= file->size; i++) {
    char *lne;
    lne = file->items[i - 1];
    buf = buf + sizeof(char[strlen(lne)]) + sizeof(char[4]);
    str = safe_realloc(str, buf);
    strcat(str, strdup(chomp(lne)));
    if (i % per_line == 0 || i == file->size) {
      strcat(str, " \\\n");
    } else {
      strcat(str, ", ");
    }
  }
  return str;
}

dyn_array*
filter_file(dyn_array *file, struct Set *set) {
  for (int i = 0; i < file->size; i++) {
    if (strncmp(file->items[i], "#", 1) == 0 ||
        is_space(file->items[i])) {
      array_free_item(file, i);
      i--;
    } else {
      SetNode *node;
      node = safe_malloc(sizeof(SetNode));
      node->str = strdup(file->items[i]);
      if (RB_FIND(Set, set, node) == NULL) {
        RB_INSERT(Set, set, node);
      } else {
        array_free_item(file, i);
        i--;
      }
    }
  }
  return file;
}

dyn_array*
read_file(const char *path) {
  FILE *f;
  dyn_array *ary;
  f = fopen(path, "rb");
  if (f == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(1);
  }
  ary = array_from_file(f);
  fclose(f);
  return ary;
}


int
write_file(const char *path, dyn_array *ary) {
  int t;
  FILE *f;
  t = 0;
  f = fopen(path, "wb");
  if (f == NULL) {
    printf("%s: %s\n", path, strerror(errno));
    exit(errno);
  }
  for(int i = 0; i < ary->size; i++) {
    t += write(fileno(f),
               ary->items[i],
               strlen(ary->items[i]));
  }
  fclose(f);
  return t;
}

static int
is_space(char *str) {
  for (int i = 0; i < (int)strlen(str); i++) {
    if (!isspace(str[i])) {
      return 0;
    }
  }
  return 1;
}
