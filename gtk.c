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



















// Funciones para GtkTreeView
/*void gtk_tree_view_remove_all_columns(GtkTreeView *tree_view) {
    GList *columns = gtk_tree_view_get_columns(tree_view);
    GList *iter = columns;
    
    while (iter != NULL) {
        gtk_tree_view_remove_column(tree_view, GTK_TREE_VIEW_COLUMN(iter->data));
        iter = iter->next;
    }
    
    g_list_free(columns);
}

void gtk_tree_view_append_column_with_title(GtkTreeView *tree_view, const gchar *title, gint column_index) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
        title, renderer, "text", column_index, NULL);
    gtk_tree_view_append_column(tree_view, column);
}

GtkListStore* gtk_list_store_new_from_json(const gchar *json_data, gchar ***column_names, gint *column_count) {
    JsonParser *parser = json_parser_new();
    JsonNode *root = NULL;
    GError *error = NULL;
    
    if (!json_parser_load_from_data(parser, json_data, -1, &error)) {
        g_printerr("Error parsing JSON: %s\n", error->message);
        g_error_free(error);
        g_object_unref(parser);
        return NULL;
    }
    
    root = json_parser_get_root(parser);
    if (!JSON_NODE_HOLDS_ARRAY(root)) {
        g_printerr("JSON root is not an array\n");
        g_object_unref(parser);
        return NULL;
    }
    
    JsonArray *array = json_node_get_array(root);
    guint array_length = json_array_get_length(array);
    
    if (array_length == 0) {
        g_object_unref(parser);
        return NULL;
    }
    
    // Get column names from first object
    JsonObject *first_obj = json_array_get_object_element(array, 0);
    GList *members = json_object_get_members(first_obj);
    *column_count = g_list_length(members);
    *column_names = g_new(gchar*, *column_count + 1);
    
    GType *types = g_new(GType, *column_count);
    gint i = 0;
    
    for (GList *iter = members; iter != NULL; iter = iter->next) {
        (*column_names)[i] = g_strdup(iter->data);
        types[i] = G_TYPE_STRING; // We'll assume all columns are strings for simplicity
        i++;
    }
    (*column_names)[i] = NULL;
    
    g_list_free(members);
    
    // Create the list store
    GtkListStore *store = gtk_list_store_newv(*column_count, types);
    g_free(types);
    
    // Fill the store with data
    for (guint j = 0; j < array_length; j++) {
        JsonObject *obj = json_array_get_object_element(array, j);
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        
        for (i = 0; i < *column_count; i++) {
            const gchar *value = json_object_get_string_member(obj, (*column_names)[i]);
            gtk_list_store_set(store, &iter, i, value ? value : "", -1);
        }
    }
    
    g_object_unref(parser);
    return store;
}*/










// TreeView functions
void gtk_tree_view_remove_all_columns(GtkTreeView *tree_view) {
    GList *columns = gtk_tree_view_get_columns(tree_view);
    GList *iter = columns;
    
    while (iter != NULL) {
        gtk_tree_view_remove_column(tree_view, GTK_TREE_VIEW_COLUMN(iter->data));
        iter = iter->next;
    }
    
    g_list_free(columns);
}

void gtk_tree_view_append_column_with_title(GtkTreeView *tree_view, const gchar *title, gint column_index) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
        title, renderer, "text", column_index, NULL);
    gtk_tree_view_append_column(tree_view, column);
}

GtkListStore* gtk_list_store_new_with_columns(gint n_columns, GType *types) {
    return gtk_list_store_newv(n_columns, types);
}

void gtk_list_store_append_row(GtkListStore *store, gint n_columns, const gchar **values) {
    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    
    for (gint i = 0; i < n_columns; i++) {
        const gchar *val = values[i] ? values[i] : "";
        gtk_list_store_set(store, &iter, i, val, -1);
    }
}


























// Obtiene el modelo del TreeView y cuenta las filas y columnas
void gtk_tree_view_get_model_info(GtkTreeView *tree_view, gint *n_columns, gint *n_rows) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    if (model) {
        *n_columns = gtk_tree_model_get_n_columns(model);
        *n_rows = gtk_tree_model_iter_n_children(model, NULL);
    } else {
        *n_columns = 0;
        *n_rows = 0;
    }
}

// Obtiene el valor de una celda específica
gchar* gtk_tree_view_get_cell_value(GtkTreeView *tree_view, gint row, gint column) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    if (!model) return NULL;

    GtkTreeIter iter;
    if (!gtk_tree_model_iter_nth_child(model, &iter, NULL, row)) {
        return NULL;
    }

    GValue value = {0};
    gtk_tree_model_get_value(model, &iter, column, &value);
    
    if (!G_VALUE_HOLDS_STRING(&value)) {
        g_value_unset(&value);
        return NULL;
    }

    const gchar *str_val = g_value_get_string(&value);
    gchar *result = str_val ? g_strdup(str_val) : g_strdup("");
    g_value_unset(&value);
    
    return result;
}






