CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
LFLAGS = -lm

all: banhammer

$(EXECBIN): $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

bv: bv.o city.o
	$(CC) -o $@ $^ $(LFLAGS)

bf: city.o bv.o bf.o 
	$(CC) -o $@ $^ $(LFLAGS)

node: city.o bv.o bf.o node.o 
	$(CC) -o $@ $^ $(LFLAGS)

ll: city.o bv.o bf.o node.o ll.o 
	$(CC) -o $@ $^ $(LFLAGS)

ht: city.o bv.o bf.o node.o ll.o ht.o 
	$(CC) -o $@ $^ $(LFLAGS)

parser: parser.o city.o bv.o bf.o node.o ll.o ht.o 
	$(CC) -o $@ $^ $(LFLAGS)

banhammer: city.o bv.o bf.o node.o ll.o ht.o parser.o banhammer.c
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f banhammer bv bf node ll ht parser city *.o

format:
	clang-format -i -style=file *.[ch]

spotless: 
	rm -f banhammer banhammer *.o
	rm -f bv bv *.o
	rm -f bf bf *.o
	rm -f node node *.o
	rm -f ll ll *.o
	rm -f ht ht *.o
	rm -f parser parser *.o
	rm -f city city *.o
