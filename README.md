## About

blocks + cron configures
[blocks](https://github.com/0x1eef/blocks#readme)
to run at regular intervals (once a day, at 12AM localtime)
via [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).
A dedicated user account (`_blocks`) isolates the execution of
[blocks](https://github.com/0x1eef/blocks#readme)
from other user accounts.

## Design

* **/home/_blocks** <br>
  [setup-blocks+cron](bin/setup-blocks+cron) creates a
  `_blocks` user, group and environment that's optimized for
  running
  [blocks](https://github.com/0x1eef/blocks#readme)
  via
  [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).
  The `/home/_blocks` directory contains all data and code
  that is generated or executed via
  [cron(8)](https://man.freebsd.org/cgi/man.cgi?cron(8)).

* **/var/cron/tabs/_blocks** <br>
  [setup-blocks+cron](bin/setup-blocks+cron)
  installs a crontab that executes
  [/home/_blocks/bin/run-blocks](share/blocks+cron/home/_blocks/bin/run-blocks)
  everyday at 12AM localtime. See
  [share/blocks+cron/crontab](share/blocks+cron/cron).

* **doas.conf** <br>
  [setup-blocks+cron](setup-blocks+cron)
  updates `doas.conf` to be able to copy
  `/usr/local/share/pf/blocklist`
  into place and reload
  [pf.conf(5)](https://man.freebsd.org/cgi/man.cgi?pf.conf(5))
  (both tasks are done as root).
  See [doas.conf](share/blocks+cron/doas.conf).

* **/usr/local/share/pf/blocklist** <br>
  This file is the most recent copy of
  `/home/_blocks/.local/share/blocks+cron/YYYYMMDD`.
  It contains
  [pf.conf(5)](https://man.freebsd.org/cgi/man.cgi?pf.conf(5))
  tables that can be used when when crafting
  firewall rules in `/etc/pf.conf`.

## Tree

    $ tree -a /home/_blocks
    ├── .local
    │   ├── libexec
    │   │   └── blocks+cron
    │   │       ├── copy
    │   │       └── reload
    │   ├── share
    │   │   ├── blocks
    │   │   │   └── .gitkeep
    │   │   └── blocks+cron
    │   │       └── .gitkeep
    │   └── var
    │       └── log
    │           └── .gitkeep
    └── bin
        └── run-blocks

## Requirements

* [blocks](https://github.com/0x1eef/blocks#readme)
* doas
* pfctl

## Install

    # Clone
    git clone https://github.com/0x1eef/blocks.cron
    cd blocks.cron

    # Install
    $ doas -u root make install
    $ doas -u root setup-blocks+cron

## Sources

* [GitHub](https://github.com/0x1eef/blocks.cron)
* [GitLab](https://gitlab.com/0x1eef/blocks.cron)
* [git.HardenedBSD.org](https://git.HardenedBSD.org/0x1eef/blocks.cron)

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
