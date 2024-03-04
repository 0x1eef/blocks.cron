#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <fetch.h>
#include <errno.h>
#include <blocklist/blocklists.h>

int
download_command(void)
{
  struct blocklist *b = &BLOCKLISTS[0];
  while (b->name != NULL)
  {
    if (b->enabled) {
      char *path = b->path(b);
      FILE *stream = b->get(b);
      if (stream) {
        if (b->write(stream, path)) {
          printf("[ok] %s\n", path);
        } else {
          fprintf(
                  stderr,
                  "[warn] %s: %s\n", path, strerror(errno)
                  );
        }
      } else {
        fprintf(
                stderr,
                "[warn] %s: %s\n", b->url, fetchLastErrString
                );
      }
    }
    b++;
  }
  return EXIT_SUCCESS;
}

