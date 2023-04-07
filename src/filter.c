#include <blocklist.pf/buffer.h>
#include <ctype.h>

static int filter_first_pass(buffer *buf);
static buffer* filter_second_pass(buffer *buf, int j);
static int is_space(char *str);

buffer*
filter_buffer(buffer *buf) {
  return filter_second_pass(buf, filter_first_pass(buf));
}

static int
filter_first_pass(buffer *buf) {
  int j;

  j = 0;
  for (int i = 0; i < buf->size; i++) {
    if (strncmp(buf->strings[i], "#", 1) == 0 ||
        is_space(buf->strings[i])) {
      free(buf->strings[i]);
      buf->strings[i] = NULL;
      j++;
    }
  }

  return j;
}

static buffer*
filter_second_pass(buffer *buf, int j) {
  char **strings;
  int k;

  j = buf->size - j;
  strings = malloc(sizeof(char*) * j);
  k = 0;
  for (int i = 0; i < buf->size; i++) {
    if (k == j) {
      break;
    }
    if (buf->strings[i] != NULL) {
      strings[k] = buf->strings[i];
      k++;
    }
  }
  buf->size = j;
  buf->strings = strings;

  return buf;
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
