#pragma once
#include <blocklist.pf/buffer.h>
buffer* read_file(const char *path, int maxl, int maxw);
int write_file(const char *path, buffer *buf);
