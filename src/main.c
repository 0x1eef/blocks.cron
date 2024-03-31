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
    return (EXIT_FAILURE);
  }
  else if (strcmp(argv[1], "download") == 0)
  {
    return (download_command());
  }
  else if (strcmp(argv[1], "emit") == 0)
  {
    return (emit_command());
  }
  else
  {
    print_usage();
    return (EXIT_FAILURE);
  }
}

static void
print_usage(void)
{
  fprintf(stderr,
          "Usage: blocklist COMMAND [OPTIONS]\n"
          "\n"
          "Commands:\n"
          "download\tDownload blocklists into ~/.local/share/blocklist.\n"
          "emit    \tEmit pf.conf(5) tables to standard output.\n");
}
