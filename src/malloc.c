#include <blocklist.pf/malloc.h>

void*
safe_malloc(size_t size)
{
  void *ptr;
  errno = 0;
  ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "(fatal): %s", strerror(errno));
    abort();
  }
  return ptr;
}
