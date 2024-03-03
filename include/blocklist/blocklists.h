#include "blocklist.h"

extern const char* TABLES[];
extern struct blocklist BLOCKLISTS[];
struct blocklist* blocklists_enabled(struct blocklist*);
struct blocklist* blocklists_disabled(struct blocklist*);
size_t blocklists_count(struct blocklist*);
