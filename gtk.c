#include <gtk/gtk.h>
#include <gtk/gtkspinner.h> 
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










void gtk_entry_set_visibility_wrapper(GObject *entry, gboolean visible) {
    gtk_entry_set_visibility(GTK_ENTRY(entry), visible);
}

gboolean gtk_entry_get_visibility_wrapper(GObject *entry) {
    return gtk_entry_get_visibility(GTK_ENTRY(entry));
}












// Funciones wrapper para GtkComboBoxText
void gtk_combo_box_text_append_wrapper(GObject *combo, const gchar *id, const gchar *text) {
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), id, text);
}

void gtk_combo_box_text_prepend_wrapper(GObject *combo, const gchar *id, const gchar *text) {
    gtk_combo_box_text_prepend(GTK_COMBO_BOX_TEXT(combo), id, text);
}

void gtk_combo_box_text_insert_wrapper(GObject *combo, gint position, const gchar *id, const gchar *text) {
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(combo), position, id, text);
}

void gtk_combo_box_text_remove_all_wrapper(GObject *combo) {
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo));
}

void gtk_combo_box_set_active_wrapper(GObject *combo, gint index) {
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), index);
}

gint gtk_combo_box_get_active_wrapper(GObject *combo) {
    return gtk_combo_box_get_active(GTK_COMBO_BOX(combo));
}

const gchar* gtk_combo_box_text_get_active_text_wrapper(GObject *combo) {
    return gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
}

















// Implementación para GtkSwitch
void gtk_switch_set_active_wrapper(GObject *sw, gboolean active) {
    gtk_switch_set_active(GTK_SWITCH(sw), active);
}

gboolean gtk_switch_get_active_wrapper(GObject *sw) {
    return gtk_switch_get_active(GTK_SWITCH(sw));
}

void go_switch_state_set_bridge(GtkWidget *widget, gboolean state, gpointer data) {
    // Llama a la función Go pasando el estado como parámetro
    goCallbackProxy(data);
}

gboolean isswitch(GObject *object) {
    return GTK_IS_SWITCH(object);
}















// Implementación corregida para GtkScale
void gtk_scale_set_value_wrapper(GObject *scale, gdouble value) {
    gtk_range_set_value(GTK_RANGE(scale), value);
}

gdouble gtk_scale_get_value_wrapper(GObject *scale) {
    return gtk_range_get_value(GTK_RANGE(scale));
}

void gtk_scale_set_range_wrapper(GObject *scale, gdouble min, gdouble max) {
    gtk_range_set_range(GTK_RANGE(scale), min, max);
}

void gtk_scale_set_digits_wrapper(GObject *scale, gint digits) {
    gtk_scale_set_digits(GTK_SCALE(scale), digits);
}

void gtk_scale_set_draw_value_wrapper(GObject *scale, gboolean draw_value) {
    gtk_scale_set_draw_value(GTK_SCALE(scale), draw_value);
}



















// Funciones wrapper para GtkTextView
void gtk_text_view_set_text_wrapper(GObject *text_view, const gchar *text) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, text, -1);
}

gchar* gtk_text_view_get_text_wrapper(GObject *text_view) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    return gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
}

void gtk_text_view_set_editable_wrapper(GObject *text_view, gboolean editable) {
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), editable);
}

gboolean gtk_text_view_get_editable_wrapper(GObject *text_view) {
    return gtk_text_view_get_editable(GTK_TEXT_VIEW(text_view));
}

void gtk_text_view_set_wrap_mode_wrapper(GObject *text_view, GtkWrapMode mode) {
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), mode);
}

GtkWrapMode gtk_text_view_get_wrap_mode_wrapper(GObject *text_view) {
    return gtk_text_view_get_wrap_mode(GTK_TEXT_VIEW(text_view));
}

void gtk_text_view_set_cursor_visible_wrapper(GObject *text_view, gboolean visible) {
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), visible);
}

gboolean gtk_text_view_get_cursor_visible_wrapper(GObject *text_view) {
    return gtk_text_view_get_cursor_visible(GTK_TEXT_VIEW(text_view));
}

















