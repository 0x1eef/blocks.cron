#include <blocklist.pf/blocklist.h>

blocklist BLOCKLISTS[] = {
  [0] = {
    .name = "blocklist.de",
    .desc = "A list of IP addresses recommended for block by blocklist.de.",
    .path = "/usr/local/share/pf/blocklists/blocklist.txt",
    .url = "https://lists.blocklist.de/lists/all.txt",
    .format = "ipset"
  },
  [1] = {
    .name = "BinaryDefense.com",
    .desc = "A list of IP addresses recommended for block by BinaryDefense.",
    .path = "/usr/local/share/pf/blocklists/binarydefense_banlist.txt",
    .url = "https://www.binarydefense.com/banlist.txt",
    .format = "ipset"
  },
  [2] = {
    .name = "EmergingThreats.net",
    .desc = "A list of IP addresses recommended for block by EmergingThreats.",
    .path = "/usr/local/share/pf/blocklists/emergingthreats_compromised_ips.txt",
    .url = "https://rules.emergingthreats.net/blockrules/compromised-ips.txt",
    .format = "ipset"
  },
  [3] = {
    .name = "EmergingThreats.net",
    .desc = "A list of IP addresses recommended for block by EmergingThreats.",
    .path = "/usr/local/share/pf/blocklists/emergingthreats_block_ips.txt",
    .url = "https://rules.emergingthreats.net/fwrules/emerging-Block-IPs.txt",
    .format = "ipset"
  },
  [4] = {
    .name = "Firehol (LEVEL 1)",
    .desc = "A list of IP addresses recommended for block by Firehol.",
    .path = "/usr/local/share/pf/blocklists/firehol_level1.txt",
    .url = "https://iplists.firehol.org/files/firehol_level1.netset",
    .format = "ipset"
  },
  [5] = {
    .name = "Firehol (LEVEL 2)",
    .desc = "A list of IP addresses recommended for block by Firehol.",
    .path = "/usr/local/share/pf/blocklists/firehol_level2.txt",
    .url = "https://iplists.firehol.org/files/firehol_level2.netset",
    .format = "ipset"
  },
  [6] = {
    .name = "Firehol (webserver)",
    .desc = "A list of IP addresses recommended for block by Firehol.",
    .path = "/usr/local/share/pf/blocklists/firehol_webserver.txt",
    .url = "https://iplists.firehol.org/files/firehol_webserver.netset",
    .format = "ipset"
  },
  [7] = {
    .name = "CyberCrime",
    .desc = "A list of IP addresses recommended for block by cybercrime-tracker.net",
    .path = "/usr/local/share/pf/blocklists/cybercrime_tracker.txt",
    .url = "https://iplists.firehol.org/files/cybercrime.ipset",
    .format = "ipset"
  },
  [8] = {
    .name = "Tor exit nodes",
    .desc = "A list of Tor exit nodes provided by the Tor project",
    .path = "/usr/local/share/pf/blocklists/tor_exit_nodes.txt",
    .url = "https://check.torproject.org/torbulkexitlist",
    .format = "ipset"
  },
  [9] = {
    .name = "adservers",
    .desc = "A list of IP addresses serving ads.",
    .path = "/usr/local/share/pf/blocklists/yoyo_adservers.txt",
    .url = "https://pgl.yoyo.org/adservers/iplist.php?ipformat=plain&showintro=0&mimetype=plaintext",
    .format = "ipset"
  },
};
