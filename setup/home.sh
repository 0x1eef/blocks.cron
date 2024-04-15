#!/bin/sh

create_home()
{
    exes="home/_blocklist/.local/libexec home/_blocklist/.local/sh home/_blocklist/bin"
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
