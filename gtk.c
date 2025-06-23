#include <gtk/gtk.h>
#include <stdlib.h>

extern void goCallbackProxy(gpointer data);

void go_callback_bridge(GtkWidget *widget, gpointer data) {
    goCallbackProxy(data);
}

// Funciones wrapper para GtkEntry
void gtk_entry_set_text_wrapper(GObject *entry, const gchar *text) {
    gtk_entry_set_text(GTK_ENTRY(entry), text);
}

const gchar* gtk_entry_get_text_wrapper(GObject *entry) {
    return gtk_entry_get_text(GTK_ENTRY(entry));
}

// Funciones wrapper para GtkLabel
void gtk_label_set_text_wrapper(GObject *label, const gchar *text) {
    gtk_label_set_text(GTK_LABEL(label), text);
}

const gchar* gtk_label_get_text_wrapper(GObject *label) {
    return gtk_label_get_text(GTK_LABEL(label));
}


// Funciones wrapper para GtkButton
void gtk_button_set_label_wrapper(GObject *button, const gchar *text) {
    gtk_button_set_label(GTK_BUTTON(button), text);
}

const gchar* gtk_button_get_label_wrapper(GObject *button) {
    return gtk_button_get_label(GTK_BUTTON(button));
}

void gtk_button_set_sensitive_wrapper(GObject *button, gboolean sensitive) {
    gtk_widget_set_sensitive(GTK_WIDGET(button), sensitive);
}

gboolean gtk_button_get_sensitive_wrapper(GObject *button) {
    return gtk_widget_get_sensitive(GTK_WIDGET(button));
}










// Función única para manejar ToggleButton y CheckButton
void gtk_toggle_button_set_active_wrapper(GObject *toggle_widget, gboolean active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_widget), active);
}

gboolean gtk_toggle_button_get_active_wrapper(GObject *toggle_widget) {
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_widget));
}





// Funciones wrapper para GtkMenuItem
void gtk_menu_item_set_label_wrapper(GObject *menu_item, const gchar *label) {
    gtk_menu_item_set_label(GTK_MENU_ITEM(menu_item), label);
}

const gchar* gtk_menu_item_get_label_wrapper(GObject *menu_item) {
    return gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item));
}

void gtk_menu_item_set_sensitive_wrapper(GObject *menu_item, gboolean sensitive) {
    gtk_widget_set_sensitive(GTK_WIDGET(menu_item), sensitive);
}

gboolean gtk_menu_item_get_sensitive_wrapper(GObject *menu_item) {
    return gtk_widget_get_sensitive(GTK_WIDGET(menu_item));
}

void gtk_menu_item_set_active_wrapper(GObject *menu_item, gboolean active) {
    GtkCheckMenuItem *check_item = GTK_CHECK_MENU_ITEM(menu_item);
    if (GTK_IS_CHECK_MENU_ITEM(check_item)) {
        gtk_check_menu_item_set_active(check_item, active);
    }
}

gboolean gtk_menu_item_get_active_wrapper(GObject *menu_item) {
    GtkCheckMenuItem *check_item = GTK_CHECK_MENU_ITEM(menu_item);
    if (GTK_IS_CHECK_MENU_ITEM(check_item)) {
        return gtk_check_menu_item_get_active(check_item);
    }
    return FALSE;
}











// Funciones wrapper para GtkPopover
void gtk_popover_set_visible_wrapper(GObject *popover, gboolean visible) {
    gtk_widget_set_visible(GTK_WIDGET(popover), visible);
}

gboolean gtk_popover_get_visible_wrapper(GObject *popover) {
    return gtk_widget_get_visible(GTK_WIDGET(popover));
}

void show_popover(GObject *popover) {
    if (GTK_IS_POPOVER(popover)) {
        gtk_widget_show_all(GTK_WIDGET(popover));
        gtk_popover_popup(GTK_POPOVER(popover));
    }
}

void set_popover_position(GObject *popover, GtkPositionType position) {
    if (GTK_IS_POPOVER(popover)) {
        gtk_popover_set_position(GTK_POPOVER(popover), position);
    }
}