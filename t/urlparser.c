#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

int main(int argc, char **argv) {
	static char buf[8192];
	char *p;
	http_uri_t u;

	while (fgets(buf, 8192, stdin) != NULL) {
		p = strchr(buf, '\n');
		if (!p) {
			fprintf(stderr, "line too long!\n");
			exit(1);
		}
		*p = '\0';
		fprintf(stderr, "url: %s\n", buf);
		u = http_parse_uri(buf);
		if (u) {
			fprintf(stderr, " - scheme:   '%s'\n", u->scheme);
			fprintf(stderr, " - host:     '%s'\n", u->host);
			fprintf(stderr, " - port:     '%d'\n", u->port);
			fprintf(stderr, " - path:     '%s'\n", u->path);
			fprintf(stderr, " - rawquery: '%s'\n", u->rawquery);
			fprintf(stderr, " - fragment: '%s'\n", u->fragment);
			free(u);
		}
	}
	return 0;
}
