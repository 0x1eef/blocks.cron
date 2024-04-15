shellcheck:
	shellcheck -x bin/*
	shellcheck -x setup/*.sh
	shellcheck -x src/home/_blocklist/.local/libexec/*
	shellcheck -x src/home/_blocklist/.local/sh/*
	shellcheck -x src/home/_blocklist/bin/*
