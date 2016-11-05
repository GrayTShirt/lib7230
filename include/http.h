#ifndef LIB7230_HTTP_H
#define LIB7230_HTTP_H

/*
   http_uri_t represents a parsed URL, as it is broken down
   into its components parts:

     http://ho.st.na.me:8080/path/?query=string#fragment
     \__/   \_________/ \__/\____/ \__________/ \______/
       \         \        \    \          \         \
        \         \        \    \          \         `-- fragment
         \         \        \    \          `----------- rawquery
          \         \        \    `--------------------- path
           \         \        `------------------------- port
            \         `--------------------------------- host
             `------------------------------------------ scheme

   The query string is not parsed, since semantics differ
   from application to application, especially with respect
   to array encoding and duplicated querystring keys.
 */
typedef struct __opaque_http_uri_t* http_uri_t;
struct __opaque_http_uri_t {
	char *scheme;
	char *host;
	int   port;
	char *path;
	char *rawquery;
	char *fragment;

	char _s[];
};

http_uri_t http_parse_uri(const char *uri);

#endif
