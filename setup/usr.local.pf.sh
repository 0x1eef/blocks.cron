#!/bin/sh

create_usr_local_pf()
{
    mkdir -p /usr/local/share/pf
    chmod u=rwx,g=rx,o= /usr/local/share/pf
    echo "[ok] /usr/local/share/pf/ setup."
}
