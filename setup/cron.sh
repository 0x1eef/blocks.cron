#!/bin/sh

install_crontab()
{
    crontab="/var/cron/tabs/_blocklist"
    if [ -e "${crontab}" ]; then
        yes | crontab -u _blocklist -r
    fi
    crontab -u _blocklist src/var/cron/tabs/_blocklist
    chmod u=rw,g=,o= "${crontab}"
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
    if [ -e "${allowfile}" ]; then
        if grep -F "${allowuser}" "${allowfile}" > /dev/null 2>&1; then
            echo "[warn] ${allowfile} already includes the _blocklist user."
        else
            echo "${allowuser}" >> "${allowfile}"
            chmod u=rw,g=r,o= "${allowfile}"
            if isOpenBSD; then
                chgrp crontab "${allowfile}"
            fi
            echo "[ok] added _blocklist to ${allowfile} file."
        fi
    fi
}
