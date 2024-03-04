#include <blocklist/blocklist.h>
#include <sys/param.h>
#include <time.h>
#include <fetch.h>
#include <errno.h>

char *
blocklist_path(struct blocklist *self)
{
  char *home = getenv("HOME");
  if (home) {
    char *relpath = "/.local/share/blocklist/", *fullpath;
    size_t
      offset1 = strlen(home),
      offset2 = strlen(relpath),
      bufsize = offset1 + offset2 + strlen(self->filename) + 1;
    fullpath = smalloc(sizeof(char) * bufsize);
    memcpy(&fullpath[0], home, offset1);
    memcpy(&fullpath[offset1], relpath, offset2);
    memcpy(&fullpath[offset1 + offset2], self->filename,
      strlen(self->filename) + 1);
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


FILE *
blocklist_get(struct blocklist *self)
{
  struct url *url = fetchParseURL(self->url);
  FILE *stream = fetchGetHTTP(url, "");
  fetchFreeURL(url);
  return (stream);
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
