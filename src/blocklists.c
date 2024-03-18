#include <blocklist/alloc.h>
#include <blocklist/blocklists.h>
#include <string.h>
#include <stdio.h>
#include <sys/param.h>
#include <fetch.h>

const char *TABLES[] = {
    "attacks", "malware", "reputation", "anonymizers", "adware", NULL};

static struct blocklist BLOCKLISTS[] = {
    /**
     * table = attacks
     **/
    [0] = {.name  = "blocklist.de",
           .desc  = "A list of IP addresses that have been seen by fail2ban in "
                    "the last 48 hours.",
           .table = "attacks",
           .filename  = "attacks_blocklist.de.txt",
           .url       = "https://iplists.firehol.org/files/blocklist_de.ipset",
           .about_url = "https://iplists.firehol.org/?ipset=blocklist_de",
           .format    = "ipset",
           .enabled   = true,
           .get       = blocklist_get,
           .path      = blocklist_path,
           .write     = blocklist_write},
    [1] = {.name     = "emergingthreats.net",
           .desc     = "A list of IP addresses that have been reported to be "
                       "'significantly infected and hostile'.",
           .table    = "attacks",
           .filename = "attacks_etcompromised.txt",
           .url      = "https://iplists.firehol.org/files/et_compromised.ipset",
           .about_url = "https://iplists.firehol.org/?ipset=et_compromised",
           .format    = "ipset",
           .enabled   = true,
           .get       = blocklist_get,
           .path      = blocklist_path,
           .write     = blocklist_write},
    [2] = {.name = "firehol (level 1)",
           .desc = "A list of IP addresses recommended for block in nearly all "
                   "circumstances.",
           .table    = "attacks",
           .filename = "attacks_firehol1.txt",
           .url = "https://iplists.firehol.org/files/firehol_level1.netset",
           .about_url = "https://iplists.firehol.org/?ipset=firehol_level1",
           .format    = "ipset",
           .enabled   = true,
           .get       = blocklist_get,
           .path      = blocklist_path,
           .write     = blocklist_write},
    [3] = {.name  = "firehol (webserver)",
           .desc  = "A list of IP addresses that web servers shouldn't be in "
                    "communication with.",
           .table = "attacks",
           .filename = "attacks_fireholwebserver.txt",
           .url = "https://iplists.firehol.org/files/firehol_webserver.netset",
           .about_url = "https://iplists.firehol.org/?ipset=firehol_webserver",
           .format    = "ipset",
           .enabled   = true,
           .get       = blocklist_get,
           .path      = blocklist_path,
           .write     = blocklist_write},

    /**
     * table = malware
     **/
    [4] = {.name      = "cybercrime",
           .desc      = "A list of IP addresses recommended for block by "
                        "cybercrime-tracker.net",
           .filename  = "malware_cybercrimetracker.txt",
           .table     = "malware",
           .url       = "https://iplists.firehol.org/files/cybercrime.ipset",
           .about_url = "https://iplists.firehol.org/?ipset=cybercrime",
           .format    = "ipset",
           .enabled   = true,
           .get       = blocklist_get,
           .path      = blocklist_path,
           .write     = blocklist_write},

    /**
     * table = anonymizers
     **/
    [5] = {.name = "Tor network nodes",
           .desc =
               "A list of Tor network nodes provided by emergingthreats.net",
           .filename = "anonymizers_tornetworknodes.txt",
           .table    = "anonymizers",
           .url      = "https://iplists.firehol.org/files/et_tor.ipset",
           .format   = "ipset",
           .enabled  = true,
           .get      = blocklist_get,
           .path     = blocklist_path,
           .write    = blocklist_write},

    /**
     * table = adware
     **/
    [6] = {.name     = "adservers",
           .desc     = "A list of IP addresses associated with adware",
           .filename = "adware_yoyoadservers.txt",
           .table    = "adware",
           .url      = "https://pgl.yoyo.org/adservers/"
                       "iplist.php?ipformat=plain&showintro=0&mimetype=plaintext",
           .format   = "ipset",
           .enabled  = true,
           .get      = blocklist_get,
           .path     = blocklist_path,
           .write    = blocklist_write},

    /**
     * Terminates the array. DO NOT REMOVE.
     **/
    [7] = NULL_BLOCKLIST};

struct blocklist *
blocklists_all(const char *state)
{
    if (strcmp(state, "enabled") == 0)
    {
        return (blocklists_enabled(BLOCKLISTS));
    }
    else if (strcmp(state, "disabled") == 0)
    {
        return (blocklists_disabled(BLOCKLISTS));
    }
    else
    {
        return (NULL);
    }
}

struct blocklist *
blocklists_enabled(struct blocklist blocklist[])
{
    struct blocklist *enabled;
    struct blocklist *dest;
    size_t size;
    size    = blocklists_size(blocklist);
    enabled = alloc(sizeof(struct blocklist) * size);
    dest    = &enabled[0];
    while (blocklist->name != NULL)
    {
        if (blocklist->enabled)
        {
            *dest = *blocklist;
            dest++;
        }
        blocklist++;
    }
    *dest = NULL_BLOCKLIST;
    return (enabled);
}

struct blocklist *
blocklists_disabled(struct blocklist blocklist[])
{
    struct blocklist *disabled;
    struct blocklist *dest;
    size_t size;
    size     = blocklists_size(blocklist);
    disabled = alloc(sizeof(struct blocklist) * size);
    dest     = &disabled[0];
    while (blocklist->name != NULL)
    {
        if (!blocklist->enabled)
        {
            *dest = *blocklist;
            dest++;
        }
        blocklist++;
    }
    *dest = NULL_BLOCKLIST;
    return (disabled);
}

struct blocklist *
blocklists_by_table(struct blocklist blocklist[], const char *table)
{
    struct blocklist *by_table;
    struct blocklist *dest;
    size_t size;
    size     = blocklists_size(blocklist);
    by_table = alloc(sizeof(struct blocklist) * size);
    dest     = &by_table[0];
    while (blocklist->name != NULL)
    {
        if (strcmp(blocklist->table, table) == 0)
        {
            *dest = *blocklist;
            dest++;
        }
        blocklist++;
    }
    *dest = NULL_BLOCKLIST;
    return (by_table);
}

size_t
blocklists_size(struct blocklist blocklist[])
{
    size_t size = 0;
    while (blocklist->name != NULL)
    {
        size++;
        blocklist++;
    }
    return (size);
}
