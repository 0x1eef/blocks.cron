#include "blocklist.h"

struct blocklist* blocklists_all(const char*);
struct blocklist* blocklists_enabled(struct blocklist[]);
struct blocklist* blocklists_disabled(struct blocklist[]);
struct blocklist* blocklists_group(struct blocklist[], const char*);
size_t blocklists_size(struct blocklist[]);
