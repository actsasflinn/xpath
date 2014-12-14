all:
	gcc xpath.c -I/usr/local/opt/libxml2/include/libxml2 -L/usr/local/opt/libxml2/lib -lxml2 -lz -lpthread -lm -O3 -o xpath

clean:
	rm xpath
