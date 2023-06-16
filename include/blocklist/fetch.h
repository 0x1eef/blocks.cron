#pragma once
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <fetch.h>
#include <stdlib.h>
#include <blocklist/dyn_array.h>
#include <blocklist/file.h>
#include <blocklist/blocklist.h>
dyn_array* fetch_blocklist(blocklist *bl);
