## About

blocklist.cron is a collection of POSIX shell scripts that
configure
[blocklist](https://github.com/0x1eef/blocklist#readme)
to run at regular intervals (once a day, at 12AM localtime).
The goal of the project is to reduce the manual effort involved
in running
[blocklist](https://github.com/0x1eef/blocklist#readme)
via cron(8). The same platforms supported by
[blocklist](https://github.com/0x1eef/blocklist#readme)
are supported by blocklist.cron: FreeBSD, HardenedBSD, and
OpenBSD.

## Design

**/home/_blocklist/**

blocklist.cron creates a `_blocklist` user, and group. <br>
The `/home/_blocklist/` directory stores:

* `/home/_blocklist/blocklists/YYYY-MM-DD` <br>
  A file that contains a collection of PF tables for a given day.

* `/home/_blocklist/reloads/YYYY-MM-DD` <br>
  A file that is created once pfctl reloads `/etc/pf.conf` successfully
  on a given day.

**/usr/local/share/pf/blocklists**

This file is the most recent copy of `/home/_blocklist/blocklists/YYYY-MM-DD`,
and it is intended to be included when crafting firewall rules in `/etc/pf.conf`.
See the
[blocklist](https://github.com/0x1eef/blocklist#readme)
README for an example.

**/var/cron/tabs/_blocklist**

blocklist.cron installs a crontab entry for the `_blocklist` user. <br>
See [src/var/cron/tabs/_blocklist](src/var/cron/tabs/_blocklist).

**/var/cron/cron.allow**

blocklist.cron adds the `_blocklist` user to `/var/cron/cron.allow` on OpenBSD,
and `/var/cron/allow` on FreeBSD. This is required on OpenBSD, but not neccessarily
required on FreeBSD. See [src/var/cron/allow](src/var/cron/allow).

**doas.conf**

blocklist.cron updates `doas.conf` to perform certain operations as root.
The executables that are run with root privileges can only be edited by root.
See [src/usr/local/etc/doas.conf](src/usr/local/etc/doas.conf),
[src/home/_blocklist/libexec](src/home/_blocklist/libexec), and
[src/home/_blocklist/bin](src/home/_blocklist/bin).

## Requirements

Runtime requirements:

* [blocklist](https://github.com/0x1eef/blocklist#readme)
* doas
* pfctl

## Install

    # Clone repository
    $ git clone https://github.com/0x1eef/blocklist.cron
    $ cd blocklist.cron

    # Install (as root)
    # ./bin/setup

## Sources

* [GitHub](https://github.com/0x1eef/blocklist.cron)
* [GitLab](https://gitlab.com/0x1eef/blocklist.cron)
* [git.hardenedbsd.org](https://git.hardenedbsd.org/0x1eef/blocklist.cron)

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
