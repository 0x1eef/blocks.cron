#include <blocklist/alloc.h>
#include <blocklist/blocklists.h>
#include <string.h>
#include <stdio.h>
#include <sys/param.h>
#include <curl/curl.h>

static struct blocklist BLOCKLISTS[] = {
    /**
     * table = attacks
     **/
    [0] = {.name  = "firehol (level 1)",
           .desc  = "An IP blocklist that's suitable for basic protection on "
                    "all internet facing servers, routers and firewalls.",
           .table = "attacks",
           .filename = "attacks_firehol1.txt",
           .url = "https://iplists.firehol.org/files/firehol_level1.netset",
           .about_url = "https://iplists.firehol.org/?ipset=firehol_level1",
           .format    = "netset",
           .enabled   = true,
           .path      = blocklist_path,
           .store     = blocklist_store},
    [1] = {.name     = "firehol (web server)",
           .desc     = "An IP blocklist made from blocklists that track IPs "
                       "a web server should never talk to.",
           .table    = "attacks",
           .filename = "attacks_fireholwebserver.txt",
           .url = "https://iplists.firehol.org/files/firehol_webserver.netset",
           .about_url = "https://iplists.firehol.org/?ipset=firehol_webserver",
           .format    = "netset",
           .enabled   = true,
           .path      = blocklist_path,
           .store     = blocklist_store},

    /**
     * table = malware
     **/
    [2] = {.name     = "firehol (web browser)",
           .desc     = "An IP blocklist made from blocklists that track IPs "
                       "a web browser should never talk to.",
           .filename = "malware_fireholwebclient.txt",
           .table    = "malware",
           .url = "https://iplists.firehol.org/files/firehol_webclient.netset",
           .about_url = "https://iplists.firehol.org/?ipset=firehol_webclient",
           .format    = "netset",
           .enabled   = true,
           .path      = blocklist_path,
           .store     = blocklist_store},

    /**
     * table = anonymizers
     **/
    [3] = {.name      = "TOR exit nodes",
           .desc      = "An IP blocklist of TOR exit nodes.",
           .filename  = "anonymizers_torexit.txt",
           .table     = "anonymizers",
           .url       = "https://iplists.firehol.org/files/tor_exits.ipset",
           .about_url = "https://iplists.firehol.org/?ipset=tor_exits",
           .format    = "ipset",
           .enabled   = true,
           .path      = blocklist_path,
           .store     = blocklist_store},

    /**
     * table = adware
     **/
    [4] = {.name     = "adservers",
           .desc     = "An IP blocklist of ad servers.",
           .filename = "adware_yoyoadservers.txt",
           .table    = "adware",
           .url      = "https://iplists.firehol.org/files/yoyo_adservers.ipset",
           .about_url = "https://iplists.firehol.org/?ipset=yoyo_adservers",
           .format    = "ipset",
           .enabled   = true,
           .path      = blocklist_path,
           .store     = blocklist_store},

    /**
     * Terminates the array. DO NOT REMOVE.
     **/
    [5] = NULL_BLOCKLIST};

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
  enabled = alloc(sizeof(struct blocklist) * (size + 1));
  dest    = enabled;
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
  disabled = alloc(sizeof(struct blocklist) * (size + 1));
  dest     = disabled;
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
blocklists_group(struct blocklist blocklist[], const char *table)
{
  struct blocklist *group;
  struct blocklist *dest;
  size_t size;
  size  = blocklists_size(blocklist);
  group = alloc(sizeof(struct blocklist) * (size + 1));
  dest  = group;
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
  return (group);
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
