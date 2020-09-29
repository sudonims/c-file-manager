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
// sigset_t x;
WINDOW *current_win;

void init_windows() {
  current_win = newwin(80, 24, 0, 0);
  // keypad(current_win, TRUE);
  // sigprocmask(SIG_UNBLOCK, &x, NULL);
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

int main() {
  int i = 0;
  init_curses();
  char cwd[1000];
  getcwd(cwd, sizeof(cwd));
  // printf("%d", get_no_files_in_directory(cwd));
  int no_files;
  char *files[(no_files = get_no_files_in_directory(cwd))], *temp_dir;
  get_files(cwd, files);

  // for (int i = 0; i < no_files; i++) {
  //   printf("%s\n", files[i]);
  // }
  // init_windows();
  initscr();
  int t = 0, row, col;
  getmaxyx(stdscr, row, col);
  for (i = 0; i < no_files; i++) {
    // if (t == 24 - 1)
    //   break;
    // free(temp_dir);
    // allocSize = snprintf(NULL, 0, "%s/%s", dir, directories[i]);
    // temp_dir = malloc(allocSize + 1);
    // if (temp_dir == NULL) {
    //   endwin();
    //   printf("%s\n", "Couldn't allocate memory!");
    //   exit(1);
    // }
    // snprintf(temp_dir, allocSize + 1, "%s/%s", dir, directories[i]);
    // if (i == selection)
    //   wattron(current_win, A_STANDOUT);
    // else
    //   wattroff(current_win, A_STANDOUT);
    int size = snprintf(NULL, 0, "%s/%s", cwd, files[i]);
    // printf("%d", size);
    temp_dir = malloc(size + 1);
    snprintf(temp_dir, size + 1, "%s/%s", cwd, files[i]);
    // wattron(current_win, A_BOLD);
    // wattron(current_win, COLOR_PAIR(1));
    // if (is_regular_file(temp_dir) == 0) {
    // }
    // else {
    wattroff(current_win, A_BOLD);
    wattroff(current_win, COLOR_PAIR(1));
    // }
    // wmove(current_win, t + 1, 2);
    // if (checkClipboard(temp_dir) == 0)
    // mvwprintw(current_win, i + 1, 2, "%s\n", temp_dir);
    mvprintw(i + 2, 2, "%s", temp_dir);
    // printw("%s\n", temp_dir);
    // wprintw(current_win, "%.*s\n", 80 / 2, files[i]);
    // else
    // wprintw(current_win, "* %.*s\n", 80 / 2 - 3, files[i]);
    refresh();
  }
  getch();
  endwin();
}