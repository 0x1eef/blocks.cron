#include <blocklist.pf/malloc.h>
#include <blocklist.pf/buffer.h>

buffer*
new_buffer(FILE *f, int maxs, int maxw) {
  char *str, **strings;
  buffer *buf;
  int i;

  i = 0;
  strings = safe_malloc(sizeof(char *) * (maxs + 1));
  str = safe_malloc(sizeof(char[maxw]));
  while(fgets(str, maxw, f) != NULL) {
    if (i == maxs) {
      free(str);
      break;
    } else {
      if (strchr(str, '\n') == NULL) {
        strncat(str, "\n", 1);
      }
      strings[i++] = str;
    }
    str = safe_malloc(sizeof(char[maxw]));
  }
  strings[i] = NULL;
  buf = malloc(sizeof(buffer));
  buf->size = i;
  buf->strings = strings;

  return buf;
}

char*
format_buffer(buffer *buf, int per_line) {
  char *s;

  s = safe_malloc(sizeof(char[MAXCOLS * buf->size]));
  for (int i = 1; i < buf->size; i++) {
    char *f = buf->strings[i - 1];
    int onlastline = (1 + i) == buf->size;
    strcat(s, strdup(chomp(f)));
    if (i % per_line == 0 || onlastline) {
      strcat(s, " \\\n");
    } else {
      strcat(s, ", ");
    }
  }

  return s;
}

void
free_buffer(buffer *buf) {
  for (int i = 0; i < buf->size; i++) {
    free(buf->strings[i]);
  }
  free(buf->strings);
  free(buf);
}
