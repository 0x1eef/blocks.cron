#include <blocklist.pf/buffer.h>
#include <blocklist.pf/malloc.h>
#include <ctype.h>

static buffer* filter(buffer *buf, struct hsearch_data *tbl);
static int is_space(char *str);

buffer* filter_buffer(buffer *buf, struct hsearch_data *tbl) {
  return filter(buf, tbl);
}

buffer*
filter(buffer *buf, struct hsearch_data *tbl) {
  for (int i = 0; i < buf->size; i++) {
    if (strncmp(buf->strings[i], "#", 1) == 0 ||
        is_space(buf->strings[i])) {
      free(buf->strings[i]);
      buf->strings[i] = NULL;
    } else {
      ENTRY *item;
      item = safe_malloc(sizeof(item));
      item->key = buf->strings[i];
      if (hsearch_r(*item, FIND, &item, tbl) == 0) {
        hsearch_r(*item, ENTER, &item, tbl);
      } else {
        buf->strings[i] = NULL;
      }
    }
  }
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
