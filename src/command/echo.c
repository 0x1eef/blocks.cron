#include <blocklist/string.h>
#include <blocklist/blocklists.h>
#include <isinetaddr.h>
#include <string.h>
#include <errno.h>

static const int MAXLEN = 1024;
static struct blocklist* filter(struct blocklist*, const char*);

int
echo_command(void)
{
  char
    **table = (char**)&TABLES[0],
    *line = smalloc(sizeof(char) * MAXLEN);
  struct blocklist *blocklists = NULL;
  while (*table != NULL) {
    blocklists = filter(&BLOCKLISTS[0], *table);
    struct blocklist *b = &blocklists[0];
    printf("table <%s> {\n", *table);
    while (b->name != NULL) {
      if (b->enabled) {
        char *path = b->path(b);
        FILE *file = fopen(path, "rb");
        if (file) {
          printf("##\n# %s\n# %s\n# %s\n", b->name, b->desc, b->url);
          while(fgets(line, MAXLEN, file)) {
            line = chomp(line);
            if (iscidraddr4(line)) {
              printf("  %s\n", line);
            }
          }
        } else {
          fprintf(stderr, "[warn] %s: %s\n", path, strerror(errno));
        }
      }
      b++;
    }
    free(blocklists);
    printf("}\n");
    table++;
  }
  free(line);
  return EXIT_SUCCESS;
}

static
struct blocklist *
filter(struct blocklist *blocklists, const char *table)
{
  struct blocklist
    *group = smalloc(sizeof(struct blocklist) * blocklists_count(&blocklists[0])),
    *group_ptr = &group[0],
    *b = &blocklists[0];
  while (b->name != NULL)
  {
    if (strcmp(table, b->table) == 0) {
      *group_ptr = *b;
      group_ptr++;
    }
    b++;
  }
  *group_ptr = NULL_BLOCKLIST;
  return (group);
}