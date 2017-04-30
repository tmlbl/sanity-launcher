#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "completions.h"

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

// Quit the application when the escape key is pressed
static gboolean check_escape(GtkWidget *widget,
GdkEventKey *event, gpointer data)
{
  if (event->keyval == GDK_KEY_Escape) {
    g_application_quit(G_APPLICATION(data));
    return TRUE;
  }
  return FALSE;
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *input;
  GtkEntryCompletion *completion;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Sanic - gotta go fast");

  // Center position
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  // Don't allow user to resize
  gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
  // No window decoration
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
  // Set window size
  gtk_window_set_default_size(GTK_WINDOW (window), 500, 100);

  // Create the text input
  input = gtk_entry_new();
  // Remove the frame
  gtk_entry_set_has_frame(GTK_ENTRY(input), FALSE);

  completion = gtk_entry_completion_new();
  gtk_entry_set_completion(GTK_ENTRY(input), completion);

  // Exit on escape
  g_signal_connect(window, "key_press_event", G_CALLBACK(check_escape), app);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  gtk_container_add(GTK_CONTAINER(button_box), input);

  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  get_path();

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
