#include <blocklist/alloc.h>
#include <blocklist/blocklist.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/param.h>
#include <fetch.h>

char *
blocklist_path(const char *filename)
{
    char *home;
    home = getenv("HOME");
    if (home)
    {
        char *relpath  = "/.local/share/blocklist/", *fullpath;
        size_t offset1 = strlen(home), offset2 = strlen(relpath),
               bufsize = offset1 + offset2 + strlen(filename) + 1;
        fullpath       = alloc(sizeof(char) * bufsize);
        memcpy(&fullpath[0], home, offset1);
        memcpy(&fullpath[offset1], relpath, offset2);
        memcpy(&fullpath[offset1 + offset2], filename, strlen(filename) + 1);
        return (fullpath);
    }
    else
    {
        char *fullpath = strdup("/usr/local/share/pf/blocklist");
        if (fullpath)
        {
            return (fullpath);
        }
        else
        {
            fprintf(stderr, "[fatal] %s", strerror(errno));
            abort();
        }
    }
}

FILE *
blocklist_get(const char *urlstr)
{
    struct url *url;
    url = fetchParseURL(urlstr);
    if (url == NULL)
    {
        return NULL;
    }
    else
    {
        FILE *stream;
        stream = fetchGetHTTP(url, "");
        fetchFreeURL(url);
        return (stream);
    }
}

int
blocklist_write(FILE *stream, char *path)
{
    FILE *file;
    file = fopen(path, "wb");
    if (file == NULL)
    {
        return (-1);
    }
    else
    {
        char buf[1];
        while (fread(&buf, 1, 1, stream) != 0)
        {
            fwrite(&buf, 1, 1, file);
        }
        fclose(file);
        return (0);
    }
}
