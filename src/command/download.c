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
  struct blocklist *enabled;
  struct blocklist *blocklist;
  enabled = blocklists_all("enabled");
  blocklist = &enabled[0];
  while (blocklist->name != NULL)
  {
    char *path;
    FILE *stream;
    path   = blocklist->path(blocklist->filename);
    stream = blocklist->get(blocklist->url);
    if (stream) {
      if (blocklist->write(stream, path) == 0) {
        printf("[ok] %s\n", path);
      } else {
        fprintf(
          stderr,
          "[warn] %s: %s\n", path, strerror(errno)
        );
      }
      fclose(stream);
    } else {
      fprintf(
        stderr,
        "[warn] %s: %s\n", enabled->url, fetchLastErrString
      );
    }
    blocklist++;
    free(path);
  }
  free(enabled);
  return (EXIT_SUCCESS);
}

