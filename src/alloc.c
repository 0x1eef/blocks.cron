#include <blocklist/alloc.h>
#include <stdio.h>
#include <stdlib.h>

void *
alloc(size_t size)
{
    void *mem;
    mem = malloc(size);
    if (mem == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return (mem);
}
