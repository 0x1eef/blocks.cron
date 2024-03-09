create_home()
{
    cp -Rf src/home/_blocklist/* /home/_blocklist/

    chown -R _blocklist:_blocklist /home/_blocklist/
    chmod -R u=rwX,g=rX,o= /home/_blocklist/

    chown -R root:_blocklist /home/_blocklist/libexec/
    chmod -R u=rwx,g=rx,o= /home/_blocklist/libexec/

    chown -R root:_blocklist /home/_blocklist/bin/
    chmod -R u=rwx,g=rx,o= /home/_blocklist/bin/

    chown -R _blocklist:_blocklist /home/_blocklist/blocklists/
    chmod -R u=rwx,g=rx,o= /home/_blocklist/blocklists/

    chown -R _blocklist:_blocklist /home/_blocklist/reloads/
    chmod -R u=rwx,g=rx,o= /home/_blocklist/reloads/

    echo "[ok] /home/_blocklist/ setup."
}
