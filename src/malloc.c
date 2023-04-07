#include <blocklist.pf/malloc.h>

void*
safe_malloc(size_t size)
{
  errno = 0;
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "%s", strerror(errno));
    abort();
  }
  return ptr;
}
