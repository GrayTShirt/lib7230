#include "http.h"
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


http_uri_t
http_parse_uri(const char *uri)
{
	http_uri_t u;
	size_t len;
	char *p;

	len = strlen(uri);

	/* the smallest URI possible is "http://x/"
	   so if we have fewer than 9 characters, it's invalid */
	if (len < 9) {
		errno = EINVAL;
		return NULL;
	}

	u = calloc(1, sizeof(http_uri_t) + len + 1);
	if (!u) {
		errno = ENOBUFS;
		return NULL;
	}

	memcpy(u->_s, uri, len);
	u->_s[len] = '\0';
	u->scheme = &u->_s[0];

	/* find the end of the scheme component */
	p = strchr(u->scheme, ':');
	if (!p) {
		errno = EINVAL;
		free(u);
		return NULL;
	}
	*p = '\0';

	/* verify that the scheme is followed by '//' */
	p++;
	if (!*p || *p != '/') {
		errno = EINVAL;
		free(u);
		return NULL;
	}
	p++;
	if (!*p || *p != '/') {
		errno = EINVAL;
		free(u);
		return NULL;
	}

	/* extract the hostname */
	u->host = p-1;
	while (*p && *p != ':' && *p != '/') {
		*(p-1) = *p;
		p++;
	}
	*(p-1)  = '\0';

	/* do we have a port? */
	if (*p == ':') {
		p++;
		u->port = 0;
		while (isdigit(*p)) {
			u->port *= 10 + *p - '0';
			if (u->port > 65535) {
				/* port out of range */
				errno = EINVAL;
				free(u);
				return NULL;
			}
		}
	}

	/* do we have a path? */
	if (*p == '/') {
		u->path = p;
		if ((p = strchr(p, '?')) != NULL) {
			*p++ = '\0';
			u->rawquery = p;
		}
		if ((p = strchr(p, '#')) != NULL) {
			*p++ = '\0';
			u->fragment = p;
		}
	}

	return u;
}
