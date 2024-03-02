#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <fetch.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <blocklist/blocklist.h>
static FILE* download(struct blocklist*);

int
download_command(void)
{
  struct blocklist *b = &BLOCKLISTS[0];
  while (b->name != NULL)
  {
    if (b->enabled) {
      char *path = b->path(b);
      FILE *stream = download(b);
      if (stream) {
        if (b->write(b, stream)) {
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

FILE*
download(struct blocklist *b)
{
  struct url *url;
  FILE *stream;
  url = fetchParseURL(b->url);
  stream = fetchGetHTTP(url, "");
  fetchFreeURL(url);
  return stream;
}
