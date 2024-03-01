#include <blocklist/fetch.h>
#include <blocklist/file.h>
#include <blocklist/cmd.h>
#include <blocklist/set.h>
#include <blocklist/dyn_array.h>
#include <blocklist/path.h>
#include <blocklist/blocklist.h>

void
fetch_cmd(void)
{
  dyn_array *ary;
  blocklist *b;
  char *dir, *path;

  b = &BLOCKLISTS[0];
  dir = blocklistpf_dir();
  while (b->name != NULL)
  {
    path = join_path(dir, b->filename, NULL);
    ary = fetch_blocklist(b);
    if (ary == NULL) {
      fprintf(stderr, "Network error (%s): %s\n", b->url,
        fetchLastErrString);
      continue;
    }
    mkdir_p(dir);
    write_file(path, ary);
    printf("Write: %s\n", path);
    b++;
  }
}


void
cat_cmd(void)
{
  char *str, *dir;
  const char *table;
  struct Set set = RB_INITIALIZER(&set);

  dir = blocklistpf_dir();
  table = TABLES[0];
  while (table != NULL)
  {
    dyn_array *blocklists;
    blocklists = group_blocklists(table);
    printf("table <%s> {\n", table);
    for (int j = 0; j < blocklists->size; j++)
    {
      blocklist *b;
      dyn_array *file, *ipset;
      b = blocklists->items[j];
      printf("##\n# %s\n# %s\n# %s\n", b->name, b->desc, b->url);
      file = read_file(join_path(dir, b->filename, NULL));
      ipset = filter_file(file, &set);
      str = format_file(ipset, 3);
      printf("%s", str);
      free(str);
    }
    printf("}\n");
    table++;
    free_set(&set);
  }
}
