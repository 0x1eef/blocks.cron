## About

blocklist.pf is a command line utility that can fetch common IP
blocklists, and from those blocklists create a single PF table
that can be used when crafting firewall rules in `/etc/pf.conf`.
The available blocklists can be found in the
[`blocklists.c`](/src/blocklists.c)
file. The project is written in C, still young, one of my few C
projects, and for now only works on platforms where libfetch is
available (eg FreeBSD).

## Examples

The command line interface:

    # Fetch the blocklists.
    $ blocklist.pf fetch

    # Cat the PF table "<blocklist>" to "/usr/local/share/pf/blocklist.pf"
    $ blocklist.pf cat > /usr/local/share/pf/blocklist.pf

An example of how the table might be used from `/etc/pf.conf`:

    include "/usr/local/share/pf/blocklist.pf"

    block all
    block in quick on ue0 from { <blocklist> } to any
    block out quick on ue0 from any to { <blocklist> }
    pass out on ue0
    pass in on ue0

## Install

    git clone https://github.com/0x1eef/blocklist.pf
    cd blocklist.pf
    make build
    ./bin/blocklist.pf

## Sources

* [Source code (GitHub)](https://github.com/0x1eef/blocklist.pf#readme)
* [Source code (GitLab)](https://gitlab.com/0x1eef/blocklist.pf#about)
* [Source code (HardenedBSD)](https://git.hardenedbsd.org/0x1eef/blocklist.pf#about)

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
