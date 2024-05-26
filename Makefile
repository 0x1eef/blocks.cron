PREFIX=/usr/local

install:
	find bin \
		 -type f \
		 -exec install \
			-o root \
			-g wheel \
			-m "u=rwx,go=rx" \
			"{}" "$(PREFIX)"/"{}" \;

	find libexec/blocks+cron \
		-type d \
		-exec install \
			-d \
			-o root \
			-g wheel \
			-m "u=rwx,go=rx" \
			"$(PREFIX)"/"{}" \;
	find libexec/blocks+cron \
		-type f \
		-exec install \
		      -o root \
		      -g wheel \
		      -m "u=rwx,go=rx" \
		      "{}" "$(PREFIX)"/"{}" \;

	find share/blocks+cron \
		-type d \
		-exec install \
		      -d \
		      -o root \
		      -g wheel \
		      -m "u=rwx,go=rx" \
		      "$(PREFIX)"/"{}" \;
	find share/blocks+cron \
		-type f \
		-exec install \
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
	find libexec/ -type f -exec shellcheck -x {} \;
	find share/blocks+cron/home/_blocks/.local/libexec/ -type f -exec shellcheck -x {} \;
	find share/blocks+cron/home/_blocks/bin/ -type f -exec shellcheck -x {} \;
