OBJS=main.o single.o downWeb.o getTDK.o price.o size-color.o fetchSKU.o writeTheRest.o cp2win.o mkdir.o search.o picture.o writeTop.o
CC=gcc
CFLAGS+=-Wall -c -g
CFLAGS_+=-Wall -g
LDFLAGS+=-pthread

catchWish:$(OBJS)
	$(CC) $^ -o $@ $(CFLAGS_) $(LDFLAGS)
%.o:%.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) *.o catchWish -r
