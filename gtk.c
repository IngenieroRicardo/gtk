#include <stdio.h>
#include <gtk/gtk.h>
#include <gtk/gtkspinner.h> 
#include <stdlib.h>
#include <glib-object.h>
#include <dirent.h>
#include <sys/stat.h>

extern void goTreeItemDoubleClick(gpointer data);
extern void goSetClipboardText(gpointer text);
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

void gtk_spinner_start_wrapper(GObject *spinner) {
    gtk_spinner_start(GTK_SPINNER(spinner));
}

void gtk_spinner_stop_wrapper(GObject *spinner) {
    gtk_spinner_stop(GTK_SPINNER(spinner));
}


const gchar* get_object_class_name(GObject *object) {
    if (object == NULL) {
        return NULL;
    }
    GType gtype = G_OBJECT_TYPE(object);
    return g_type_name(gtype);
}


















void tree_store_set_string(GtkTreeStore* store, GtkTreeIter* iter, int col, const char* val) {
    gtk_tree_store_set(store, iter,
        col, val,
        -1);
}

// Modifica la función tree_view_button_press_event
gboolean tree_view_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (event->button == GDK_BUTTON_SECONDARY) {
        GtkWidget *menu = GTK_WIDGET(user_data);
        gtk_menu_popup_at_pointer(GTK_MENU(menu), (GdkEvent*)event);
        return TRUE;
    }
    return FALSE;
}

// Modifica tree_selection_changed
void tree_selection_changed(GtkTreeSelection *selection, gpointer user_data) {
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *value;
        gtk_tree_model_get(model, &iter, 2, &value, -1); // Columna 2 es Value
        
        if (value != NULL) {
            // Llama a la función Go para establecer el texto del portapapeles
            goSetClipboardText((gpointer)value);
            g_free(value);
        }
    }
}































// Añadir estas funciones al final del archivo
GtkTreeStore* create_file_model() {
    return gtk_tree_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
}

// Añade esta función para obtener el directorio padre
static gchar* get_parent_directory(const gchar *path) {
    gchar *parent = g_path_get_dirname(path);
    // Evitar devolver el mismo path si ya estamos en la raíz
    if (g_strcmp0(path, parent) == 0) {
        g_free(parent);
        return NULL;
    }
    return parent;
}

void populate_file_model(GtkTreeStore *store, const gchar *path) {
    GtkTreeIter iter;
    gtk_tree_store_append(store, &iter, NULL);
    gtk_tree_store_set(store, &iter, 
                      0, path,
                      1, "directory",
                      2, path,
                      -1);
    
    // Agregar un hijo vacío para que aparezca el expander
    GtkTreeIter child_iter;
    gtk_tree_store_append(store, &child_iter, &iter);
    gtk_tree_store_set(store, &child_iter, 
                      0, "",  // Usamos string vacío en lugar de "Cargando..."
                      1, "",
                      2, "",
                      -1);
}

void gtk_tree_view_refresh(GObject *tree_view) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));
    if (GTK_IS_TREE_STORE(model)) {
        GtkTreeIter iter;
        if (gtk_tree_model_get_iter_first(model, &iter)) {
            gchar *path;
            gtk_tree_model_get(model, &iter, 2, &path, -1);
            
            // Limpiar y recargar el modelo
            gtk_tree_store_clear(GTK_TREE_STORE(model));
            populate_file_model(GTK_TREE_STORE(model), path);
            
            // Expandir todo después de recargar
            gtk_tree_view_expand_all(GTK_TREE_VIEW(tree_view));
            
            g_free(path);
        }
    }
}


// Añade esta función para navegar al directorio padre
void gtk_tree_view_go_back(GObject *tree_view) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));
    if (GTK_IS_TREE_STORE(model)) {
        GtkTreeIter iter;
        if (gtk_tree_model_get_iter_first(model, &iter)) {
            gchar *current_path;
            gtk_tree_model_get(model, &iter, 2, &current_path, -1);
            
            // Obtener el directorio padre
            gchar *parent_path = g_path_get_dirname(current_path);
            
            // Solo si no estamos en la raíz
            if (strcmp(parent_path, ".") != 0 && strcmp(parent_path, "/") != 0) {
                gtk_tree_store_clear(GTK_TREE_STORE(model));
                populate_file_model(GTK_TREE_STORE(model), parent_path);
            }
            
            g_free(current_path);
            g_free(parent_path);
        }
    }
}










// Elimina archivos o directorios de forma recursiva
static int delete_recursive(const gchar *path) {
    struct stat statbuf;

    if (stat(path, &statbuf) != 0) {
        return -1; // No se pudo obtener info
    }

    if (S_ISDIR(statbuf.st_mode)) {
        DIR *dir = opendir(path);
        if (!dir) return -1;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (g_strcmp0(entry->d_name, ".") == 0 || g_strcmp0(entry->d_name, "..") == 0)
                continue;

            gchar *child_path = g_build_filename(path, entry->d_name, NULL);
            if (delete_recursive(child_path) != 0) {
                g_free(child_path);
                closedir(dir);
                return -1;
            }
            g_free(child_path);
        }
        closedir(dir);

        return rmdir(path); // borrar el directorio una vez vacío
    } else {
        return remove(path); // eliminar archivo
    }
}


