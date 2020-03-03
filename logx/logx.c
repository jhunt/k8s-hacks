#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

void sigbyebye() {
	write(2, "signal caught; terminating...\n", 30);
	exit(3);
}

const char * SONG = "this is the log that never ends...\n"
                    "yes it goes on and on my friend!\n"
                    "some people, started logging it,\n"
                    "not knowing what it was.\n"
                    "and they'll continue logging it forever,\n"
                    "just because...\n";

int main(int argc, char **argv) {
	unsigned long bytes = 512;
	unsigned long limit = 0;
	char *buf;

	signal(SIGTERM, sigbyebye);
	signal(SIGINT,  sigbyebye);

	if (argc > 3) {
		fprintf(stderr, "too many arguments!\n");
		fprintf(stderr, "USAGE: %s [BYTES]\n", argv[0]);
		exit(1);
	}
	if (argc >= 2) {
		bytes = 0;
		for (char *p = argv[1]; *p; p++) {
			switch (*p) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				bytes = (bytes * 10) + (*p - '0');
				break;
			default:
				fprintf(stderr, "invalid byte count '%s'\n", argv[1]);
				fprintf(stderr, "USAGE: %s [BYTES [LIMIT]]\n", argv[0]);
				exit(1);
			}
		}
	}
	if (argc == 3) {
		limit = 0;
		for (char *p = argv[2]; *p; p++) {
			switch (*p) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				limit = (limit * 10) + (*p - '0');
				break;
			default:
				fprintf(stderr, "invalid upper limit '%s'\n", argv[2]);
				fprintf(stderr, "USAGE: %s [BYTES [LIMIT]]\n", argv[0]);
				exit(1);
			}
		}
	}

	if (bytes < 128) {
		bytes = 128;
	}
	if (bytes > 1048576) {
		bytes = 1048576;
	}

	buf = malloc(bytes);
	if (!buf) {
		fprintf(stderr, "failed to allocate a buffer of %lu bytes: %s\n", bytes, strerror(errno));
		exit(2);
	}

	size_t SONG_LEN = strlen(SONG);
	for (int i = 0; i < bytes; ) {
		size_t n = (i + SONG_LEN) > bytes ? (bytes - i) : SONG_LEN;
		memcpy(buf+i, SONG, n);
		i += n;
	}
	buf[bytes-3] = '-';
	buf[bytes-2] = '-';
	buf[bytes-1] = '\n';

	int limited = limit ? 1 : 0;
	for (;;) {
		size_t off = 0;
		while (off < bytes) {
			ssize_t nwrit = write(2, buf+off, bytes-off);
			if (nwrit < 0) {
				fprintf(stderr, "\nwrite failed: %s\n", strerror(errno));
				exit(3);
			}
			off += nwrit;
		}

		if (limited && --limit == 0) {
			break;
		}

		usleep(1000000);
	}
}
