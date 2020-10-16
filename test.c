#include <magic.h>
#include <ncurses.h> /* ncurses.h includes stdio.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  // char mesg[] = "Just a string"; /* message to be appeared on the screen */
  // int row, col;                  /* to store the number of rows and *
  //                                 * the number of colums of the screen */
  // initscr();                     /* start the curses mode */
  // getmaxyx(stdscr, row, col);    /* get the number of rows and columns */
  // mvprintw(row / 2, (col - strlen(mesg)) / 2, "%s", mesg);
  // /* print the message at the center of the screen */
  // mvprintw(row - 2, 0, "This screen has %d rows and %d columns\n", row, col);
  // printw(
  //     "Try resizing your window(if possible) and then run this program
  //     again");
  // refresh();
  // getch();
  // endwin();

  // return 0;
  // char a[] = "hiiiiii", b[100];
  // write(1, b, sizeof(b));
  // printf("%s\n", a);
  // printf("%s", b);
  const char *mime;
  magic_t magic;

  magic = magic_open(MAGIC_MIME_TYPE);
  magic_load(magic, NULL);
  magic_compile(magic, NULL);
  mime = magic_file(magic, "test.c");

  printf("%s\n", mime);
  magic_close(magic);
}