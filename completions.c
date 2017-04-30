#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "completions.h"

static char *path;

void get_path()
{
  char *path_cstr = (char*)getenv("PATH");
  char *dirname;
  char *items[100000];
  int  n_items;
  // printf(path_cstr);

  while ((dirname = strsep(&path_cstr, ":")) != NULL)
  {
    printf("%s\n", dirname);

    DIR *d;
    struct dirent *dir;

    d = opendir(dirname);
    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {
        printf("%s\n", dir->d_name);
        items[n_items] = dir->d_name;
        n_items++;
      }
      closedir(d);
    }
  }
  printf("Read %d items from PATH\n", n_items);
  free(path_cstr);
  free(dirname);
}
