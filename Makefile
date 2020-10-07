NCURSES_CFLAGS = `pkg-config --cflags ncursesw`
NCURSES_LIBS =  `pkg-config --libs ncursesw`

LIBS += $(NCURSES_LIBS)
CFLAGS += $(NCURSES_CFLAGS)

SRCS = main.c
OBJS = $(SRCS: .c = .o)

all: $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o fs $(LIBS)
	./fs

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm *~