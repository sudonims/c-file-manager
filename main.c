#include <curses.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <locale.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
      target[i] = strdup(dir_entry->d_name);
      if (target[i++] == NULL) {
        endwin();
        printf("%s\n", "Couldn't allocate memory!");
        exit(1);
      }
    }
  }
  closedir(dir_);
  return 1;
}

int main() {
  // init_curses();
  char cwd[1000];
  getcwd(cwd, sizeof(cwd));
  // printf("%d", get_no_files_in_directory(cwd));
  int no_files;
  char *files[(no_files = get_no_files_in_directory(cwd))];
  get_files(cwd, files);

  for (int i = 0; i < no_files; i++) {
    printf("%s\n", files[i]);
  }
}