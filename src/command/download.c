#include <blocklist/blocklists.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <errno.h>
#include <string.h>

int
download_command(void)
{
  struct blocklist *enabled;
  struct blocklist *block;
  enabled = blocklists_all("enabled");
  block   = enabled;
  while (block->name != NULL)
  {
    char *url, *path;
    int err;
    url  = (char *)block->url;
    path = block->path(block->filename);
    err  = block->store(url, path);
    if (err)
    {
      if (err == -1)
      {
        fprintf(stderr, "[fatal] %s: %s\n", path, strerror(errno));
      }
      else
      {
        fprintf(stderr, "[fatal] network error (%s)\n", block->url);
      }
      return (EXIT_FAILURE);
    }
    else
    {
      printf("[ok] %s\n", path);
    }
    block++;
    free(path);
  }
  free(enabled);
  return (EXIT_SUCCESS);
}
