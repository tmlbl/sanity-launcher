#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "completions.h"

#include <set>
#include <string>
#include <vector>

enum searchable_t { EXECUTABLE };

struct searchable {
  searchable_t type;
  std::string name;
  std::string path;
};

typedef std::vector<searchable> SearchSet;

static SearchSet path_execs;

typedef std::set<std::string> StrSet;

static StrSet path_items;

// Callback for key_release event on the input.
// Compares input text to all of the searchable items.
gboolean get_completions(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
  const char *text = gtk_entry_get_text(GTK_ENTRY(widget));
  // If the input is empty, abort
  if ((text != NULL) && (text[0] == '\0'))
  {
    return FALSE;
  }
  // Check for matching executables from $PATH
  for (auto e: path_execs)
  {
    const char *name = e.name.c_str();
    bool match = FALSE;
    int len_input = strlen(text);
    int len_item = strlen(name);
    for (int i = 0; i < len_input && i < len_item; i++)
    {
      match = (text[i] == name[i]);
      if (!match) break;
    }
    if (match)
    {
      printf("It's a match! %s == %s\n", name, text);

      GtkWidget *label = gtk_label_new(name)
    }
  }
  return FALSE;
}

void get_path_items()
{
  char *path_str = std::getenv("PATH");
  printf("%s\n", path_str);
  char *dirname;

  while ((dirname = strsep(&path_str, ":")) != NULL)
  {
    DIR *d;
    struct dirent *dir;

    d = opendir(dirname);
    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {
        path_items.insert(dir->d_name);
      }
      closedir(d);
    }
  }
  path_execs = SearchSet(path_items.size());
  for (StrSet::iterator i = path_items.begin(); i != path_items.end(); i++)
  {
    searchable s;
    s.type = EXECUTABLE;
    s.name = i->c_str();
    path_execs.push_back(s);
  }
  printf("Read %d items from PATH\n", path_items.size());
  free(path_str);
  free(dirname);
}

// int levenshtein_distance(const std::string &s1, const std::string &s2)
// {
// 	// To change the type this function manipulates and returns, change
// 	// the return type and the types of the two variables below.
// 	int s1len = s1.size();
// 	int s2len = s2.size();

// 	auto column_start = (decltype(s1len))1;

// 	auto column = new decltype(s1len)[s1len + 1];
// 	std::iota(column + column_start, column + s1len + 1, column_start);

// 	for (auto x = column_start; x <= s2len; x++) {
// 		column[0] = x;
// 		auto last_diagonal = x - column_start;
// 		for (auto y = column_start; y <= s1len; y++) {
// 			auto old_diagonal = column[y];
// 			auto possibilities = {
// 				column[y] + 1,
// 				column[y - 1] + 1,
// 				last_diagonal + (s1[y - 1] == s2[x - 1]? 0 : 1)
// 			};
// 			column[y] = std::min(possibilities);
// 			last_diagonal = old_diagonal;
// 		}
// 	}
// 	auto result = column[s1len];
// 	delete[] column;
// 	return result;
// }