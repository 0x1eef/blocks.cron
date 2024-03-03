#include <blocklist/blocklist.h>
#include <blocklist/smalloc.h>
#include <sys/param.h>
#include <time.h>
#include <fetch.h>

static char * path(struct blocklist *);
static int write(struct blocklist *, FILE *);
static FILE * get(struct blocklist *);

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
  .get      = get,
  .path     = path,
  .write    = write
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
  .get      = get,
  .path     = path,
  .write    = write
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
  .get      = get,
  .path     = path,
  .write    = write
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
  .get      = get,
  .path     = path,
  .write    = write
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
  .get      = get,
  .path     = path,
  .write    = write
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
  .get      = get,
  .path     = path,
  .write    = write
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
  .get      = get,
  .path     = path,
  .write    = write
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
  .get      = get,
  .path     = path,
  .write    = write
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
  .get      = get,
  .path     = path,
  .write    = write
  },

  /**
   * Terminates the array. DO NOT REMOVE.
   **/
  [9] = NULL_BLOCKLIST
};

static char *
path(struct blocklist *b)
{
  char *home = getenv("HOME");
  if (home) {
    char *relpath, *fullpath;
    size_t bufsize, offset1, offset2;
    relpath = "/.local/share/blocklist/";
    offset1 = strlen(home);
    offset2 = strlen(relpath);
    bufsize = offset1 + offset2 + strlen(b->filename) + 1;
    fullpath = smalloc(sizeof(char) * bufsize);
    memcpy(&fullpath[0], home, offset1);
    memcpy(&fullpath[offset1], relpath, offset2);
    memcpy(&fullpath[offset1 + offset2], b->filename, strlen(b->filename) + 1);
    return (fullpath);
  } else {
    return ("/usr/local/share/pf/blocklist");
  }
}


static int
write(struct blocklist *b, FILE *stream)
{
  char *path = b->path(b);
  FILE *file = fopen(path, "wb");
  if (file == NULL) {
    return (0);
  } else {
    char buf[1];
    while (fread(&buf, 1, 1, stream) != 0)
    {
      fwrite(&buf, 1, 1, file);
    }
    fclose(file);
    fclose(stream);
    return (1);
  }
}


static FILE *
get(struct blocklist *b)
{
  struct url *url;
  FILE *stream;
  url = fetchParseURL(b->url);
  stream = fetchGetHTTP(url, "");
  fetchFreeURL(url);
  return (stream);
}
