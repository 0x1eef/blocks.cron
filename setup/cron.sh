#!/bin/sh
install_crontab()
{
    cp src/var/cron/tabs/_blocklist /var/cron/tabs/
    chmod u=rw,g=r,o= /var/cron/tabs/_blocklist
    if isOpenBSD; then
        chgrp crontab /var/cron/tabs/_blocklist
    fi
    echo "[ok] /var/cron/tabs/_blocklist installed."
}

install_allowfile()
{
    allowfile=""
    allowuser=$(cat src/var/cron/allow)
    if isOpenBSD; then
        allowfile="/var/cron/cron.allow"
    elif isFreeBSD; then
        allowfile="/var/cron/allow"
    else
        echo "$(uname) is not supported."
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
    if isOpenBSD; then
        rcctl restart cron
    elif isFreeBSD; then
        service cron restart
    else
        echo "$(uname) is not supported."
        exit 1
    fi
}
