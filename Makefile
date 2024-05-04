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

	@find libexec/blocks+cron \
		-type d \
		-exec install \
			-v \
			-d \
			-o root \
			-g wheel \
			-m "u=rwx,go=rx" \
			"$(PREFIX)"/"{}" \;
	@find libexec/blocks+cron \
		-type f \
		-exec install \
		      -v \
		      -o root \
		      -g wheel \
		      -m "u=rwx,go=rx" \
		      "{}" "$(PREFIX)"/"{}" \;

	@find share/blocks+cron \
		-type d \
		-exec install \
		      -v \
		      -d \
		      -o root \
		      -g wheel \
		      -m "u=rwx,go=rx" \
		      "$(PREFIX)"/"{}" \;
	@find share/blocks+cron \
		-type f \
		-exec install \
		      -v \
		      -o root \
		      -g wheel \
		      -m "u=rw,go=r" \
		      "{}" "$(PREFIX)"/"{}" \;

deinstall:
	rm -rf "$(PREFIX)"/bin/setup-blocks+cron
	rm -rf "$(PREFIX)"/libexec/blocks+cron
	rm -rf "$(PREFIX)"/share/blocks+cron

shellcheck:
	shellcheck -x bin/*
	shellcheck -x setup/*.sh
	shellcheck -x src/home/_blocks/.local/libexec/*
	shellcheck -x src/home/_blocks/bin/*
