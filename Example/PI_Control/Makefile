MAIN=../../main/main.o
OBJ=SlipServer.o

SlipServer:	$(OBJ) $(MAIN)
	$(CC) -Wall -O2 -o $@ $< $(MAIN)

$(OBJ):	SlipServer.c
	$(CC) -Wall -O2 -c $<

$(MAIN):	../../main/main.c
	$(MAKE) -C $(dir $(MAIN))

.PHONY:	clean
clean:
		$(RM) SlipServer $(OBJ)
