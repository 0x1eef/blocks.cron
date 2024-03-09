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
are supported by blocklist.cron.

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

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
