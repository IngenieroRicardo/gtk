#include <gtk/gtk.h>
#include <gtk/gtkspinner.h> 
#include <stdlib.h>

extern void goCallbackProxy(gpointer data);

typedef struct {
    gint row;
    gint column;
    gchar *id;
} EditedData;

void go_callback_bridge(GtkWidget *widget, gpointer data) {
    goCallbackProxy(data);
}

gboolean isswitch(GObject *object) {
    return GTK_IS_SWITCH(object);
}

void gtk_entry_set_text_wrapper(GObject *entry, const gchar *text) {
    gtk_entry_set_text(GTK_ENTRY(entry), text);
}

const gchar* gtk_entry_get_text_wrapper(GObject *entry) {
    return gtk_entry_get_text(GTK_ENTRY(entry));
}

void gtk_label_set_text_wrapper(GObject *label, const gchar *text) {
    gtk_label_set_text(GTK_LABEL(label), text);
}

const gchar* gtk_label_get_text_wrapper(GObject *label) {
    return gtk_label_get_text(GTK_LABEL(label));
}

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

void gtk_toggle_button_set_active_wrapper(GObject *toggle_widget, gboolean active) {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_widget), active);
}

gboolean gtk_toggle_button_get_active_wrapper(GObject *toggle_widget) {
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_widget));
}

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

void on_cell_edited(GtkCellRendererText *renderer, gchar *path, gchar *new_text, gpointer user_data) {
    gchar *id = (gchar *)user_data;
    GtkTreeView *tree_view = GTK_TREE_VIEW(g_object_get_data(G_OBJECT(renderer), "tree-view"));
    gint column = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(renderer), "column-index"));
    
    // Actualizar el modelo
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeIter iter;
    
    if (gtk_tree_model_get_iter_from_string(model, &iter, path)) {
        gtk_list_store_set(GTK_LIST_STORE(model), &iter, column, new_text, -1);
    }
    
    // Notificar a Go - ahora incluye la columna
    gint row = atoi(path);
    gchar *full_data = g_strdup_printf("%s::%d::%d::%s", id, row, column, new_text);
    goCallbackProxy(full_data);
    g_free(full_data);
}

void gtk_tree_view_set_column_editable(GtkTreeView *tree_view, gint column_index, gboolean editable) {
    GtkTreeViewColumn *column = gtk_tree_view_get_column(tree_view, column_index);
    if (column == NULL) return;
    
    GList *renderers = gtk_cell_layout_get_cells(GTK_CELL_LAYOUT(column));
    if (renderers == NULL) return;
    
    GtkCellRenderer *renderer = GTK_CELL_RENDERER(renderers->data);
    g_object_set(renderer, "editable", editable, NULL);
    
    g_list_free(renderers);
}

void gtk_tree_view_connect_edited_signal(GtkTreeView *tree_view, gint column_index, const gchar *id) {
    GtkTreeViewColumn *column = gtk_tree_view_get_column(tree_view, column_index);
    if (column == NULL) return;
    
    GList *renderers = gtk_cell_layout_get_cells(GTK_CELL_LAYOUT(column));
    if (renderers == NULL) return;
    
    GtkCellRendererText *renderer = GTK_CELL_RENDERER_TEXT(renderers->data);
    
    // Almacenar referencias necesarias en el renderer
    g_object_set_data(G_OBJECT(renderer), "column-index", GINT_TO_POINTER(column_index));
    g_object_set_data(G_OBJECT(renderer), "tree-view", tree_view);

    // Pasar el ID como user_data
    g_signal_connect(renderer, "edited", G_CALLBACK(on_cell_edited), g_strdup(id));
    
    g_list_free(renderers);
}

void gtk_tree_view_set_cell_value(GtkTreeView *tree_view, gint row, gint column, const gchar *new_value) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    if (!model) return;

    GtkTreeIter iter;
    if (!gtk_tree_model_iter_nth_child(model, &iter, NULL, row)) {
        return;
    }

    gtk_list_store_set(GTK_LIST_STORE(model), &iter, column, new_value, -1);
}

