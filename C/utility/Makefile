.PHONY: all
all: Msequence.o Quantizer.o

Msequence.o:	Msequence.c
	$(CC) -c -o $@ $<

Quantizer.o:	Quantizer.c
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) Msequence.o Quantizer.o
