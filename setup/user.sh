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

create_home()
{
    exes="home/_blocklist/.local/libexec \
          home/_blocklist/.local/sh \
          home/_blocklist/bin"
    cd src/
    find home/_blocklist \
        -type d \
        -exec install -d \
              -o _blocklist \
              -g _blocklist \
              -m u=rwx,g=rx,o= \
              "/{}" \;
    for exe in ${exes}; do
        find "${exe}" \
            -type f \
            -exec install \
            -o root \
            -g _blocklist \
            -m u=rx,g=rx,o= \
            "{}" "/{}" \;
    done
    cd ../
    echo "[ok] /home/_blocklist/ setup."
}
