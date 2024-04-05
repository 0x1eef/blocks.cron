#!/bin/sh

create_home()
{
    ##
    # copy
    cp -Rf src/home/_blocklist /home/

    ##
    # ownership
    chown -R _blocklist:_blocklist /home/_blocklist/
    chown -R root:_blocklist /home/_blocklist/.local/libexec/
    chown -R root:_blocklist /home/_blocklist/.local/sh/
    chown -R root:_blocklist /home/_blocklist/bin/

    ##
    # permissions
    chmod u=rwx,g=rx,o= /home/_blocklist/
    find /home/_blocklist/ -type d -exec chmod u=rwx,g=rx,o= {} +
    find /home/_blocklist/ -type f -exec chmod u=rw,g=r,o= {} +
    find /home/_blocklist/.local/ -type f -exec chmod u=rx,g=rx,o= {} +
    find /home/_blocklist/bin/ -type f -exec chmod u=rx,g=rx,o= {} +

    echo "[ok] /home/_blocklist/ setup."
}
