#include <blocklist.pf/blocklist.h>
#include <blocklist.pf/malloc.h>

const char* TABLES[] = {
  "attacks", "malware", "reputation",
  "anonymizers", "adware"
};

blocklist BLOCKLISTS[] = {
  /**
   * table = attacks
   **/
  [0] = {
    .name = "blocklist.de",
    .desc = "A list of IP addresses recommended for block by blocklist.de",
    .table = "attacks",
    .path = "/usr/local/share/pf/blocklists/blocklist.txt",
    .url = "https://lists.blocklist.de/lists/all.txt",
    .format = "ipset"
  },
  [1] = {
    .name = "emergingthreats.net",
    .desc = "A list of IP addresses recommended for block by Emerging Threats",
    .table = "attacks",
    .path = "/usr/local/share/pf/blocklists/emergingthreats_compromised_ips.txt",
    .url = "https://iplists.firehol.org/files/et_compromised.ipset",
    .format = "ipset"
  },
  [2] = {
    .name = "emergingthreats.net",
    .desc = "A list of IP addresses recommended for block by Emerging Threats",
    .table = "attacks",
    .path = "/usr/local/share/pf/blocklists/emergingthreats_block_ips.txt",
    .url = "https://iplists.firehol.org/files/et_block.netset",
    .format = "ipset"
  },
  [3] = {
    .name = "firehol (level 1)",
    .desc = "A list of IP addresses recommended for block by firehol",
    .table = "attacks",
    .path = "/usr/local/share/pf/blocklists/firehol_level1.txt",
    .url = "https://iplists.firehol.org/files/firehol_level1.netset",
    .format = "ipset"
  },
  [4] = {
    .name = "firehol (level 2)",
    .desc = "A list of IP addresses recommended for block by firehol",
    .table = "attacks",
    .path = "/usr/local/share/pf/blocklists/firehol_level2.txt",
    .url = "https://iplists.firehol.org/files/firehol_level2.netset",
    .format = "ipset"
  },
  [5] = {
    .name = "firehol (webserver)",
    .desc = "A list of IP addresses recommended for block by firehol",
    .table = "attacks",
    .path = "/usr/local/share/pf/blocklists/firehol_webserver.txt",
    .url = "https://iplists.firehol.org/files/firehol_webserver.netset",
    .format = "ipset"
  },
  [6] = {
    .name = "blocklist.net.ua",
    .desc = "A list of IP addresses recommended for block by blocklist.net.ua",
    .table = "attacks",
    .path = "/usr/local/share/pf/blocklists/blocklist.net.ua.txt",
    .url = "https://iplists.firehol.org/files/blocklist_net_ua.ipset",
    .format = "ipset"
  },
  /**
   * table = malware
   **/
  [7] = {
    .name = "cybercrime",
    .desc = "A list of IP addresses recommended for block by " \
            "cybercrime-tracker.net",
    .path = "/usr/local/share/pf/blocklists/cybercrime_tracker.txt",
    .table = "malware",
    .url = "https://iplists.firehol.org/files/cybercrime.ipset",
    .format = "ipset"
  },
  /**
   * table = reputation
   **/
  [8] = {
    .name = "binarydefense.com",
    .desc = "A list of IP addresses recommended for block by Binary Defense",
    .table = "reputation",
    .path = "/usr/local/share/pf/blocklists/binarydefense_banlist.txt",
    .url = "https://www.binarydefense.com/banlist.txt",
    .format = "ipset"
  },
  /**
   * table = anonymizers
   **/
  [9] = {
    .name = "Tor exit nodes",
    .desc = "A list of Tor exit nodes provided by the Tor project",
    .path = "/usr/local/share/pf/blocklists/tor_exit_nodes.txt",
    .table = "anonymizers",
    .url = "https://check.torproject.org/torbulkexitlist",
    .format = "ipset"
  },
  /**
   * table = adware
   **/
  [10] = {
    .name = "adservers",
    .desc = "A list of IP addresses associated with adware",
    .path = "/usr/local/share/pf/blocklists/yoyo_adservers.txt",
    .table = "adware",
    .url = "https://pgl.yoyo.org/adservers/iplist.php?ipformat=plain&showintro=0&mimetype=plaintext",
    .format = "ipset"
  },
};

htable*
group_blocklists_by_category(blocklist blocklists[], size_t size) {
  htable *table;
  dyn_array *ary;
  table = safe_malloc(sizeof(htable));
  hcreate_r(0, table);
  for(int i = 0; i < (int)(size); i++) {
    hitem *item, *fitem;
    blocklist *bl;
    bl = &blocklists[i];
    item = safe_malloc(sizeof(hitem));
    item->key = (char*)bl->table;
    if(hsearch_r(*item, FIND, &fitem, table) == 0) {
      ary = array_init();
      array_push(ary, bl);
      item->data = ary;
      hsearch_r(*item, ENTER, &fitem, table);
    } else {
      array_push(ary, bl);
      fitem->data = ary;
    }
  }
  return table;
}
