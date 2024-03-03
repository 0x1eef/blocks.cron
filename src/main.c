#include <blocklist/command.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
static void print_usage(void);

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    print_usage();
  } else if (strcmp(argv[1], "download") == 0) {
    return (download_command());
  } else if (strcmp(argv[1], "echo") == 0) {
    return (echo_command());
  } else {
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
    "download\tDownload blocklists.\n"
    "echo    \tEcho blocklists as PF tables to standard output.\n"
  );
  exit(EXIT_FAILURE);
}
