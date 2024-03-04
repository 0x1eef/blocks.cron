#include <blocklist/blocklist.h>
#include <sys/param.h>
#include <time.h>
#include <fetch.h>
#include <errno.h>

char *
blocklist_path(struct blocklist *b)
{
  char *home = getenv("HOME");
  if (home) {
    char *relpath, *fullpath;
    size_t bufsize, offset1, offset2;
    relpath = "/.local/share/blocklist/";
    offset1 = strlen(home);
    offset2 = strlen(relpath);
    bufsize = offset1 + offset2 + strlen(b->filename) + 1;
    fullpath = smalloc(sizeof(char) * bufsize);
    memcpy(&fullpath[0], home, offset1);
    memcpy(&fullpath[offset1], relpath, offset2);
    memcpy(&fullpath[offset1 + offset2], b->filename, strlen(b->filename) + 1);
    return (fullpath);
  } else {
    char *fullpath = strdup("/usr/local/share/pf/blocklist");
    if (fullpath) {
      return (fullpath);
    } else {
      fprintf(stderr, "[fatal] %s", strerror(errno));
      abort();
    }
  }
}


int
blocklist_write(FILE *stream, char *path)
{
  FILE *file = fopen(path, "wb");
  if (file == NULL) {
    return (0);
  } else {
    char buf[1];
    while (fread(&buf, 1, 1, stream) != 0)
    {
      fwrite(&buf, 1, 1, file);
    }
    fclose(file);
    fclose(stream);
    return (1);
  }
}


FILE *
blocklist_get(struct blocklist *b)
{
  struct url *url;
  FILE *stream;
  url = fetchParseURL(b->url);
  stream = fetchGetHTTP(url, "");
  fetchFreeURL(url);
  return (stream);
}
