PREFIX=/usr/local

install:
	@find bin \
		 -type f \
		 -exec install \
			-v \
			-o root \
			-g wheel \
			-m "u=rwx,go=rx" \
			"{}" "$(PREFIX)"/"{}" \;

	@find libexec/blocklist+cron \
		-type d \
		-exec install \
			-v \
			-d \
			-o root \
			-g wheel \
			-m "u=rwx,go=rx" \
			"$(PREFIX)"/"{}" \;
	@find libexec/blocklist+cron \
		-type f \
		-exec install \
		      -v \
		      -o root \
		      -g wheel \
		      -m "u=rwx,go=rx" \
		      "{}" "$(PREFIX)"/"{}" \;

	@find share/blocklist+cron \
		-type d \
		-exec install \
		      -v \
		      -d \
		      -o root \
		      -g wheel \
		      -m "u=rwx,go=rx" \
		      "$(PREFIX)"/"{}" \;
	@find share/blocklist+cron \
		-type f \
		-exec install \
		      -v \
		      -o root \
		      -g wheel \
		      -m "u=rw,go=r" \
		      "{}" "$(PREFIX)"/"{}" \;

deinstall:
	rm -rf "$(PREFIX)"/bin/setup-blocklist+cron
	rm -rf "$(PREFIX)"/libexec/blocklist+cron
	rm -rf "$(PREFIX)"/share/blocklist+cron

shellcheck:
	shellcheck -x bin/*
	shellcheck -x setup/*.sh
	shellcheck -x src/home/_blocklist/.local/libexec/*
	shellcheck -x src/home/_blocklist/.local/sh/*
	shellcheck -x src/home/_blocklist/bin/*
