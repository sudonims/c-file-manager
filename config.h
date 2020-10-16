#ifndef CONFIG
#define CONFIG

typedef struct directory_ {
  char cwd[1000];
  char *parent_dir;
  char *files[];
} directory_t;

#define FILE_OPENER "xdg-open"

#define DIR_COLOR 4

#define STATUS_SELECTED_COLOR 6

#define KEY_NAVUP 'k'

#define KEY_NAVDOWN 'j'

#define KEY_ENTER 10

#endif
