MAIN=../../main/main.o

SlipServer:	SlipServer.c $(MAIN)
	$(CC) -Wall -O3 -o $@ $< $(MAIN)

$(MAIN):	../../main/main.c
	$(MAKE) -C $(dir $(MAIN))

.PHONY:	clean
clean:
		$(RM) SlipServer
