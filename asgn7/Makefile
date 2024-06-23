CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
LFLAGS = -lm

all: encode decode

encode: encode.o huffman.o io.o code.o pq.o node.o stack.o
	$(CC) -o $@ $^ $(LFLAGS)

decode: decode.o huffman.o io.o code.o pq.o node.o stack.o
	$(CC) -o $@ $^ $(LFLAGS)

node: node.o 
	$(CC) -o $@ $^ $(LFLAGS)

pq: pq.o node.o 
	$(CC) -o $@ $^ $(LFLAGS)

code: code.o stack.o node.o
	$(CC) -o $@ $^ $(LFLAGS)

io: io.o code.o pq.o node.o 
	$(CC) -o $@ $^ $(LFLAGS)

stack: stack.o node.o
	$(CC) -o $@ $^ $(LFLAGS)

huffman: huffman.o io.o code.o pq.o node.o stack.o
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f huffman stack io code pq node decode encode *.o

format:
	clang-format -i -style=file *.[ch]

spotless: 
	rm -f huffman huffman *.o
	rm -f stack stack *.o
	rm -f io io *.o
	rm -f node node *.o
	rm -f pq pq *.o
	rm -f code code *.o
	rm -f decode decode *.o
	rm -f encode encode *.o
