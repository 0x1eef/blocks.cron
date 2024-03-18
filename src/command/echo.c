#include <blocklist/alloc.h>
#include <blocklist/blocklists.h>
#include <blocklist/string.h>
#include <errno.h>
#include <isinetaddr.h>
#include <string.h>

static char *tables[] = {
    "attacks", "malware", "reputation", "anonymizers", "adware", NULL};
static void table_head(FILE *, char *);
static void table_body(FILE *, struct blocklist[]);
static void table_tail(FILE *);
static void comment(FILE *, struct blocklist *);

int
echo_command(void)
{
  char **cursor;
  struct blocklist *enabled;
  cursor  = tables;
  enabled = blocklists_all("enabled");
  while (*cursor != NULL)
  {
    char *table;
    struct blocklist *blocks;
    table  = *cursor;
    blocks = blocklists_by_table(enabled, table);
    table_head(stdout, table);
    table_body(stdout, blocks);
    table_tail(stdout);
    cursor++;
    free(blocks);
  }
  free(enabled);
  return EXIT_SUCCESS;
}

static void
table_head(FILE *fd, char *table)
{
  fprintf(fd, "table <%s> {\n", table);
}

static void
table_body(FILE *fd, struct blocklist *blocks)
{
  struct blocklist *block;
  char *line;
  block = &blocks[0];
  line  = alloc(sizeof(char) * 1024);
  while (block->name != NULL)
  {
    char *path;
    FILE *file;
    path = block->path(block->filename);
    file = fopen(path, "rb");
    if (file)
    {
      comment(fd, block);
      while (fgets(line, 1024, file))
      {
        line = chomp(line);
        if (iscidraddr4(line))
        {
          fprintf(fd, "  %s\n", line);
        }
      }
      fclose(file);
    }
    free(path);
    block++;
  }
}

static void
table_tail(FILE *fd)
{
  fprintf(fd, "}\n");
}

static void
comment(FILE *fd, struct blocklist *block)
{
  fprintf(fd, "##\n# %s\n# %s\n# %s\n", block->name, block->desc, block->url);
}
