#pragma once

typedef struct {
  const char *name;
  const char *desc;
  const char *url;
  const char *path;
  const char *format;
} blocklist;

extern blocklist BLOCKLISTS[10];