gchar* gtk_tree_view_get_row_json(GtkTreeView *tree_view, gint row) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    if (!model) return NULL;

    gint n_columns = gtk_tree_model_get_n_columns(model);
    if (n_columns == 0) return NULL;

    GtkTreeIter iter;
    if (!gtk_tree_model_iter_nth_child(model, &iter, NULL, row)) {
        return NULL;
    }

    GString *json = g_string_new("{");
    gboolean first = TRUE;

    for (gint col = 0; col < n_columns; col++) {
        // Obtener nombre de la columna
        GtkTreeViewColumn *column = gtk_tree_view_get_column(tree_view, col);
        const gchar *col_name = column ? gtk_tree_view_column_get_title(column) : NULL;
        if (!col_name) {
            col_name = g_strdup_printf("Column%d", col+1);
        }

        // Obtener valor de la celda
        GValue value = {0};
        gtk_tree_model_get_value(model, &iter, col, &value);
        
        const gchar *str_val = NULL;
        if (G_VALUE_HOLDS_STRING(&value)) {
            str_val = g_value_get_string(&value);
        } else {
            str_val = "";
        }

        // Agregar al JSON
        if (!first) {
            g_string_append(json, ", ");
        }
        g_string_append_printf(json, "\"%s\": \"%s\"", col_name, str_val ? str_val : "");
        
        g_value_unset(&value);
        first = FALSE;
    }

    g_string_append(json, "}");
    return g_string_free(json, FALSE);
}

void gtk_tree_view_add_empty_row(GtkTreeView *tree_view) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    if (!model) return;

    GtkListStore *store = GTK_LIST_STORE(model);
    GtkTreeIter iter;
    
    gtk_list_store_append(store, &iter);
    
    // Inicializar todas las celdas como vacías
    gint n_columns = gtk_tree_model_get_n_columns(model);
    for (gint i = 0; i < n_columns; i++) {
        gtk_list_store_set(store, &iter, i, "", -1);
    }
}

gboolean gtk_tree_view_remove_selected_row(GtkTreeView *tree_view) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(tree_view);
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
        return TRUE;
    }
    return FALSE;
}

void gtk_statusbar_set_text_wrapper(GObject *statusbar, const gchar *text) {
    if (!GTK_IS_STATUSBAR(statusbar)) return;
    
    // Usamos un context ID fijo para simplificar
    static guint context_id = 0;
    if (context_id == 0) {
        context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), "default");
    }
    
    // Limpiar mensajes previos y mostrar el nuevo
    gtk_statusbar_remove_all(GTK_STATUSBAR(statusbar), context_id);
    gtk_statusbar_push(GTK_STATUSBAR(statusbar), context_id, text);
}

const gchar* gtk_statusbar_get_text_wrapper(GObject *statusbar) {
    if (!GTK_IS_STATUSBAR(statusbar)) return NULL;
    
    // Obtenemos el área de mensajes (GtkBox)
    GtkWidget *message_area = gtk_statusbar_get_message_area(GTK_STATUSBAR(statusbar));
    if (!message_area || !GTK_IS_CONTAINER(message_area)) return NULL;
    
    // Buscamos el último GtkLabel hijo
    GList *children = gtk_container_get_children(GTK_CONTAINER(message_area));
    GList *last = g_list_last(children);
    
    if (last && GTK_IS_LABEL(last->data)) {
        return gtk_label_get_text(GTK_LABEL(last->data));
    }
    
    return NULL;
}

gchar* gtk_file_chooser_get_filename_wrapper(GObject *chooser) {
    return gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
}

void gtk_file_chooser_set_current_folder_wrapper(GObject *chooser, const gchar *folder) {
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(chooser), folder);
}

gboolean handle_popover_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Escape) {
        gtk_widget_hide(widget);
        return TRUE; // Indicamos que hemos manejado el evento
    }
    return FALSE; // Evento no manejado
}

void connect_popover_escape_handler(GObject *popover) {
    g_signal_connect(G_OBJECT(popover), 
                   "key-press-event", 
                   G_CALLBACK(handle_popover_key_press), 
                   NULL);
}

gboolean on_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
    gtk_widget_hide(widget);
    return TRUE; // Indicamos que hemos manejado el evento y no debe continuar
}

void gtk_image_set_from_file_wrapper(GObject *image, const gchar *filename) {
    gtk_image_set_from_file(GTK_IMAGE(image), filename);
}

void gtk_image_set_from_icon_name_wrapper(GObject *image, const gchar *icon_name, int size) {
    gtk_image_set_from_icon_name(GTK_IMAGE(image), icon_name, size);
}
