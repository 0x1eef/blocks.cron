#!/bin/sh
install_crontab()
{
    platform=$(uname)
    src/var/cron/tabs/_blocklist /var/cron/tabs/
    chmod u=rw,g=r,o= /var/cron/tabs/_blocklist
    if [ "${platform}" = "OpenBSD" ]; then
        chgrp crontab /var/cron/tabs/_blocklist
    fi
    echo "[ok] /var/cron/tabs/_blocklist installed."
}

install_allowfile()
{

    allowfile=""
    allowuser=$(cat src/var/cron/allow)
    if [ "${platform}" = "OpenBSD" ]; then
        allowfile="/var/cron/cron.allow"
    elif [ "${platform}" = "FreeBSD" ]; then
        allowfile="/var/cron/allow"
    else
        echo "${platform} is not supported."
        exit 1
    fi
    if fgrep "${allowuser}" "${allowfile}" > /dev/null 2>&1; then
        echo "[warn] ${allowfile} already includes the _blocklist user."
    else
        echo "${allowuser}" >> "${allowfile}"
        echo "[ok] added _blocklist to ${allowfile} file."
    fi
}

restart_cron()
{
    platform=$(uname)
    if [ "${platform}" = "OpenBSD" ]; then
        rcctl restart cron
    elif [ "${platform}" = "FreeBSD" ]; then
        service cron restart
    else
        echo "${platform} is not supported."
        exit 1
    fi
}
