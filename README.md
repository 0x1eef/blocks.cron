## About

blocklist is a command line utility that can fetch common IP
blocklists, and from those blocklists create PF tables that can
be used when crafting firewall rules in `/etc/pf.conf`.
The available blocklists can be found in the
[`blocklists.c`](/src/blocklists.c)
file. The project is written in C, and depends on
FreeBSD's libfetch but compiles on OpenBSD with
[0x1eef/libfetch](https://github.com/0x1eef/libfetch)
installed.

## Examples

* **CLI**

        # Fetch the blocklist.
        $ blocklist fetch

        # Cat all PF tables to "/usr/local/share/pf/blocklist"
        $ blocklist cat > /usr/local/share/pf/blocklists

* **`/etc/pf.conf`**

        blocklist = "{ <attacks>, <malware>, <reputation>, <anonymizers>, <adware> }"
        include "/usr/local/share/pf/blocklist"

        block all
        block in quick on ue0 from $blocklist to any
        block out quick on ue0 from any to $blocklist
        pass out on ue0
        pass in on ue0

## Details

**Tables**

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

**Paths**

By order of preference, the blocklists that are fetched can be stored in:

* `$BLOCKLIST_DIR`
* Otherwise: `$XDG_DATA_HOME/blocklist/`
* Otherwise: `$HOME/.local/share/blocklist/`
* Otherwise: `/usr/local/share/blocklist/`

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
