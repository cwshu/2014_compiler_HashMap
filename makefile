all: hashmap.o

test: hashmap_tester1

hashmap_tester1: hashmap_tester1.o hashmap.o
	gcc -o $@ $^

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o

.PHONY: clean
