#include <blocklist/blocklists.h>
#include <blocklist/smalloc.h>
#include <sys/param.h>
#include <time.h>
#include <fetch.h>

const char *TABLES[] =
{
  "attacks",     "malware", "reputation",
  "anonymizers", "adware",  NULL
};

struct blocklist BLOCKLISTS[] =
{
  /**
   * table = attacks
   **/
  [0] =
  {
  .name     = "blocklist.de",
  .desc     =
    "A list of IP addresses recommended for block by blocklist.de",
  .table    = "attacks",
  .filename = "attacks_blocklist.de.txt",
  .url      = "https://lists.blocklist.de/lists/all.txt",
  .format   = "ipset",
  .enabled  = true,
  .get      = blocklist_get,
  .path     = blocklist_path,
  .write    = blocklist_write
  },
  [1] =
  {
  .name     = "emergingthreats.net",
  .desc     =
    "A list of IP addresses recommended for block by Emerging Threats",
  .table    = "attacks",
  .filename = "attacks_etcompromised.txt",
  .url      = "https://iplists.firehol.org/files/et_compromised.ipset",
  .format   = "ipset",
  .enabled  = true,
  .get      = blocklist_get,
  .path     = blocklist_path,
  .write    = blocklist_write
  },
  [2] =
  {
  .name     = "emergingthreats.net",
  .desc     =
    "A list of IP addresses recommended for block by Emerging Threats",
  .table    = "attacks",
  .filename = "attacks_etblock.txt",
  .url      = "https://iplists.firehol.org/files/et_block.netset",
  .format   = "ipset",
  .enabled  = true,
  .get      = blocklist_get,
  .path     = blocklist_path,
  .write    = blocklist_write
  },
  [3] =
  {
  .name     = "firehol (level 1)",
  .desc     = "A list of IP addresses recommended for block by firehol",
  .table    = "attacks",
  .filename = "attacks_firehol1.txt",
  .url      = "https://iplists.firehol.org/files/firehol_level1.netset",
  .format   = "ipset",
  .enabled  = true,
  .get      = blocklist_get,
  .path     = blocklist_path,
  .write    = blocklist_write
  },
  [4] =
  {
  .name     = "firehol (webserver)",
  .desc     = "A list of IP addresses recommended for block by firehol",
  .table    = "attacks",
  .filename = "attacks_fireholwebserver.txt",
  .url      =
    "https://iplists.firehol.org/files/firehol_webserver.netset",
  .format   = "ipset",
  .enabled  = true,
  .get      = blocklist_get,
  .path     = blocklist_path,
  .write    = blocklist_write
  },

  /**
   * table = malware
   **/
  [5] =
  {
  .name     = "cybercrime",
  .desc     =
    "A list of IP addresses recommended for block by cybercrime-tracker.net",
  .filename = "malware_cybercrimetracker.txt",
  .table    = "malware",
  .url      = "https://iplists.firehol.org/files/cybercrime.ipset",
  .format   = "ipset",
  .enabled  = true,
  .get      = blocklist_get,
  .path     = blocklist_path,
  .write    = blocklist_write
  },

  /**
   * table = reputation
   **/
  [6] =
  {
  .name     = "binarydefense.com",
  .desc     =
    "A list of IP addresses recommended for block by Binary Defense",
  .table    = "reputation",
  .filename = "reputation_binarydefensebanlist.txt",
  .url      = "https://www.binarydefense.com/banlist.txt",
  .format   = "ipset",
  .enabled  = true,
  .get      = blocklist_get,
  .path     = blocklist_path,
  .write    = blocklist_write
  },

  /**
   * table = anonymizers
   **/
  [7] =
  {
  .name     = "Tor network nodes",
  .desc     =
    "A list of Tor network nodes provided by emergingthreats.net",
  .filename = "anonymizers_tornetworknodes.txt",
  .table    = "anonymizers",
  .url      = "https://iplists.firehol.org/files/et_tor.ipset",
  .format   = "ipset",
  .enabled  = true,
  .get      = blocklist_get,
  .path     = blocklist_path,
  .write    = blocklist_write
  },

  /**
   * table = adware
   **/
  [8] =
  {
  .name     = "adservers",
  .desc     = "A list of IP addresses associated with adware",
  .filename = "adware_yoyoadservers.txt",
  .table    = "adware",
  .url      =
    "https://pgl.yoyo.org/adservers/iplist.php?ipformat=plain&showintro=0&mimetype=plaintext",
  .format   = "ipset",
  .enabled  = true,
  .get      = blocklist_get,
  .path     = blocklist_path,
  .write    = blocklist_write
  },

  /**
   * Terminates the array. DO NOT REMOVE.
   **/
  [9] = NULL_BLOCKLIST
};

struct blocklist *
blocklists_enabled(struct blocklist *blocklists)
{
  struct blocklist *enabled = smalloc(
    sizeof(struct blocklist) * blocklists_count(&blocklists[0])
    );
  struct blocklist
  *e = &enabled[0],
    *b = &blocklists[0];
  while (b->name != NULL)
  {
    if (b->enabled) {
      *e = *b;
      e++;
    }
    b++;
  }
  *e = NULL_BLOCKLIST;
  return (enabled);
}


struct blocklist *
blocklists_disabled(struct blocklist *blocklists)
{
  struct blocklist *disabled = smalloc(
    sizeof(struct blocklist) * blocklists_count(&blocklists[0])
    );
  struct blocklist
  *d = &disabled[0],
    *b = &blocklists[0];
  while (b->name != NULL)
  {
    if (!b->enabled) {
      *d = *b;
      d++;
    }
    b++;
  }
  *d = NULL_BLOCKLIST;
  return (disabled);
}


size_t
blocklists_count(struct blocklist *blocklists)
{
  struct blocklist *b = &blocklists[0];
  size_t count = 0;
  while (b->name != NULL)
  {
    count++;
    b++;
  }
  return (count);
}
