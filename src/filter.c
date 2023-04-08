#include <blocklist.pf/buffer.h>
#include <blocklist.pf/malloc.h>
#include <blocklist.pf/set.h>
#include <ctype.h>

static buffer* filter(buffer *buf, struct Set *set);
static int is_space(char *str);

buffer* filter_buffer(buffer *buf, struct Set *set) {
  return filter(buf, set);
}

buffer*
filter(buffer *buf, struct Set *set) {
  for (int i = 0; i < buf->size; i++) {
    if (strncmp(buf->strings[i], "#", 1) == 0 ||
        is_space(buf->strings[i])) {
      free(buf->strings[i]);
      buf->strings[i] = NULL;
    } else {
      SetNode *node;
      node = safe_malloc(sizeof(SetNode));
      node->str = strdup(buf->strings[i]);
      if (RB_FIND(Set, set, node) == NULL) {
        RB_INSERT(Set, set, node);
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
