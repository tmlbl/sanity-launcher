#ifndef COMPLETIONS_H
#define COMPLETIONS_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include <set>
#include <string>

gboolean get_completions(GtkWidget *widget, GdkEventKey *event, gpointer data);

void get_path_items();

#endif