static void on_delete_item_activate(GtkMenuItem *menuitem, gpointer user_data) {
    GtkWidget *tree_view = GTK_WIDGET(user_data);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *name, *path, *type;
        gtk_tree_model_get(model, &iter, 0, &name, 1, &type, 2, &path, -1);

        // Preguntar confirmación al usuario
        gchar *msg = g_strdup_printf("¿Seguro que quieres eliminar \"%s\"?", name);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_WARNING,
                                                   GTK_BUTTONS_OK_CANCEL,
                                                   "%s", msg);
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        g_free(msg);

        if (response == GTK_RESPONSE_OK) {
            int status = -1;

            status = delete_recursive(path);

            if (status == 0) {
                gtk_tree_view_refresh(G_OBJECT(tree_view)); // refrescar árbol
            } else {
                GtkWidget *err_dialog = gtk_message_dialog_new(NULL,
                        GTK_DIALOG_MODAL,
                        GTK_MESSAGE_ERROR,
                        GTK_BUTTONS_CLOSE,
                        "No se pudo eliminar: %s", path);
                gtk_dialog_run(GTK_DIALOG(err_dialog));
                gtk_widget_destroy(err_dialog);
            }
        }

        g_free(name);
        g_free(type);
        g_free(path);
    }
}


static void on_rename_item_activate(GtkMenuItem *menuitem, gpointer user_data) {
    GtkWidget *tree_view = GTK_WIDGET(user_data);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *old_name, *path;
        gtk_tree_model_get(model, &iter, 0, &old_name, 2, &path, -1);

        // Crear un diálogo de entrada para el nuevo nombre
        GtkWidget *dialog = gtk_dialog_new_with_buttons("Renombrar",
                                                        NULL,
                                                        GTK_DIALOG_MODAL,
                                                        "_Cancelar", GTK_RESPONSE_CANCEL,
                                                        "_Renombrar", GTK_RESPONSE_ACCEPT,
                                                        NULL);
        GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        GtkWidget *entry = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(entry), old_name);
        gtk_box_pack_start(GTK_BOX(content_area), entry, TRUE, TRUE, 0);
        gtk_widget_show_all(dialog);

        if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
            const gchar *new_name = gtk_entry_get_text(GTK_ENTRY(entry));
            gchar *parent_dir = g_path_get_dirname(path);
            gchar *new_path = g_build_filename(parent_dir, new_name, NULL);

            // Intentar renombrar usando rename()
            if (rename(path, new_path) == 0) {
                gtk_tree_view_refresh(G_OBJECT(tree_view)); // refrescar
            } else {
            
            	GtkWidget *err_dialog = gtk_message_dialog_new(NULL,
            	                        GTK_DIALOG_MODAL,
            	                        GTK_MESSAGE_ERROR,
            	                        GTK_BUTTONS_CLOSE,
            	                        "Error al renombrar %s a %s", path, new_path);
            	                gtk_dialog_run(GTK_DIALOG(err_dialog));
            	                gtk_widget_destroy(err_dialog);
            }

            g_free(parent_dir);
            g_free(new_path);
        }

        gtk_widget_destroy(dialog);
        g_free(old_name);
        g_free(path);
    }
}













// Actualiza la función del menú contextual
static gboolean on_tree_view_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (event->button == GDK_BUTTON_SECONDARY) { // Click derecho
        GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
        GtkTreeModel *model;
        GtkTreeIter iter;
        
        if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
            // Crear menú contextual
            GtkWidget *menu = gtk_menu_new();
            
            // Opción Recargar
            GtkWidget *refresh_item = gtk_menu_item_new_with_label("Recargar");
            g_signal_connect_swapped(refresh_item, "activate", 
                                    G_CALLBACK(gtk_tree_view_refresh), 
                                    widget);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), refresh_item);
            
            // Opción Atrás
            GtkWidget *back_item = gtk_menu_item_new_with_label("Atrás");
            g_signal_connect_swapped(back_item, "activate", 
                                   G_CALLBACK(gtk_tree_view_go_back), 
                                   widget);
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), back_item);	
            
            // Separador
            GtkWidget *separator = gtk_separator_menu_item_new();
            gtk_menu_shell_append(GTK_MENU_SHELL(menu), separator);

	//on_rename_item_activate
	GtkWidget *rename_item = gtk_menu_item_new_with_label("Renombrar");
    g_signal_connect(rename_item, "activate", G_CALLBACK(on_rename_item_activate), widget);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), rename_item);


// Opción Eliminar
GtkWidget *delete_item = gtk_menu_item_new_with_label("Eliminar");
g_signal_connect(delete_item, "activate", G_CALLBACK(on_delete_item_activate), widget);
gtk_menu_shell_append(GTK_MENU_SHELL(menu), delete_item);

            
            // Mostrar menú
            gtk_widget_show_all(menu);
            gtk_menu_popup_at_pointer(GTK_MENU(menu), (GdkEvent*)event);
            return TRUE;
        }
    }
    return FALSE;
}


