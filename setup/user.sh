create_user()
{
    platform=$(uname)
    if ! id _blocklist > /dev/null 2>&1; then
        if [ "${platform}" = "OpenBSD" ]; then
            useradd \
                -L daemon \
                -m \
                -d /home/_blocklist \
                -s /sbin/nologin \
                _blocklist
            echo "[ok] _blocklist user / group created"
        elif [ "${platform}" = "FreeBSD" ]; then
            pw useradd \
                -L daemon \
                -m \
                -d /home/_blocklist \
                -s /sbin/nologin \
                _blocklist
            echo "[ok] _blocklist user / group created"
        else
            echo "${platform} is not supported"
            exit 1
        fi
    else
        echo "[warn] _blocklist user already exists."
    fi
}
