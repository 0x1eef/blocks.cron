## About

blocklist.cron configures
[blocklist](https://github.com/0x1eef/blocklist#readme)
to run at regular intervals (once a day, at 12AM localtime).
The goal of the project is to automate running
[blocklist](https://github.com/0x1eef/blocklist#readme),
via [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).

## Design

* **/home/_blocklist/** <br>
  [bin/setup](bin/setup) creates a `_blocklist` user, and group. <br>
  The **/home/_blocklist/** directory stores:
    * `/home/_blocklist/blocklists/YYYY-MM-DD` <br>
    A file that contains a collection of PF tables for a given day.
    * `/home/_blocklist/reloads/YYYY-MM-DD` <br>
    A file that is created once pfctl reloads `/etc/pf.conf` successfully
    on a given day.
* **/usr/local/share/pf/blocklists** <br>
  This file is the most recent copy of `/home/_blocklist/blocklists/YYYY-MM-DD`,
  and it is intended to be included when crafting firewall rules in `/etc/pf.conf`.
  See the
  [blocklist README](https://github.com/0x1eef/blocklist#readme)
  for an example.
* **/var/cron/tabs/_blocklist** <br>
  blocklist.cron installs a crontab entry for the `_blocklist` user. <br>
  See [src/var/cron/tabs/_blocklist](src/var/cron/tabs/_blocklist).
* **/var/cron/cron.allow** <br>
  blocklist.cron adds the `_blocklist` user to `/var/cron/cron.allow` (OpenBSD),
  or `/var/cron/allow` (FreeBSD) if that file is found to already exist.
  See [src/var/cron/allow](src/var/cron/allow).
* **doas.conf** <br>
  blocklist.cron updates `doas.conf` to perform certain operations as root.
  The executables that are run with root privileges can only be edited by root.
  See [src/usr/local/etc/doas.conf](src/usr/local/etc/doas.conf),
  [src/home/_blocklist/.local/libexec](src/home/_blocklist/.local/libexec), and
  [src/home/_blocklist/bin](src/home/_blocklist/bin).

## Tree

    $ tree -a /home/_blocklist/
    /home/_blocklist/
    ├── .local
    │   ├── libexec
    │   │   ├── blocklist-copy
    │   │   └── blocklist-reload
    │   ├── sh
    │   │   └── today.sh
    │   └── share
    │       └── blocklist
    │           └── .gitkeep
    ├── bin
    │   └── blocklist.cron
    ├── blocklists
    │   └── .gitkeep
    └── reloads
        └── .gitkeep

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
