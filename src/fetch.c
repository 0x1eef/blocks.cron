#include <blocklist.pf/fetch.h>

buffer*
fetch_blocklist(blocklist *bl, int maxrows, int maxcols) {
  struct url *u;
  FILE *f;
  buffer *buf;
  u = fetchParseURL(bl->url);
  f = fetchGetHTTP(u, "");
  if (f == NULL) {
    return NULL;
  }
  buf = new_buffer(f, maxrows, maxcols);
  fclose(f);
  return buf;
}
