## About

blocklist + cron configures
[blocklist](https://github.com/0x1eef/blocklist#readme)
to run at regular intervals (once a day, at 12AM localtime)
via [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).

## Install

    # Clone
    git clone https://github.com/0x1eef/blocklist.cron
    cd blocklist.cron

    # Install (as root)
    doas -u root -- make install
    doas -u root -- setup-blocklist+cron

## Design

* **/home/_blocklist/** <br>
  [setup-blocklist+cron](bin/setup-blocklist+cron) creates a
  `_blocklist` user, group and environment that's optimized for
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
  for an example. See
  [share/blocklist+cron/home/_blocklist/.local/libexec/copy](share/blocklist+cron/home/_blocklist/.local/libexec/copy)
  to learn how this file is created.

* **/var/cron/tabs/_blocklist** <br>
  [setup-blocklist+cron](bin/setup-blocklist+cron) installs this crontab.
  The crontab executes
  [share/blocklist+cron/home/_blocklist/bin/run-blocklist](share/blocklist+cron/home/_blocklist/bin/run-blocklist)
  everyday at 12AM localtime. See
  [share/blocklist+cron/crontab](share/blocklist+cron/cron).

* **doas.conf** <br>
  [setup-blocklist+cron](setup-blocklist+cron) changes `doas.conf` to perform
  operations as root and only when neccessary. The creation of `/usr/local/share/pf/blocklist`
  and reloading
  [pf.conf(5)](https://man.freebsd.org/cgi/man.cgi?pf.conf(5))
  require root privileges.
  See [share/blocklist+cron/doas.conf](share/blocklist+cron/doas.conf).

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

## Sources

* [GitHub](https://github.com/0x1eef/blocklist.cron)
* [GitLab](https://gitlab.com/0x1eef/blocklist.cron)
* [git.hardenedbsd.org](https://git.hardenedbsd.org/0x1eef/blocklist.cron)

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
