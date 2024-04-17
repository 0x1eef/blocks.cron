#!/bin/sh

install_crontab()
{
    crontab="/var/cron/tabs/_blocklist"
    if [ -e "${crontab}" ]; then
        yes | crontab -u _blocklist -r
    fi
    crontab -u _blocklist src/"${crontab}"
    chmod u=rw,g=,o= "${crontab}"
    echo "[-] New crontab: ${crontab}"
}

install_allowfile()
{
    file=""
    user=$(cat src/var/cron/allow)
    if isOpenBSD; then
        file="/var/cron/cron.allow"
    elif isFreeBSD; then
        file="/var/cron/allow"
    else
        echo "[-] Platform is not supported"
        exit 1
    fi
    if [ -e "${file}" ]; then
        if grep -F "${user}" "${file}" > /dev/null 2>&1; then
            echo "[-] ${file} remains unchanged"
        else
            echo "${user}" >> "${file}"
            chmod u=rw,g=r,o= "${file}"
            if isOpenBSD; then
                chgrp crontab "${file}"
            fi
            echo "[-] ${file} has been changed. Please review the changes"
        fi
    fi
}
