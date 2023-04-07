#pragma once
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <fetch.h>
#include <stdlib.h>
#include <blocklist.pf/buffer.h>
#include <blocklist.pf/file.h>
#include <blocklist.pf/blocklist.h>
buffer* fetch_blocklist(blocklist *bl, int maxrows, int maxcols);
