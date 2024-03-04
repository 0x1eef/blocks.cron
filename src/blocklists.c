#include <blocklist/blocklists.h>
#include <blocklist/smalloc.h>
#include <sys/param.h>
#include <time.h>
#include <fetch.h>

const char *TABLES[] =
{
  "attacks",     "malware",     "reputation",
  "anonymizers", "adware",      NULL
};

struct blocklist BLOCKLISTS[] =
{
  /**
   * table = attacks
   **/
  [0] =
  {
  .name      = "blocklist.de",
  .desc      =
    "A list of IP addresses that have been seen by fail2ban in the last 48 hours.",
  .table     = "attacks",
  .filename  = "attacks_blocklist.de.txt",
  .url       = "https://lists.blocklist.de/lists/all.txt",
  .about_url = "https://iplists.firehol.org/?ipset=blocklist_de",
  .format    = "ipset",
  .enabled   = true,
  .get       = blocklist_get,
  .path      = blocklist_path,
  .write     = blocklist_write
  },
  [1] =
  {
  .name      = "emergingthreats.net",
  .desc      =
    "A list of IP addresses that have been reported to be 'significantly infected and hostile'.",
  .table     = "attacks",
  .filename  = "attacks_etcompromised.txt",
  .url       = "https://iplists.firehol.org/files/et_compromised.ipset",
  .about_url = "https://iplists.firehol.org/?ipset=et_compromised",
  .format    = "ipset",
  .enabled   = true,
  .get       = blocklist_get,
  .path      = blocklist_path,
  .write     = blocklist_write
  },
  [2] =
  {
  .name      = "firehol (level 1)",
  .desc      =
    "A list of IP addresses recommended for block in nearly all circumstances.",
  .table     = "attacks",
  .filename  = "attacks_firehol1.txt",
  .url       = "https://iplists.firehol.org/files/firehol_level1.netset",
  .about_url = "https://iplists.firehol.org/?ipset=firehol_level1",
  .format    = "ipset",
  .enabled   = true,
  .get       = blocklist_get,
  .path      = blocklist_path,
  .write     = blocklist_write
  },
  [3] =
  {
  .name      = "firehol (webserver)",
  .desc      =
    "A list of IP addresses that web servers shouldn't be in communication with.",
  .table     = "attacks",
  .filename  = "attacks_fireholwebserver.txt",
  .url       =
    "https://iplists.firehol.org/files/firehol_webserver.netset",
  .about_url = "https://iplists.firehol.org/?ipset=firehol_webserver",
  .format    = "ipset",
  .enabled   = true,
  .get       = blocklist_get,
  .path      = blocklist_path,
  .write     = blocklist_write
  },

  /**
   * table = malware
   **/
  [4] =
  {
  .name      = "cybercrime",
  .desc      =
    "A list of IP addresses recommended for block by cybercrime-tracker.net",
  .filename  = "malware_cybercrimetracker.txt",
  .table     = "malware",
  .url       = "https://iplists.firehol.org/files/cybercrime.ipset",
  .about_url = "https://iplists.firehol.org/?ipset=cybercrime",
  .format    = "ipset",
  .enabled   = true,
  .get       = blocklist_get,
  .path      = blocklist_path,
  .write     = blocklist_write
  },

  /**
   * table = reputation
   **/
  [5] =
  {
  .name      = "binarydefense.com",
  .desc      =
    "A list of IP addresses recommended for block by Binary Defense",
  .table     = "reputation",
  .filename  = "reputation_binarydefensebanlist.txt",
  .url       = "https://www.binarydefense.com/banlist.txt",
  .about_url = "https://www.binarydefense.com",
  .format    = "ipset",
  .enabled   = true,
  .get       = blocklist_get,
  .path      = blocklist_path,
  .write     = blocklist_write
  },

  /**
   * table = anonymizers
   **/
  [6] =
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
  [7] =
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
  [8] = NULL_BLOCKLIST
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
