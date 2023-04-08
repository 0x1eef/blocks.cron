#include <blocklist.pf/fetch.h>
#include <blocklist.pf/file.h>
#include <blocklist.pf/buffer.h>
#include <blocklist.pf/cmd.h>
#include <search.h>

void
fetch_cmd(void) {
  int size;
  buffer *buf;
  size = sizeof(BLOCKLISTS) / sizeof(BLOCKLISTS[0]);
  for (int i = 0; i < size; i++) {
    blocklist bl = BLOCKLISTS[i];
    printf("Fetch: %s\n", bl.url);
    buf = fetch_blocklist(&bl, MAXROWS, MAXCOLS);
    if (buf == NULL) {
      fprintf(stderr, "Network error: %s\n", fetchLastErrString);
      continue;
    }
    write_file(bl.path, buf);
    printf("Write: %s\n", bl.path);
    free_buffer(buf);
  }
}

void
cat_cmd(void) {
  int size;
  char *str;
  buffer *buf;
  struct hsearch_data tbl;
  size = sizeof(BLOCKLISTS) / sizeof(BLOCKLISTS[0]);
  hcreate_r(0, &tbl);
  printf("table <blocklist> {\n");
  for (int i = 0; i < size; i++) {
    blocklist bl = BLOCKLISTS[i];
    printf("##\n# %s\n# %s\n# %s\n", bl.name, bl.desc, bl.url);
    buf = read_file(bl.path, MAXROWS, MAXCOLS);
    buf = filter_buffer(buf, &tbl);
    str = format_buffer(buf, 3);
    printf("%s", str);
    free_buffer(buf);
    free(str);
  }
  printf("}\n");
  hdestroy_r(&tbl);
}
