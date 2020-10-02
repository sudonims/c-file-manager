CC = gcc

NCURSES_CFLAGS = `pkg-config --cflags ncursesw`
NCURSES_LIBS =  `pkg-config --libs ncursesw`

LIBS += $(NCURSES_LIBS)
CFLAGS += $(NCURSES_CFLAGS)

SRCS = main.c
OBJS = $(SRCS: .c = .o)
PROG = fs

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG) $(LIBS)
	sudo ./fs

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm *~