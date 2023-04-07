#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <blocklist.pf/buffer.h>

buffer*
read_file(const char *path, int maxl, int maxw) {
  FILE *f;
  buffer *buf;

  f = fopen(path, "rb");
  if (f == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(1);
  }
  buf = new_buffer(f, maxl, maxw);
  fclose(f);

  return buf;
}


int
write_file(const char *path, buffer *buf) {
  int t;
  FILE *f;

  t = 0;
  f = fopen(path, "wb");
  if (f == NULL) {
    printf("%s: %s\n", path, strerror(errno));
    exit(errno);
  }
  for(int i = 0; i < buf->size; i++) {
    t += write(fileno(f),
               buf->strings[i],
               strlen(buf->strings[i]));
  }
  fclose(f);

  return t;
}
