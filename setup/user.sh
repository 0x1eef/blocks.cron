#!/bin/sh

create_user()
{
    if ! id _blocklist > /dev/null 2>&1; then
        if isOpenBSD; then
            useradd \
                -L daemon \
                -m \
                -d /home/_blocklist \
                -s /sbin/nologin \
                _blocklist
            echo "[ok] _blocklist user / group created"
        elif isFreeBSD; then
            pw useradd \
                -L daemon \
                -m \
                -d /home/_blocklist \
                -s /sbin/nologin \
                _blocklist
            echo "[ok] _blocklist user / group created"
        else
            echo "$(uname) is not supported."
            exit 1
        fi
    else
        echo "[warn] _blocklist user already exists."
    fi
}
