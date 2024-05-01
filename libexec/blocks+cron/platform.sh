#!/bin/sh

isFreeBSD()
{
    platform=$(uname)
    if [ "${platform}" = "FreeBSD" ]; then
        return 0
    else
        return 1
    fi
}

isOpenBSD()
{
    platform=$(uname)
    if [ "${platform}" = "OpenBSD" ]; then
        return 0
    else
        return 1
    fi
}
