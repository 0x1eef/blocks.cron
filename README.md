## About

blocks + cron configures
[blocks](https://github.com/0x1eef/blocks#readme)
to run at regular intervals (once a day, at 12AM localtime)
via [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).
(Free|Open)BSD-based platforms are supported.

## Install

    # Clone
    git clone https://github.com/0x1eef/blocks.cron
    cd blocks.cron

    # Install (as root)
    doas -u root -- make install
    doas -u root -- setup-blocks+cron

## Design

* **/home/_blocks** <br>
  [setup-blocks+cron](bin/setup-blocks+cron) creates a
  `_blocks` user, group and environment that's optimized for
  running
  [blocks](https://github.com/0x1eef/blocks#readme) via
  [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)). The `/home/_blocks`
  directory contains all data and code that is generated or executed via
  [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).

* **/usr/local/share/pf/blocklist** <br>
  This file is the most recent copy of `/home/_blocks/blocks/YYYY-MM-DD`. It
  contains [pf.conf(5)](https://man.freebsd.org/cgi/man.cgi?pf.conf(5)) tables that
  can be used when when crafting firewall rules in `/etc/pf.conf`. See the
  [blocks README](https://github.com/0x1eef/blocks#readme)
  for an example. See
  [share/blocks+cron/home/_blocks/.local/libexec/copy](share/blocks+cron/home/_blocks/.local/libexec/copy)
  to learn how this file is created.

* **/var/cron/tabs/_blocks** <br>
  [setup-blocks+cron](bin/setup-blocks+cron) installs this crontab.
  The crontab executes
  [share/blocks+cron/home/_blocks/bin/run-blocks](share/blocks+cron/home/_blocks/bin/run-blocks)
  everyday at 12AM localtime. See
  [share/blocks+cron/crontab](share/blocks+cron/cron).

* **doas.conf** <br>
  [setup-blocks+cron](setup-blocks+cron) changes `doas.conf` to perform
  operations as root and only when neccessary. The creation of `/usr/local/share/pf/blocklist`
  and reloading
  [pf.conf(5)](https://man.freebsd.org/cgi/man.cgi?pf.conf(5))
  require root privileges.
  See [share/blocks+cron/doas.conf](share/blocks+cron/doas.conf).

## Tree

    $ tree -a /home/blocks
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

* [blocks](https://github.com/0x1eef/blocks#readme)
* doas
* pfctl

## Sources

* [GitHub](https://github.com/0x1eef/blocks.cron)
* [GitLab](https://gitlab.com/0x1eef/blocks.cron)
* [git.hardenedbsd.org](https://git.hardenedbsd.org/0x1eef/blocks.cron)

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
