default: t/urlparser

clean:
	rm -f *.o t/*.o src/*.o
	rm -f t/urlparser

t/urlparser: t/urlparser.o src/url.o
	$(CC) $(CFLAGS) -o $@ $+

%.o: %.c include/http.h
	$(CC) $(CPPFLAGS) -c $(CFLAGS) -I. -I./include -o $@ $<
