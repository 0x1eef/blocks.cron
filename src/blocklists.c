#include <blocklist/blocklist.h>
#include <blocklist/malloc.h>

const char *TABLES[] =
{
  "attacks",     "malware",     "reputation",
  "anonymizers", "adware",      NULL
};

blocklist BLOCKLISTS[] =
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
         .enabled  = true
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
         .enabled  = true
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
         .enabled  = true
         },
  [3] =
         {
         .name     = "firehol (level 1)",
         .desc     = "A list of IP addresses recommended for block by firehol",
         .table    = "attacks",
         .filename = "attacks_firehol1.txt",
         .url      = "https://iplists.firehol.org/files/firehol_level1.netset",
         .format   = "ipset",
         .enabled  = true
         },
  [4] =
         {
         .name     = "firehol (level 2)",
         .desc     = "A list of IP addresses recommended for block by firehol",
         .table    = "attacks",
         .filename = "attacks_firehol2.txt",
         .url      = "https://iplists.firehol.org/files/firehol_level2.netset",
         .format   = "ipset",
         .enabled  = true
         },
  [5] =
         {
         .name     = "firehol (webserver)",
         .desc     = "A list of IP addresses recommended for block by firehol",
         .table    = "attacks",
         .filename = "attacks_fireholwebserver.txt",
         .url      =
           "https://iplists.firehol.org/files/firehol_webserver.netset",
         .format   = "ipset",
         .enabled  = true
         },
  [6] =
         {
         .name     = "blocklist.net.ua",
         .desc     =
           "A list of IP addresses recommended for block by blocklist.net.ua",
         .table    = "attacks",
         .filename = "attacks_blocklist.net.ua.txt",
         .url      = "https://iplists.firehol.org/files/blocklist_net_ua.ipset",
         .format   = "ipset",
         .enabled  = true
         },

  /**
   * table = malware
   **/
  [7] =
         {
         .name     = "cybercrime",
         .desc     =
           "A list of IP addresses recommended for block by cybercrime-tracker.net",
         .filename = "malware_cybercrimetracker.txt",
         .table    = "malware",
         .url      = "https://iplists.firehol.org/files/cybercrime.ipset",
         .format   = "ipset",
         .enabled  = true
         },

  /**
   * table = reputation
   **/
  [8] =
         {
         .name     = "binarydefense.com",
         .desc     =
           "A list of IP addresses recommended for block by Binary Defense",
         .table    = "reputation",
         .filename = "reputation_binarydefensebanlist.txt",
         .url      = "https://www.binarydefense.com/banlist.txt",
         .format   = "ipset",
         .enabled  = true
         },

  /**
   * table = anonymizers
   **/
  [9] =
         {
         .name     = "Tor network nodes",
         .desc     =
           "A list of Tor network nodes provided by emergingthreats.net",
         .filename = "anonymizers_tornetworknodes.txt",
         .table    = "anonymizers",
         .url      = "https://iplists.firehol.org/files/et_tor.ipset",
         .format   = "ipset",
         .enabled  = true
         },

  /**
   * table = adware
   **/
  [10] =
         {
         .name     = "adservers",
         .desc     = "A list of IP addresses associated with adware",
         .filename = "adware_yoyoadservers.txt",
         .table    = "adware",
         .url      =
           "https://pgl.yoyo.org/adservers/iplist.php?ipformat=plain&showintro=0&mimetype=plaintext",
         .format   = "ipset",
         .enabled  = true
         },
  [11] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL }
};

dyn_array *
group_blocklists(const char *tbl)
{
  dyn_array *group;
  blocklist *b;

  group = array_init();
  b = &BLOCKLISTS[0];
  while (b->name != NULL)
  {
    if (strncmp(b->table, tbl, strlen(b->table)) == 0) {
      array_push(group, b);
    }
    b++;
  }
  return (group);
}
