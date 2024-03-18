#include <blocklist/alloc.h>
#include <blocklist/blocklists.h>
#include <blocklist/string.h>
#include <errno.h>
#include <isinetaddr.h>
#include <string.h>

static const int MAXLEN = 1024;

int
echo_command(void)
{
    char **table = (char **)&TABLES[0], *line = alloc(sizeof(char) * MAXLEN);
    struct blocklist *blocklists = NULL;
    while (*table != NULL)
    {
        blocklists = blocklists_by_table(blocklists_all("enabled"), *table);
        struct blocklist *b = &blocklists[0];
        printf("table <%s> {\n", *table);
        while (b->name != NULL)
        {
            char *path = b->path(b->filename);
            FILE *file = fopen(path, "rb");
            if (file)
            {
                printf("##\n# %s\n# %s\n# %s\n", b->name, b->desc, b->url);
                while (fgets(line, MAXLEN, file))
                {
                    line = chomp(line);
                    if (iscidraddr4(line))
                    {
                        printf("  %s\n", line);
                    }
                }
            }
            else
            {
                fprintf(stderr, "[warn] %s: %s\n", path, strerror(errno));
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
