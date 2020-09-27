MAIN=../../main/main.o
UTIL=../../utility/Msequence.o ../../utility/Quantizer.o
IFLAG=../../utility/

SlipServer:	SlipServer.c $(MAIN) $(UTIL)
	$(CC) -Wall -O2 -o $@ $< $(MAIN) $(UTIL) -I $(IFLAG) -lm

$(MAIN):	../../main/main.c
	$(MAKE) -C $(dir $(MAIN))

$(UTIL):	../../utility/Msequence.c
	$(MAKE) -C $(dir $(UTIL))

.PHONY:	clean
clean:
		$(RM) SlipServer
