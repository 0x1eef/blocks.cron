## About

blocklist.cron configures
[blocklist](https://github.com/0x1eef/blocklist#readme)
to run at regular intervals (once a day, at 12AM localtime)
via [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).

## Design

* **/home/_blocklist/** <br>
  The [setup/* scripts](setup/) and [bin/setup](bin/setup) create
  a `_blocklist` user, group and environment that's optimized for
  running
  [blocklist](https://github.com/0x1eef/blocklist#readme) via
  [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)). The `/home/_blocklist/`
  directory contains all data and code that is generated or executed via
  [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).

* **/usr/local/share/pf/blocklist** <br>
  This file is the most recent copy of `/home/_blocklist/blocks/YYYY-MM-DD`. It
  contains [pf.conf(5)](https://man.freebsd.org/cgi/man.cgi?pf.conf(5)) tables that
  can be used when when crafting firewall rules in `/etc/pf.conf`. See the
  [blocklist README](https://github.com/0x1eef/blocklist#readme)
  for an example. See [src/home/_blocklist/.local/libexec/copy](src/home/blocklist/.local/libexec/copy)
  to learn how this file is created.

* **/var/cron/tabs/_blocklist** <br>
  [setup/cron.sh](setup/cron.sh) installs this crontab (via bin/setup).
  The crontab executes
  [src/home/bin/run-blocklist](src/home/bin/run-blocklist)
  everyday at 12AM localtime.   See
  [src/var/cron/tabs/_blocklist](src/var/cron/tabs/_blocklist).

* **/var/cron/cron.allow** <br>
  [setup/cron.sh](setup/cron.sh) changes this file only if neccessary.
  The path varies by platform: `/var/cron/cron.allow` (OpenBSD),
  `/var/cron/allow` (FreeBSD).
  See
  [src/var/cron/allow](src/var/cron/allow).

* **doas.conf** <br>
  [setup/doas.sh](setup/doas.sh) changes `doas.conf` to perform operations
  as root and only when neccessary. The creation of `/usr/local/share/pf/blocklist`
  and reloading
  [pf.conf(5)](https://man.freebsd.org/cgi/man.cgi?pf.conf(5))
  require root privileges.
  See [src/usr/local/etc/doas.conf](src/usr/local/etc/doas.conf),
  [src/home/_blocklist/.local/libexec](src/home/_blocklist/.local/libexec), and
  [src/home/_blocklist/bin](src/home/_blocklist/bin).

## Tree

    $ tree -a /home/_blocklist/
    ├── .local
    │   ├── libexec
    │   │   ├── copy
    │   │   └── reload
    │   ├── sh
    │   │   └── today.sh
    │   └── share
    │       └── blocklist
    │           └── .gitkeep
    ├── bin
    │   └── run-blocklist
    ├── blocks
    │   └── .gitkeep
    └── reloads
        └── .gitkeep

## Requirements

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
'
