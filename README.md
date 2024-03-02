## About

blocklist is a command line utility that can fetch common IPv4
blocklists, and from those blocklists create PF tables that can
be used when crafting firewall rules in `/etc/pf.conf`.
The available blocklists can be found in the
[`blocklists.c`](/src/blocklists.c)
file.

## Examples

* **CLI**

        # Download blocklists to ~/.local/share/blocklist/
        $ blocklist download

        # Echo PF tables to "/usr/local/share/pf/blocklists"
        $ blocklist echo > /usr/local/share/pf/blocklists

* **`/etc/pf.conf`**

        blocklists = "{ <attacks>, <malware>, <reputation>, <anonymizers>, <adware> }"
        include "/usr/local/share/pf/blocklists"

        block all
        block in quick on ue0 from $blocklists to any
        block out quick on ue0 from any to $blocklists
        pass out on ue0
        pass in on ue0

## PF tables

**Names**

The following PF tables are available:

* __&lt;attacks&gt;__ <br>
  A table of IP addresses reported to be associated with attacks (eg brute force attacks).
* __&lt;malware&gt;__ <br>
  A table of IP addresses reported to be associated with malware.
* __&lt;reputation&gt;__ <br>
  A table of IP addresses reported to be associated with suspicous or malicious activity.
* __&lt;anonymizers&gt;__ <br>
  A table of IP addresses reported to be associated with anonymity (eg Tor).
* __&lt;adware&gt;__ <br>
  A table of IP addreses reported to be associated with adware.

## Install

    $ git clone https://github.com/0x1eef/blocklist
    $ cd blocklist
    $ make build
    $ ./bin/blocklist

## Sources

* [Source code (GitHub)](https://github.com/0x1eef/blocklist#readme)
* [Source code (GitLab)](https://gitlab.com/0x1eef/blocklist#about)
* [Source code (HardenedBSD)](https://git.hardenedbsd.org/0x1eef/blocklist#about)

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
