#!/bin/sh

create_home()
{
    ##
    # Copy
    cp -Rf src/home/_blocklist/* /home/_blocklist/
    cp -Rf src/home/_blocklist/.* /home/_blocklist/

    ##
    # Ownership
    chown -R _blocklist:_blocklist /home/_blocklist/
    chown -R root:_blocklist /home/_blocklist/functions/
    chown -R root:_blocklist /home/_blocklist/libexec/
    chown -R root:_blocklist /home/_blocklist/bin/

    ##
    # Permissions
    chmod u=rwx,g=rx,o= /home/_blocklist/
    find /home/_blocklist/ -type d -exec chmod u=rwx,g=rx,o= {} +
    find /home/_blocklist/ -type f -exec chmod u=rw,g=r,o= {} +
    find /home/_blocklist/functions/ -type f -exec chmod u=rx,g=rx,o= {} +
    find /home/_blocklist/libexec/ -type f -exec chmod u=rx,g=rx,o= {} +
    find /home/_blocklist/bin/ -type f -exec chmod u=rx,g=rx,o= {} +

    echo "[ok] /home/_blocklist/ setup."
}
