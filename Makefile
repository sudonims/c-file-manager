NCURSES_CFLAGS = `pkg-config --cflags ncursesw`
NCURSES_LIBS =  `pkg-config --libs ncursesw`

LIBS += $(NCURSES_LIBS)
CFLAGS += $(NCURSES_CFLAGS)

SRCS = main.c
OBJS = $(SRCS: .c = .o)
PROG = fs

# prefix = usr
# bindir = $(prefix)/bin
# scriptdir = $(prefix)/share/cfiles/scripts
# mandir = $(prefix)/share/man

# BINDIR = $(DESTDIR)/$(bindir)
# MANDIR = $(DESTDIR)/$(mandir)
# SCRIPTDIR = $(DESTDIR)/$(scriptdir)

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG) $(LIBS)
	./fs

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm *~