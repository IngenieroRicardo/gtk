#include <gtk/gtk.h>
#include <stdlib.h>

extern void goCallbackProxy(gpointer data);

void go_callback_bridge(GtkWidget *widget, gpointer data) {
    goCallbackProxy(data);
}
