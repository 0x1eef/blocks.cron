#!/bin/sh

install_doas_conf()
{
    doasfile=""
    doas=$(cat src/usr/local/etc/doas.conf)
    if isOpenBSD; then
        doasfile="/etc/doas.conf"
    elif isFreeBSD; then
        doasfile="/usr/local/etc/doas.conf"
    fi
    if fgrep "${doas}" "${doasfile}" > /dev/null 2>&1; then
        echo "[warn] ${doasfile} already includes blocklist rules."
    else
        echo "${doas}" >> "${doasfile}"
        echo "[ok] ${doasfile} updated."
    fi
}
