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
  printf("Usage: blocklist download|echo [OPTIONS]\n");
  exit(EXIT_FAILURE);
}
