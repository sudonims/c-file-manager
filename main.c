#include <dirent.h>   // Directory
#include <fcntl.h>    // FD Manipulate (Probably won't need here)
#include <limits.h>   // INT_MAX, etc...
#include <locale.h>   // Locale
#include <ncurses.h>  // Curses (UI)
#include <pwd.h>      // get uid, username n stuff
#include <signal.h>   // Dunno what this does but curses code had this...lol
#include <stdio.h>    //	std i/o
#include <stdlib.h>   //	std libs
#include <string.h>   //	string opr
#include <strings.h>
#include <sys/stat.h>   // system stats
#include <sys/types.h>  //	sys types
#include <sys/wait.h>   //	child_process report kinda
#include <unistd.h>     //	POSIX definitions

#include "config.h"

void init_curses() {
  initscr();
  noecho();
  curs_set(0);
  start_color();
  init_pair(1, DIR_COLOR, 0);
  init_pair(2, STATUS_FILECOUNT_COLOR, 0);
  init_pair(3, STATUS_SELECTED_COLOR, 0);
}
sigset_t x;
WINDOW *current_win, *preview_win, *status_win;
int selection, maxx, maxy, len = 0, start = 0;

void init_windows() {
  current_win = newwin(maxy, maxx / 2 + 2, 0, 0);
  preview_win = newwin(maxy, maxx / 2 - 1, 0, maxx / 2 + 1);
  status_win = newwin(2, maxx, maxy, 0);
  keypad(current_win, TRUE);
  sigprocmask(SIG_UNBLOCK, &x, NULL);
}

void refreshWindows() {
  box(current_win, 0, 0);
  box(preview_win, 0, 0);
  wrefresh(current_win);
  wrefresh(preview_win);
}

int get_no_files_in_directory(char *directory) {
  int len = 0;
  DIR *dir_;
  struct dirent *dir_entry;

  dir_ = opendir(directory);
  if (dir_ == NULL) {
    return -1;
  }

  while ((dir_entry = readdir(dir_)) != NULL) {
    // Skip . and ..
    if (strcmp(dir_entry->d_name, ".") != 0 &&
        strcmp(dir_entry->d_name, "..") != 0) {
      len++;
    }
  }
  closedir(dir_);
  return len;
}

int get_files(char *directory, char *target[]) {
  int i = 0;
  DIR *dir_;
  struct dirent *dir_entry;

  dir_ = opendir(directory);
  if (dir_ == NULL) {
    return -1;
  }

  while ((dir_entry = readdir(dir_)) != NULL) {
    // Skip . and ..
    if (strcmp(dir_entry->d_name, ".") != 0 &&
        strcmp(dir_entry->d_name, "..") != 0) {
      target[i++] = strdup(dir_entry->d_name);
    }
  }
  closedir(dir_);
  return 1;
}

void scroll_up() {
  selection--;
  selection = (selection < 0) ? 0 : selection;
  wclear(current_win);
  if (len >= maxy - 1)
    if (selection <= start + maxy / 2) {
      if (start == 0)
        wclear(current_win);
      else {
        start--;
        wclear(current_win);
      }
    }
}

void scroll_down() {
  selection++;
  selection = (selection > len - 1) ? len - 1 : selection;
  if (len >= maxy - 1)
    if (selection - 1 > maxy / 2) {
      if (start + maxy - 2 != len) {
        start++;
        wclear(current_win);
      }
    }
}

int main() {
  int i = 0;
  init_curses();
  char cwd[1000];
  getcwd(cwd, sizeof(cwd));

  int ch;
  // init_windows();
  do {
    int temp_len;

    len = get_no_files_in_directory(cwd);

    temp_len = len <= 0 ? 1 : len;

    char *files[temp_len], *temp_dir;
    // char *files[(len = get_no_files_in_directory(cwd) <= 0
    //                        ? 0
    //                        : get_no_files_in_directory(cwd))],

    get_files(cwd, files);

    if (selection > len - 1) {
      selection = len - 1;
    }

    getmaxyx(stdscr, maxx, maxy);
    maxy -= 2;
    int t = 0;
    init_windows();

    for (i = start; i < len; i++) {
      if (t == maxy - 1)
        break;
      int size = snprintf(NULL, 0, "%s/%s", cwd, files[i]);
      // printf("%d", size);
      if (i == selection) {
        mvprintw(i + 2, 0, "Hm");
        wattron(current_win, A_STANDOUT);
      } else {
        wattroff(current_win, A_STANDOUT);
      }
      temp_dir = malloc(size + 1);
      snprintf(temp_dir, size + 1, "%s/%s", cwd, files[i]);

      wmove(current_win, t + 1, 2);
      wprintw(current_win, "%.*s\n", maxx / 2, files[i]);
      // mvprintw(i + 2, 2, "%s", temp_dir);
      // free(temp_dir);
      t++;
    }
    // refresh();
    // wrefresh(current_win);

    refreshWindows();

    switch ((ch = wgetch(current_win))) {
      case KEY_UP:
      case KEY_NAVUP:
        // mvprintw(i + 2, 2, "lol");
        scroll_up();
        break;
      case KEY_DOWN:
      case KEY_NAVDOWN:
        scroll_down();
        break;
    }

  } while (ch != 'q');
  endwin();
}