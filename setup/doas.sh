#!/bin/sh

install_doas_conf()
{
    file=""
    doas=$(cat src/usr/local/etc/doas.conf)
    if isOpenBSD; then
        file="/etc/doas.conf"
    elif isFreeBSD; then
        file="/usr/local/etc/doas.conf"
    fi
    if grep -F "^${doas}$" "${file}" > /dev/null 2>&1; then
        echo "[-] ${file} remains unchanged"
    else
        echo "${doas}" >> "${file}"
        echo "[-] ${file} has been changed. Please review the changes"
    fi
}
