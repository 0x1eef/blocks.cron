#include <blocklist/blocklists.h>
#include <stdlib.h>
#include <curl/curl.h>

int
download_command(void)
{
  struct blocklist *enabled;
  struct blocklist *blocklist;
  enabled   = blocklists_all("enabled");
  blocklist = &enabled[0];
  while (blocklist->name != NULL)
  {
    char *url, *path;
    url  = (char *)blocklist->url;
    path = blocklist->path(blocklist->filename);
    if (blocklist->store(url, path) == 0)
    {
      printf("[ok] %s\n", path);
    }
    else
    {
      fprintf(stderr, "[warn] %s: error\n", blocklist->url);
    }
    blocklist++;
    free(path);
  }
  free(enabled);
  return (EXIT_SUCCESS);
}