// Corrección: Cambiar GtkTreeTreePath por GtkTreePath
gboolean on_row_expanded(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeStore *store = GTK_TREE_STORE(model);
    
    gchar *full_path;
    GValue value = G_VALUE_INIT;
    
    // Obtener la ruta completa del directorio
    gtk_tree_model_get_value(model, iter, 2, &value);
    full_path = g_strdup(g_value_get_string(&value));
    g_value_unset(&value);
    
    if (full_path == NULL) {
        return FALSE;
    }
    
    // Verificar si ya tiene hijos reales (no solo el placeholder)
    GtkTreeIter child_iter;
    gboolean has_real_children = FALSE;
    
    if (gtk_tree_model_iter_children(model, &child_iter, iter)) {
        gchar *child_text;
        gtk_tree_model_get(model, &child_iter, 0, &child_text, -1);
        
        // Si el primer hijo no está vacío, ya tiene hijos reales
        has_real_children = (g_strcmp0(child_text, "") != 0);
        g_free(child_text);
    }
    
    // Solo cargar si no tiene hijos reales
    if (!has_real_children) {
        // Eliminar el placeholder si existe
        if (gtk_tree_model_iter_children(model, &child_iter, iter)) {
            gtk_tree_store_remove(store, &child_iter);
        }
        
        // Cargar el contenido real del directorio
        DIR *dir;
        struct dirent *entry;
        struct stat statbuf;
        
        if ((dir = opendir(full_path)) != NULL) {
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                    continue;
                }
                
                gchar *child_path = g_build_filename(full_path, entry->d_name, NULL);
                if (stat(child_path, &statbuf) == 0) {
                    GtkTreeIter new_child_iter;
                    gtk_tree_store_append(store, &new_child_iter, iter);
                    
                    const gchar *type = S_ISDIR(statbuf.st_mode) ? "directory" : "file";
                    gtk_tree_store_set(store, &new_child_iter, 
                                      0, entry->d_name,
                                      1, type,
                                      2, child_path,
                                      -1);
                    
                    // Si es directorio, agregar un hijo vacío para mostrar el expander
                    if (S_ISDIR(statbuf.st_mode)) {
                        GtkTreeIter dummy_iter;
                        gtk_tree_store_append(store, &dummy_iter, &new_child_iter);
                        gtk_tree_store_set(store, &dummy_iter, 
                                          0, "",
                                          1, "",
                                          2, "",
                                          -1);
                    }
                }
                g_free(child_path);
            }
            closedir(dir);
        }
    }
    
    g_free(full_path);
    return FALSE;
}


// Función puente para el doble click
void on_tree_item_activated(GtkTreeView *tree_view, 
                          GtkTreePath *path,
                          GtkTreeViewColumn *column,
                          gpointer user_data) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeIter iter;
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gchar *name, *full_path, *type;
        gtk_tree_model_get(model, &iter, 
                          0, &name,      // Nombre del item
                          1, &type,      // Tipo (file/directory)
                          2, &full_path, // Ruta completa
                          -1);
        
        // Formato: "nombre|ruta|tipo"
        gchar *result = g_strdup_printf("%s|%s|%s", name, full_path, type);
        
        goTreeItemDoubleClick((gpointer)result);
        
        g_free(name);
        g_free(type);
        g_free(full_path);
        g_free(result);
    }
}

void gtk_tree_view_setup_file_view(GObject *tree_view) {
    // Crear modelo
    GtkTreeStore *store = create_file_model();
    
    // Configurar columnas (sin texto de encabezado)
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 0);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    
    // Ocultar los encabezados
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_view), FALSE);
    
    // Establecer modelo
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    // Configurar propiedades visuales del árbol
    gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(tree_view), TRUE);
    
    // Conectar señal para cargar contenido dinámico al expandir
    g_signal_connect(tree_view, "row-expanded", 
                    G_CALLBACK(on_row_expanded), NULL);

    // Conectar señal de doble click (row-activated)
    g_signal_connect(tree_view, "row-activated", 
                    G_CALLBACK(on_tree_item_activated), NULL);

    // Conectar señal de click derecho
    g_signal_connect(tree_view, "button-press-event", 
                    G_CALLBACK(on_tree_view_button_press), NULL);

}

void gtk_tree_view_set_path(GObject *tree_view, const gchar *path) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));
    if (GTK_IS_TREE_STORE(model)) {
        gtk_tree_store_clear(GTK_TREE_STORE(model));
        populate_file_model(GTK_TREE_STORE(model), path);
    }
}

// Función para obtener la ruta actual del TreeView
gchar* gtk_tree_view_get_current_path(GObject *tree_view) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));
    if (model == NULL) {
        return g_strdup("");
    }

    GtkTreeIter iter;
    if (!gtk_tree_model_get_iter_first(model, &iter)) {
        return g_strdup("");
    }

    gchar *path;
    gtk_tree_model_get(model, &iter, 2, &path, -1);
    
    // Devolver una copia para que Go pueda manejar la memoria
    return g_strdup(path ? path : "");
}


char* gtk_file_chooser_get_current_folder_wrapper(GObject* chooser) {
    return gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(chooser));
}
