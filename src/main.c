#include <blocklist/command.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void print_usage(void);

int
main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage();
    }
    else if (strcmp(argv[1], "download") == 0)
    {
        return (download_command());
    }
    else if (strcmp(argv[1], "echo") == 0)
    {
        return (echo_command());
    }
    else
    {
        print_usage();
    }
}

static void
print_usage(void)
{
    fprintf(stderr,
            "Usage: blocklist COMMAND [OPTIONS]\n"
            "\n"
            "Commands:\n"
            "download\tDownload blocklists to ~/.local/share/blocklist.\n"
            "echo    \tEcho PF tables to standard output.\n");
    exit(EXIT_FAILURE);
}
