package gtk

/*
#cgo pkg-config: gtk+-3.0
#include <gtk/gtk.h>
#include <stdlib.h>



// Solo declaración (no definición)
extern void goCallbackProxy(gpointer data);

// Declaración de la función puente (definición en otro archivo)
extern void go_callback_bridge(GtkWidget *widget, gpointer data);


// Nuevas declaraciones con GObject* como parámetro
extern void gtk_entry_set_text_wrapper(GObject *entry, const gchar *text);
extern const gchar* gtk_entry_get_text_wrapper(GObject *entry);


// Nuevas declaraciones para GtkLabel
extern void gtk_label_set_text_wrapper(GObject *label, const gchar *text);
extern const gchar* gtk_label_get_text_wrapper(GObject *label);



// Nuevas declaraciones para GtkButton
extern void gtk_button_set_label_wrapper(GObject *button, const gchar *text);
extern const gchar* gtk_button_get_label_wrapper(GObject *button);
extern void gtk_button_set_sensitive_wrapper(GObject *button, gboolean sensitive);
extern gboolean gtk_button_get_sensitive_wrapper(GObject *button);


extern void gtk_toggle_button_set_active_wrapper(GObject *toggle_widget, gboolean active);
extern gboolean gtk_toggle_button_get_active_wrapper(GObject *toggle_widget);





// Nuevas declaraciones para GtkMenuItem
extern void gtk_menu_item_set_label_wrapper(GObject *menu_item, const gchar *label);
extern const gchar* gtk_menu_item_get_label_wrapper(GObject *menu_item);
extern void gtk_menu_item_set_sensitive_wrapper(GObject *menu_item, gboolean sensitive);
extern gboolean gtk_menu_item_get_sensitive_wrapper(GObject *menu_item);
extern void gtk_menu_item_set_active_wrapper(GObject *menu_item, gboolean active);
extern gboolean gtk_menu_item_get_active_wrapper(GObject *menu_item);






// Popover functions
extern void gtk_popover_set_visible_wrapper(GObject *popover, gboolean visible);
extern gboolean gtk_popover_get_visible_wrapper(GObject *popover);
extern void show_popover(GObject *popover);
extern void set_popover_position(GObject *popover, GtkPositionType position);










extern void gtk_entry_set_visibility_wrapper(GObject *entry, gboolean visible);
extern gboolean gtk_entry_get_visibility_wrapper(GObject *entry);









extern void gtk_combo_box_text_append_wrapper(GObject *combo, const gchar *id, const gchar *text);
extern void gtk_combo_box_text_prepend_wrapper(GObject *combo, const gchar *id, const gchar *text);
extern void gtk_combo_box_text_insert_wrapper(GObject *combo, gint position, const gchar *id, const gchar *text);
extern void gtk_combo_box_text_remove_all_wrapper(GObject *combo);
extern void gtk_combo_box_set_active_wrapper(GObject *combo, gint index);
extern gint gtk_combo_box_get_active_wrapper(GObject *combo);
extern const gchar* gtk_combo_box_text_get_active_text_wrapper(GObject *combo);





// Declaraciones para GtkSwitch
extern void gtk_switch_set_active_wrapper(GObject *sw, gboolean active);
extern gboolean gtk_switch_get_active_wrapper(GObject *sw);










extern void gtk_scale_set_value_wrapper(GObject *scale, gdouble value);
extern gdouble gtk_scale_get_value_wrapper(GObject *scale);
extern void gtk_scale_set_range_wrapper(GObject *scale, gdouble min, gdouble max);
extern void gtk_scale_set_digits_wrapper(GObject *scale, gint digits);
extern void gtk_scale_set_draw_value_wrapper(GObject *scale, gboolean draw_value);






extern void go_switch_state_set_bridge(GtkWidget *widget, gboolean state, gpointer data);
extern gboolean isswitch(GObject *object);










extern void gtk_text_view_set_text_wrapper(GObject *text_view, const gchar *text);
extern gchar* gtk_text_view_get_text_wrapper(GObject *text_view);
extern void gtk_text_view_set_editable_wrapper(GObject *text_view, gboolean editable);
extern gboolean gtk_text_view_get_editable_wrapper(GObject *text_view);
extern void gtk_text_view_set_wrap_mode_wrapper(GObject *text_view, GtkWrapMode mode);
extern GtkWrapMode gtk_text_view_get_wrap_mode_wrapper(GObject *text_view);
extern void gtk_text_view_set_cursor_visible_wrapper(GObject *text_view, gboolean visible);
extern gboolean gtk_text_view_get_cursor_visible_wrapper(GObject *text_view);













// ------------------------------




extern void gtk_tree_view_remove_all_columns(GtkTreeView *tree_view);
extern void gtk_tree_view_append_column_with_title(GtkTreeView *tree_view, const gchar *title, gint column_index);
extern GtkListStore* gtk_list_store_new_with_columns(gint n_columns, GType *types);
extern void gtk_list_store_append_row(GtkListStore *store, gint n_columns, const gchar **values);

extern void gtk_tree_view_get_model_info(GtkTreeView *tree_view, gint *n_columns, gint *n_rows);
extern gchar* gtk_tree_view_get_cell_value(GtkTreeView *tree_view, gint row, gint column);


extern void gtk_tree_view_set_column_editable(GtkTreeView *tree_view, gint column_index, gboolean editable);
extern void gtk_tree_view_connect_edited_signal(GtkTreeView *tree_view, gint column_index, const gchar *id);
extern void gtk_tree_view_set_cell_value(GtkTreeView *tree_view, gint row, gint column, const gchar *new_value);






*/
import "C"
import (
	"errors"
	"sync"
	"unsafe"
	"fmt"
	"strings"
	"encoding/json"
	"runtime"
	"strconv"
)

    

var (
    callbackMutex   sync.Mutex
    callbacks       = make(map[string]func())
    switchCallbacks = make(map[string]func(bool))
    globalBuilder   *C.GtkBuilder
)

var (
    editedCallbacks = make(map[string]func(row, col int, newValue string)) // Nuevo mapa para callbacks de edición
)

//export goCallbackProxy
func goCallbackProxy(data unsafe.Pointer) {

	fullData := C.GoString((*C.char)(data))
    
    parts := strings.SplitN(fullData, "::", 3) // Cambiado a 3 partes
    if len(parts) == 3 {
        id := parts[0]
        row, _ := strconv.Atoi(parts[1])
        value := parts[2]
        
        callbackMutex.Lock()
        if cb, ok := editedCallbacks[id]; ok {
            cb(row, 0, value) // El índice de columna ya se maneja en el callback
        }
        callbackMutex.Unlock()
        return
    }

    


    callbackMutex.Lock()
    if cb, ok := callbacks[fullData]; ok {
        cb()
    }
    callbackMutex.Unlock()
    
	id := C.GoString((*C.char)(data))



    if scb, ok := switchCallbacks[id]; ok {
        parts := strings.Split(id, "::")
        if len(parts) > 0 {
            switchName := parts[0]
            cSwitchName := C.CString(switchName)
            defer C.free(unsafe.Pointer(cSwitchName))
            
            widget := C.gtk_builder_get_object(globalBuilder, cSwitchName)
            if widget != nil && C.isswitch(widget)!= 0 {
                state := C.gtk_switch_get_active((*C.GtkSwitch)(unsafe.Pointer(widget)))
                scb(state != 0)
            }
        }
    }
}
    

type GTKApp struct {
	builder *C.GtkBuilder
}

func NewGTKApp() *GTKApp {
	C.gtk_init(nil, nil)
	return &GTKApp{}
}

func (app *GTKApp) LoadUI(filename string) error {
    app.builder = C.gtk_builder_new()
    if app.builder == nil {
        return errors.New("no se pudo crear el builder")
    }

    // Establece el builder global
    globalBuilder = app.builder

    cFilename := C.CString(filename)
    defer C.free(unsafe.Pointer(cFilename))

    if C.gtk_builder_add_from_file(app.builder, cFilename, nil) == 0 {
        C.g_object_unref(C.gpointer(unsafe.Pointer(app.builder)))
        globalBuilder = nil
        return errors.New("error al cargar el archivo UI")
    }

    return nil
}

func (app *GTKApp) ConnectSignal(widgetName, signal string, callback func()) {
    cWidgetName := C.CString(widgetName)
    defer C.free(unsafe.Pointer(cWidgetName))

    cSignal := C.CString(signal)
    defer C.free(unsafe.Pointer(cSignal))

    widget := C.gtk_builder_get_object(app.builder, cWidgetName)
    if widget == nil {
        return
    }

    // Crear un ID único basado en widgetName y signal
    id := widgetName + "::" + signal
    cId := C.CString(id)
    
    callbackMutex.Lock()
    callbacks[id] = callback
    callbackMutex.Unlock()

    C.g_signal_connect_data(
        C.gpointer(widget),
        cSignal,
        C.GCallback(C.go_callback_bridge),
        C.gpointer(unsafe.Pointer(cId)),
        C.GClosureNotify(C.free), // Esto liberará la memoria cuando la señal se desconecte
        0,
    )
}

func (app *GTKApp) ConnectSignalDirect(widgetName, signal string, callback uintptr, data unsafe.Pointer) {
    cWidgetName := C.CString(widgetName)
    defer C.free(unsafe.Pointer(cWidgetName))

    cSignal := C.CString(signal)
    defer C.free(unsafe.Pointer(cSignal))

    widget := C.gtk_builder_get_object(app.builder, cWidgetName)
    var gCallback C.GCallback
    if callback == 0 {
        gCallback = C.GCallback(C.gtk_main_quit)
    } else if callback == 1 {
        gCallback = C.GCallback(C.gtk_window_close)
    } else {
    	gCallback = C.GCallback(C.gtk_widget_hide)
    }
    
    C.g_signal_connect_data(
        C.gpointer(widget),
        cSignal,
        gCallback,
        C.gpointer(data),
        nil,
        0,
    )
}

func (app *GTKApp) GetWindow(name string) unsafe.Pointer {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	obj := C.gtk_builder_get_object(app.builder, cName)
	return unsafe.Pointer(obj)
}


func (app *GTKApp) Run(window unsafe.Pointer) {
    gtkwidget := (*C.GtkWidget)(window)
    C.gtk_widget_show_all(gtkwidget)
    C.gtk_main()
}

func (app *GTKApp) Quit() {
	C.gtk_main_quit()
}

func (app *GTKApp) Cleanup() {
    if app.builder != nil {
        C.g_object_unref(C.gpointer(unsafe.Pointer(app.builder)))
    }
    callbackMutex.Lock()
    callbacks = make(map[string]func())
    callbackMutex.Unlock()
}






// SetEntryText establece el texto de un GtkEntry
func (app *GTKApp) SetEntryText(widgetName, text string) {
	cWidgetName := C.CString(widgetName)
	defer C.free(unsafe.Pointer(cWidgetName))

	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	widget := C.gtk_builder_get_object(app.builder, cWidgetName)
	if widget != nil {
		C.gtk_entry_set_text_wrapper((*C.GObject)(widget), cText)
	}
}

// GetEntryText obtiene el texto de un GtkEntry
func (app *GTKApp) GetEntryText(widgetName string) string {
	cWidgetName := C.CString(widgetName)
	defer C.free(unsafe.Pointer(cWidgetName))

	widget := C.gtk_builder_get_object(app.builder, cWidgetName)
	if widget != nil {
		cText := C.gtk_entry_get_text_wrapper((*C.GObject)(widget))
		return C.GoString(cText)
	}
	return ""
}






// SetLabelText establece el texto de un GtkLabel
func (app *GTKApp) SetLabelText(widgetName, text string) {
	cWidgetName := C.CString(widgetName)
	defer C.free(unsafe.Pointer(cWidgetName))

	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	widget := C.gtk_builder_get_object(app.builder, cWidgetName)
	if widget != nil {
		C.gtk_label_set_text_wrapper((*C.GObject)(widget), cText)
	}
}

// GetLabelText obtiene el texto de un GtkLabel
func (app *GTKApp) GetLabelText(widgetName string) string {
	cWidgetName := C.CString(widgetName)
	defer C.free(unsafe.Pointer(cWidgetName))

	widget := C.gtk_builder_get_object(app.builder, cWidgetName)
	if widget != nil {
		cText := C.gtk_label_get_text_wrapper((*C.GObject)(widget))
		return C.GoString(cText)
	}
	return ""
}










// SetButtonText establece el texto de un GtkButton
func (app *GTKApp) SetButtonText(widgetName, text string) {
	cWidgetName := C.CString(widgetName)
	defer C.free(unsafe.Pointer(cWidgetName))

	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	widget := C.gtk_builder_get_object(app.builder, cWidgetName)
	if widget != nil {
		C.gtk_button_set_label_wrapper((*C.GObject)(widget), cText)
	}
}

// GetButtonText obtiene el texto de un GtkButton
func (app *GTKApp) GetButtonText(widgetName string) string {
	cWidgetName := C.CString(widgetName)
	defer C.free(unsafe.Pointer(cWidgetName))

	widget := C.gtk_builder_get_object(app.builder, cWidgetName)
	if widget != nil {
		cText := C.gtk_button_get_label_wrapper((*C.GObject)(widget))
		return C.GoString(cText)
	}
	return ""
}

// SetButtonSensitive establece la sensibilidad de un GtkButton
func (app *GTKApp) SetButtonSensitive(widgetName string, sensitive bool) {
	cWidgetName := C.CString(widgetName)
	defer C.free(unsafe.Pointer(cWidgetName))

	var cSensitive C.gboolean
	if sensitive {
		cSensitive = C.TRUE
	} else {
		cSensitive = C.FALSE
	}

	widget := C.gtk_builder_get_object(app.builder, cWidgetName)
	if widget != nil {
		C.gtk_button_set_sensitive_wrapper((*C.GObject)(widget), cSensitive)
	}
}

// GetButtonSensitive obtiene el estado de sensibilidad de un GtkButton
func (app *GTKApp) GetButtonSensitive(widgetName string) bool {
	cWidgetName := C.CString(widgetName)
	defer C.free(unsafe.Pointer(cWidgetName))

	widget := C.gtk_builder_get_object(app.builder, cWidgetName)
	if widget != nil {
		return C.gtk_button_get_sensitive_wrapper((*C.GObject)(widget)) != 0
	}
	return false
}
















// SetCheckButtonActive marca el GtkCheckButton
func (app *GTKApp) SetCheckButtonUnchecked(widgetName string) {
    app.setCheckButtonState(widgetName, true)
}

// SetCheckButtonInactive desmarca el GtkCheckButton
func (app *GTKApp) SetCheckButtonChecked(widgetName string) {
    app.setCheckButtonState(widgetName, false)
}

// Función interna para manejar el estado
func (app *GTKApp) setCheckButtonState(widgetName string, active bool) {
    cWidgetName := C.CString(widgetName)
    defer C.free(unsafe.Pointer(cWidgetName))

    var cActive C.gboolean
    if active {
        cActive = C.TRUE
    } else {
        cActive = C.FALSE
    }

    widget := C.gtk_builder_get_object(app.builder, cWidgetName)
    if widget != nil {
        C.gtk_toggle_button_set_active_wrapper((*C.GObject)(widget), cActive)
    }
}

// GetCheckButtonStatus (se mantiene igual)
func (app *GTKApp) GetCheckButtonStatus(widgetName string) bool {
    cWidgetName := C.CString(widgetName)
    defer C.free(unsafe.Pointer(cWidgetName))

    widget := C.gtk_builder_get_object(app.builder, cWidgetName)
    if widget != nil {
        return C.gtk_toggle_button_get_active_wrapper((*C.GObject)(widget)) != 0
    }
    return false
}

// ToggleCheckButton (se mantiene igual)
func (app *GTKApp) ToggleCheckButton(widgetName string) {
    app.toggleWidget(widgetName)
}

func (app *GTKApp) ToggleToggleButton(widgetName string) {
    app.toggleWidget(widgetName)
}

func (app *GTKApp) toggleWidget(widgetName string) {
    currentState := app.getToggleState(widgetName)
    app.setToggleState(widgetName, !currentState)
}















// Funciones para ToggleButton
func (app *GTKApp) SetToggleButtonActive(widgetName string) {
    app.setToggleState(widgetName, true)
}

func (app *GTKApp) SetToggleButtonInactive(widgetName string) {
    app.setToggleState(widgetName, false)
}

func (app *GTKApp) GetToggleButtonActive(widgetName string) bool {
    return app.getToggleState(widgetName)
}

func (app *GTKApp) getToggleState(widgetName string) bool {
    cWidgetName := C.CString(widgetName)
    defer C.free(unsafe.Pointer(cWidgetName))

    widget := C.gtk_builder_get_object(app.builder, cWidgetName)
    if widget != nil {
        return C.gtk_toggle_button_get_active_wrapper((*C.GObject)(widget)) != 0
    }
    return false
}

// Función base común para toggle/check buttons
func (app *GTKApp) setToggleState(widgetName string, active bool) {
    cWidgetName := C.CString(widgetName)
    defer C.free(unsafe.Pointer(cWidgetName))

    var cActive C.gboolean
    if active {
        cActive = C.TRUE
    } else {
        cActive = C.FALSE
    }

    widget := C.gtk_builder_get_object(app.builder, cWidgetName)
    if widget != nil {
        C.gtk_toggle_button_set_active_wrapper((*C.GObject)(widget), cActive)
    }
}
































// SetMenuItemLabel establece la etiqueta de un GtkMenuItem
func (app *GTKApp) SetMenuItemLabel(itemName, label string) {
	cItemName := C.CString(itemName)
	defer C.free(unsafe.Pointer(cItemName))

	cLabel := C.CString(label)
	defer C.free(unsafe.Pointer(cLabel))

	item := C.gtk_builder_get_object(app.builder, cItemName)
	if item != nil {
		C.gtk_menu_item_set_label_wrapper((*C.GObject)(item), cLabel)
	}
}

// GetMenuItemLabel obtiene la etiqueta de un GtkMenuItem
func (app *GTKApp) GetMenuItemLabel(itemName string) string {
	cItemName := C.CString(itemName)
	defer C.free(unsafe.Pointer(cItemName))

	item := C.gtk_builder_get_object(app.builder, cItemName)
	if item != nil {
		cLabel := C.gtk_menu_item_get_label_wrapper((*C.GObject)(item))
		return C.GoString(cLabel)
	}
	return ""
}

// SetMenuItemSensitive establece la sensibilidad de un GtkMenuItem
func (app *GTKApp) SetMenuItemSensitive(itemName string, sensitive bool) {
	cItemName := C.CString(itemName)
	defer C.free(unsafe.Pointer(cItemName))

	var cSensitive C.gboolean
	if sensitive {
		cSensitive = C.TRUE
	} else {
		cSensitive = C.FALSE
	}

	item := C.gtk_builder_get_object(app.builder, cItemName)
	if item != nil {
		C.gtk_menu_item_set_sensitive_wrapper((*C.GObject)(item), cSensitive)
	}
}

// GetMenuItemSensitive obtiene la sensibilidad de un GtkMenuItem
func (app *GTKApp) GetMenuItemSensitive(itemName string) bool {
	cItemName := C.CString(itemName)
	defer C.free(unsafe.Pointer(cItemName))

	item := C.gtk_builder_get_object(app.builder, cItemName)
	if item != nil {
		return C.gtk_menu_item_get_sensitive_wrapper((*C.GObject)(item)) != 0
	}
	return false
}


func (app *GTKApp) SetCheckMenuItemChecked(itemName string) {
    app.setCheckMenuItemState(itemName, true)
}
func (app *GTKApp) SetCheckMenuItemUnchecked(itemName string) {
    app.setCheckMenuItemState(itemName, false)
}

func (app *GTKApp) setCheckMenuItemState(itemName string, active bool) {
    cItemName := C.CString(itemName)
    defer C.free(unsafe.Pointer(cItemName))

    var cActive C.gboolean
    if active {
        cActive = C.TRUE
    } else {
        cActive = C.FALSE
    }

    item := C.gtk_builder_get_object(app.builder, cItemName)
    if item != nil {
        C.gtk_menu_item_set_active_wrapper((*C.GObject)(item), cActive)
    }
}

// SetCheckMenuItemActive establece el estado activo de un GtkCheckMenuItem
func (app *GTKApp) SetCheckMenuItemActive(itemName string, active bool) {
	cItemName := C.CString(itemName)
	defer C.free(unsafe.Pointer(cItemName))

	var cActive C.gboolean
	if active {
		cActive = C.TRUE
	} else {
		cActive = C.FALSE
	}

	item := C.gtk_builder_get_object(app.builder, cItemName)
	if item != nil {
		C.gtk_menu_item_set_active_wrapper((*C.GObject)(item), cActive)
	}
}

// GetCheckMenuItemActive obtiene el estado activo de un GtkCheckMenuItem
func (app *GTKApp) GetCheckMenuItemStatus(itemName string) bool {
	cItemName := C.CString(itemName)
	defer C.free(unsafe.Pointer(cItemName))

	item := C.gtk_builder_get_object(app.builder, cItemName)
	if item != nil {
		return C.gtk_menu_item_get_active_wrapper((*C.GObject)(item)) != 0
	}
	return false
}

// ToggleCheckMenuItem alterna el estado de un GtkCheckMenuItem
func (app *GTKApp) ToggleCheckMenuItem(itemName string) {
	currentState := app.GetCheckMenuItemStatus(itemName)
	app.SetCheckMenuItemActive(itemName, !currentState)
}














// ShowPopover muestra un GtkPopover con todas las características necesarias
func (app *GTKApp) ShowPopover(popoverName string) {
	cPopoverName := C.CString(popoverName)
	defer C.free(unsafe.Pointer(cPopoverName))

	popover := C.gtk_builder_get_object(app.builder, cPopoverName)
	if popover != nil {
		app.setPopoverVisibility(popoverName, true)
		C.show_popover((*C.GObject)(popover))
	}
}

// HidePopover oculta un GtkPopover
func (app *GTKApp) HidePopover(popoverName string) {
	app.setPopoverVisibility(popoverName, false)
}

// SetPopoverPosition establece la posición del popover
func (app *GTKApp) SetPopoverPosition(popoverName string, position string) {
	cPopoverName := C.CString(popoverName)
	defer C.free(unsafe.Pointer(cPopoverName))

	popover := C.gtk_builder_get_object(app.builder, cPopoverName)
	if popover != nil {
		var pos C.GtkPositionType
		switch position {
		case "top":
			pos = C.GTK_POS_TOP
		case "bottom":
			pos = C.GTK_POS_BOTTOM
		case "left":
			pos = C.GTK_POS_LEFT
		case "right":
			pos = C.GTK_POS_RIGHT
		default:
			pos = C.GTK_POS_BOTTOM
		}
		C.set_popover_position((*C.GObject)(popover), pos)
	}
}

// setPopoverVisibility función interna para manejar visibilidad
func (app *GTKApp) setPopoverVisibility(popoverName string, visible bool) {
	cPopoverName := C.CString(popoverName)
	defer C.free(unsafe.Pointer(cPopoverName))

	var cVisible C.gboolean
	if visible {
		cVisible = C.TRUE
	} else {
		cVisible = C.FALSE
	}

	popover := C.gtk_builder_get_object(app.builder, cPopoverName)
	if popover != nil {
		C.gtk_popover_set_visible_wrapper((*C.GObject)(popover), cVisible)
	}
}

// IsPopoverVisible verifica si un popover está visible
func (app *GTKApp) IsPopoverVisible(popoverName string) bool {
	cPopoverName := C.CString(popoverName)
	defer C.free(unsafe.Pointer(cPopoverName))

	popover := C.gtk_builder_get_object(app.builder, cPopoverName)
	if popover != nil {
		return C.gtk_popover_get_visible_wrapper((*C.GObject)(popover)) != 0
	}
	return false
}



















func (app *GTKApp) SetRadioButtonActive(buttonName string) {
    cButtonName := C.CString(buttonName)
    defer C.free(unsafe.Pointer(cButtonName))

    widget := C.gtk_builder_get_object(app.builder, cButtonName)
    if widget != nil {
        C.gtk_toggle_button_set_active_wrapper((*C.GObject)(widget), C.TRUE)
    }
}

// GetRadioButtonActive obtiene el estado de un GtkRadioButton
func (app *GTKApp) GetRadioButtonActive(buttonName string) bool {
    cButtonName := C.CString(buttonName)
    defer C.free(unsafe.Pointer(cButtonName))

    widget := C.gtk_builder_get_object(app.builder, cButtonName)
    if widget != nil {
        return C.gtk_toggle_button_get_active_wrapper((*C.GObject)(widget)) != 0
    }
    return false
}









// SetEntryVisibility establece la visibilidad del texto en un GtkEntry
func (app *GTKApp) SetEntryVisibility(entryName string, visible bool) {
    cEntryName := C.CString(entryName)
    defer C.free(unsafe.Pointer(cEntryName))

    var cVisible C.gboolean
    if visible {
        cVisible = C.TRUE
    } else {
        cVisible = C.FALSE
    }

    widget := C.gtk_builder_get_object(app.builder, cEntryName)
    if widget != nil {
        C.gtk_entry_set_visibility_wrapper((*C.GObject)(widget), cVisible)
    }
}

// GetEntryVisibility obtiene la visibilidad del texto en un GtkEntry
func (app *GTKApp) GetEntryVisibility(entryName string) bool {
    cEntryName := C.CString(entryName)
    defer C.free(unsafe.Pointer(cEntryName))

    widget := C.gtk_builder_get_object(app.builder, cEntryName)
    if widget != nil {
        return C.gtk_entry_get_visibility_wrapper((*C.GObject)(widget)) != 0
    }
    return false
}




















// ComboBoxText functions

// Append adds an item to the end of the combo box list
func (app *GTKApp) ComboBoxTextAppend(comboName, id, text string) {
    cComboName := C.CString(comboName)
    defer C.free(unsafe.Pointer(cComboName))

    cId := C.CString(id)
    defer C.free(unsafe.Pointer(cId))

    cText := C.CString(text)
    defer C.free(unsafe.Pointer(cText))

    widget := C.gtk_builder_get_object(app.builder, cComboName)
    if widget != nil {
        C.gtk_combo_box_text_append_wrapper((*C.GObject)(widget), cId, cText)
    }
}

// Prepend adds an item to the beginning of the combo box list
func (app *GTKApp) ComboBoxTextPrepend(comboName, id, text string) {
    cComboName := C.CString(comboName)
    defer C.free(unsafe.Pointer(cComboName))

    cId := C.CString(id)
    defer C.free(unsafe.Pointer(cId))

    cText := C.CString(text)
    defer C.free(unsafe.Pointer(cText))

    widget := C.gtk_builder_get_object(app.builder, cComboName)
    if widget != nil {
        C.gtk_combo_box_text_prepend_wrapper((*C.GObject)(widget), cId, cText)
    }
}

// Insert adds an item at the specified position in the combo box list
func (app *GTKApp) ComboBoxTextInsert(comboName string, position int, id, text string) {
    cComboName := C.CString(comboName)
    defer C.free(unsafe.Pointer(cComboName))

    cId := C.CString(id)
    defer C.free(unsafe.Pointer(cId))

    cText := C.CString(text)
    defer C.free(unsafe.Pointer(cText))

    widget := C.gtk_builder_get_object(app.builder, cComboName)
    if widget != nil {
        C.gtk_combo_box_text_insert_wrapper((*C.GObject)(widget), C.gint(position), cId, cText)
    }
}

// RemoveAll removes all items from the combo box
func (app *GTKApp) ComboBoxTextRemoveAll(comboName string) {
    cComboName := C.CString(comboName)
    defer C.free(unsafe.Pointer(cComboName))

    widget := C.gtk_builder_get_object(app.builder, cComboName)
    if widget != nil {
        C.gtk_combo_box_text_remove_all_wrapper((*C.GObject)(widget))
    }
}

// SetActive sets the active item in the combo box by index
func (app *GTKApp) ComboBoxSetActive(comboName string, index int) {
    cComboName := C.CString(comboName)
    defer C.free(unsafe.Pointer(cComboName))

    widget := C.gtk_builder_get_object(app.builder, cComboName)
    if widget != nil {
        C.gtk_combo_box_set_active_wrapper((*C.GObject)(widget), C.gint(index))
    }
}

// GetActive returns the index of the active item in the combo box
func (app *GTKApp) ComboBoxGetActive(comboName string) int {
    cComboName := C.CString(comboName)
    defer C.free(unsafe.Pointer(cComboName))

    widget := C.gtk_builder_get_object(app.builder, cComboName)
    if widget != nil {
        return int(C.gtk_combo_box_get_active_wrapper((*C.GObject)(widget)))
    }
    return -1
}

// GetActiveText returns the text of the currently active item
func (app *GTKApp) ComboBoxTextGetActiveText(comboName string) string {
    cComboName := C.CString(comboName)
    defer C.free(unsafe.Pointer(cComboName))

    widget := C.gtk_builder_get_object(app.builder, cComboName)
    if widget != nil {
        cText := C.gtk_combo_box_text_get_active_text_wrapper((*C.GObject)(widget))
        return C.GoString(cText)
    }
    return ""
}






























// SetSwitchActive activa un GtkSwitch
func (app *GTKApp) SetSwitchActive(switchName string) {
    cSwitchName := C.CString(switchName)
    defer C.free(unsafe.Pointer(cSwitchName))

    widget := C.gtk_builder_get_object(app.builder, cSwitchName)
    if widget != nil {
        C.gtk_switch_set_active_wrapper((*C.GObject)(widget), C.TRUE)
    }
}

// SetSwitchInactive desactiva un GtkSwitch
func (app *GTKApp) SetSwitchInactive(switchName string) {
    cSwitchName := C.CString(switchName)
    defer C.free(unsafe.Pointer(cSwitchName))

    widget := C.gtk_builder_get_object(app.builder, cSwitchName)
    if widget != nil {
        C.gtk_switch_set_active_wrapper((*C.GObject)(widget), C.FALSE)
    }
}

// GetSwitchActive obtiene el estado de un GtkSwitch
func (app *GTKApp) GetSwitchActive(switchName string) bool {
    cSwitchName := C.CString(switchName)
    defer C.free(unsafe.Pointer(cSwitchName))

    widget := C.gtk_builder_get_object(app.builder, cSwitchName)
    if widget != nil {
        return C.gtk_switch_get_active_wrapper((*C.GObject)(widget)) != 0
    }
    return false
}

// ToggleSwitch alterna el estado de un GtkSwitch
func (app *GTKApp) ToggleSwitch(switchName string) {
    if app.GetSwitchActive(switchName) {
        app.SetSwitchInactive(switchName)
    } else {
        app.SetSwitchActive(switchName)
    }
}




















// ScaleSetValue establece el valor de un GtkScale
func (app *GTKApp) ScaleSetValue(scaleName string, value float64) {
    cScaleName := C.CString(scaleName)
    defer C.free(unsafe.Pointer(cScaleName))

    widget := C.gtk_builder_get_object(app.builder, cScaleName)
    if widget != nil {
        C.gtk_scale_set_value_wrapper((*C.GObject)(widget), C.gdouble(value))
    }
}

// ScaleGetValue obtiene el valor actual de un GtkScale
func (app *GTKApp) ScaleGetValue(scaleName string) float64 {
    cScaleName := C.CString(scaleName)
    defer C.free(unsafe.Pointer(cScaleName))

    widget := C.gtk_builder_get_object(app.builder, cScaleName)
    if widget != nil {
        return float64(C.gtk_scale_get_value_wrapper((*C.GObject)(widget)))
    }
    return 0.0
}

// ScaleSetRange establece el rango mínimo y máximo de un GtkScale
func (app *GTKApp) ScaleSetRange(scaleName string, min, max float64) {
    cScaleName := C.CString(scaleName)
    defer C.free(unsafe.Pointer(cScaleName))

    widget := C.gtk_builder_get_object(app.builder, cScaleName)
    if widget != nil {
        C.gtk_scale_set_range_wrapper((*C.GObject)(widget), C.gdouble(min), C.gdouble(max))
    }
}

// ScaleSetDigits establece el número de decimales a mostrar
func (app *GTKApp) ScaleSetDigits(scaleName string, digits int) {
    cScaleName := C.CString(scaleName)
    defer C.free(unsafe.Pointer(cScaleName))

    widget := C.gtk_builder_get_object(app.builder, cScaleName)
    if widget != nil {
        C.gtk_scale_set_digits_wrapper((*C.GObject)(widget), C.gint(digits))
    }
}

// ScaleSetDrawValue controla si se muestra el valor numérico
func (app *GTKApp) ScaleSetDrawValue(scaleName string, show bool) {
    cScaleName := C.CString(scaleName)
    defer C.free(unsafe.Pointer(cScaleName))

    var cShow C.gboolean
    if show {
        cShow = C.TRUE
    } else {
        cShow = C.FALSE
    }

    widget := C.gtk_builder_get_object(app.builder, cScaleName)
    if widget != nil {
        C.gtk_scale_set_draw_value_wrapper((*C.GObject)(widget), cShow)
    }
}




// ConnectSwitchSignal conecta una señal de GtkSwitch con un callback que recibe el estado
func (app *GTKApp) ConnectSwitchSignal(switchName string, callback func(bool)) {
    cSwitchName := C.CString(switchName)
    defer C.free(unsafe.Pointer(cSwitchName))

    widget := C.gtk_builder_get_object(app.builder, cSwitchName)
    if widget == nil {
        return
    }

    // Crear un ID único para este callback
    id := fmt.Sprintf("%s::state-set", switchName)
    cId := C.CString(id)
    
    callbackMutex.Lock()
    switchCallbacks[id] = callback
    callbackMutex.Unlock()

    C.g_signal_connect_data(
        C.gpointer(widget),
        C.CString("state-set"),
        C.GCallback(C.go_switch_state_set_bridge),
        C.gpointer(unsafe.Pointer(cId)),
        C.GClosureNotify(C.free),
        0,
    )
}






















// SetTextViewText establece el texto de un GtkTextView
func (app *GTKApp) SetTextViewText(textViewName, text string) {
    cTextViewName := C.CString(textViewName)
    defer C.free(unsafe.Pointer(cTextViewName))

    cText := C.CString(text)
    defer C.free(unsafe.Pointer(cText))

    widget := C.gtk_builder_get_object(app.builder, cTextViewName)
    if widget != nil {
        C.gtk_text_view_set_text_wrapper((*C.GObject)(widget), cText)
    }
}

// GetTextViewText obtiene el texto de un GtkTextView
func (app *GTKApp) GetTextViewText(textViewName string) string {
    cTextViewName := C.CString(textViewName)
    defer C.free(unsafe.Pointer(cTextViewName))

    widget := C.gtk_builder_get_object(app.builder, cTextViewName)
    if widget != nil {
        cText := C.gtk_text_view_get_text_wrapper((*C.GObject)(widget))
        defer C.free(unsafe.Pointer(cText))
        return C.GoString(cText)
    }
    return ""
}

// SetTextViewEditable establece si un GtkTextView es editable
func (app *GTKApp) SetTextViewEditable(textViewName string, editable bool) {
    cTextViewName := C.CString(textViewName)
    defer C.free(unsafe.Pointer(cTextViewName))

    var cEditable C.gboolean
    if editable {
        cEditable = C.TRUE
    } else {
        cEditable = C.FALSE
    }

    widget := C.gtk_builder_get_object(app.builder, cTextViewName)
    if widget != nil {
        C.gtk_text_view_set_editable_wrapper((*C.GObject)(widget), cEditable)
    }
}

// GetTextViewEditable obtiene si un GtkTextView es editable
func (app *GTKApp) GetTextViewEditable(textViewName string) bool {
    cTextViewName := C.CString(textViewName)
    defer C.free(unsafe.Pointer(cTextViewName))

    widget := C.gtk_builder_get_object(app.builder, cTextViewName)
    if widget != nil {
        return C.gtk_text_view_get_editable_wrapper((*C.GObject)(widget)) != 0
    }
    return false
}

// SetTextViewWrapMode establece el modo de ajuste de texto
func (app *GTKApp) SetTextViewWrapMode(textViewName string, mode string) {
    cTextViewName := C.CString(textViewName)
    defer C.free(unsafe.Pointer(cTextViewName))

    var cMode C.GtkWrapMode
    switch mode {
    case "none":
        cMode = C.GTK_WRAP_NONE
    case "char":
        cMode = C.GTK_WRAP_CHAR
    case "word":
        cMode = C.GTK_WRAP_WORD
    case "word-char":
        cMode = C.GTK_WRAP_WORD_CHAR
    default:
        cMode = C.GTK_WRAP_WORD
    }

    widget := C.gtk_builder_get_object(app.builder, cTextViewName)
    if widget != nil {
        C.gtk_text_view_set_wrap_mode_wrapper((*C.GObject)(widget), cMode)
    }
}

// GetTextViewWrapMode obtiene el modo de ajuste de texto
func (app *GTKApp) GetTextViewWrapMode(textViewName string) string {
    cTextViewName := C.CString(textViewName)
    defer C.free(unsafe.Pointer(cTextViewName))

    widget := C.gtk_builder_get_object(app.builder, cTextViewName)
    if widget != nil {
        mode := C.gtk_text_view_get_wrap_mode_wrapper((*C.GObject)(widget))
        switch mode {
        case C.GTK_WRAP_NONE:
            return "none"
        case C.GTK_WRAP_CHAR:
            return "char"
        case C.GTK_WRAP_WORD:
            return "word"
        case C.GTK_WRAP_WORD_CHAR:
            return "word-char"
        }
    }
    return "word"
}

// SetTextViewCursorVisible establece la visibilidad del cursor
func (app *GTKApp) SetTextViewCursorVisible(textViewName string, visible bool) {
    cTextViewName := C.CString(textViewName)
    defer C.free(unsafe.Pointer(cTextViewName))

    var cVisible C.gboolean
    if visible {
        cVisible = C.TRUE
    } else {
        cVisible = C.FALSE
    }

    widget := C.gtk_builder_get_object(app.builder, cTextViewName)
    if widget != nil {
        C.gtk_text_view_set_cursor_visible_wrapper((*C.GObject)(widget), cVisible)
    }
}

// GetTextViewCursorVisible obtiene la visibilidad del cursor
func (app *GTKApp) GetTextViewCursorVisible(textViewName string) bool {
    cTextViewName := C.CString(textViewName)
    defer C.free(unsafe.Pointer(cTextViewName))

    widget := C.gtk_builder_get_object(app.builder, cTextViewName)
    if widget != nil {
        return C.gtk_text_view_get_cursor_visible_wrapper((*C.GObject)(widget)) != 0
    }
    return false
}

















































type TableData struct {
    Columns []string          `json:"columns"`
    Rows    []map[string]string `json:"rows"`
}

func (app *GTKApp) SetupTreeView(treeViewName, jsonData string) error {
    // Parse JSON data
    var data struct {
        Columns []string            `json:"columns"`
        Rows    []map[string]string `json:"rows"`
    }
    err := json.Unmarshal([]byte(jsonData), &data)
    if err != nil {
        return fmt.Errorf("error parsing JSON: %v", err)
    }

    if len(data.Columns) == 0 || len(data.Rows) == 0 {
        return fmt.Errorf("no columns or rows in data")
    }

    // Get the tree view widget
    cTreeViewName := C.CString(treeViewName)
    defer C.free(unsafe.Pointer(cTreeViewName))

    widget := C.gtk_builder_get_object(app.builder, cTreeViewName)
    if widget == nil {
        return fmt.Errorf("widget '%s' not found", treeViewName)
    }
    treeView := (*C.GtkTreeView)(unsafe.Pointer(widget))

    // Remove existing columns
    C.gtk_tree_view_remove_all_columns(treeView)

    // Create column types (all strings)
    nColumns := len(data.Columns)
    cTypes := make([]C.GType, nColumns)
    for i := range cTypes {
        cTypes[i] = C.G_TYPE_STRING
    }

    // Create list store
    store := C.gtk_list_store_new_with_columns(C.gint(nColumns), &cTypes[0])
    if store == nil {
        return fmt.Errorf("failed to create list store")
    }

    // Add data rows
    for _, row := range data.Rows {
        // Prepare row values
        cRow := make([]*C.gchar, nColumns)
        for i, col := range data.Columns {
            val := row[col]
            // Convert to valid UTF-8 and replace invalid runes
            cleanVal := strings.ToValidUTF8(val, "�")
            cRow[i] = C.CString(cleanVal)
            defer C.free(unsafe.Pointer(cRow[i]))
        }

        C.gtk_list_store_append_row(store, C.gint(nColumns), &cRow[0])
    }

    // Add columns to tree view
    for i, col := range data.Columns {
        cleanCol := strings.ToValidUTF8(col, "�")
        cCol := C.CString(cleanCol)
        defer C.free(unsafe.Pointer(cCol))
        C.gtk_tree_view_append_column_with_title(treeView, cCol, C.gint(i))
    }

    // Set the model
    C.gtk_tree_view_set_model(treeView, (*C.GtkTreeModel)(unsafe.Pointer(store)))

    // Keep the store reference
    runtime.KeepAlive(store)

    return nil
}




// GetTreeViewJSON obtiene los datos de un TreeView y los devuelve como JSON string
func (app *GTKApp) GetTreeViewJSON(treeViewName string) (string, error) {
    cTreeViewName := C.CString(treeViewName)
    defer C.free(unsafe.Pointer(cTreeViewName))

    widget := C.gtk_builder_get_object(app.builder, cTreeViewName)
    if widget == nil {
        return "", fmt.Errorf("widget '%s' not found", treeViewName)
    }
    treeView := (*C.GtkTreeView)(unsafe.Pointer(widget))

    // Obtener información del modelo
    var nColumns, nRows C.gint
    C.gtk_tree_view_get_model_info(treeView, &nColumns, &nRows)
    
    if nColumns == 0 || nRows == 0 {
        return "", fmt.Errorf("tree view has no data")
    }

    // Obtener nombres de columnas
    columns := make([]string, nColumns)
    for i := 0; i < int(nColumns); i++ {
        // Obtener la columna del TreeView
        treeColumn := C.gtk_tree_view_get_column(treeView, C.gint(i))
        if treeColumn == nil {
            columns[i] = fmt.Sprintf("Column %d", i+1)
            continue
        }
        
        // Obtener el título de la columna
        cTitle := C.gtk_tree_view_column_get_title(treeColumn)
        if cTitle != nil {
            columns[i] = C.GoString(cTitle)
        } else {
            columns[i] = fmt.Sprintf("Column %d", i+1)
        }
    }

    // Obtener datos de las filas
    rows := make([]map[string]string, nRows)
    for row := 0; row < int(nRows); row++ {
        rowData := make(map[string]string)
        for col := 0; col < int(nColumns); col++ {
            cValue := C.gtk_tree_view_get_cell_value(treeView, C.gint(row), C.gint(col))
            if cValue != nil {
                rowData[columns[col]] = C.GoString(cValue)
                C.g_free(C.gpointer(cValue))
            } else {
                rowData[columns[col]] = ""
            }
        }
        rows[row] = rowData
    }

    // Crear estructura TableData y convertir a JSON
    data := TableData{
        Columns: columns,
        Rows:    rows,
    }

    jsonData, err := json.Marshal(data)
    if err != nil {
        return "", fmt.Errorf("error marshaling to JSON: %v", err)
    }

    return string(jsonData), nil
}


























// ... (código existente)

// SetColumnEditable hace editable una columna específica del TreeView
func (app *GTKApp) SetColumnEditable(treeViewName string, columnIndex int, editable bool) {
    cTreeViewName := C.CString(treeViewName)
    defer C.free(unsafe.Pointer(cTreeViewName))

    widget := C.gtk_builder_get_object(app.builder, cTreeViewName)
    if widget == nil {
        return
    }
    treeView := (*C.GtkTreeView)(unsafe.Pointer(widget))

    C.gtk_tree_view_set_column_editable(treeView, C.gint(columnIndex), C.gboolean(boolToGboolean(editable)))
}


func (app *GTKApp) ConnectEditedSignal(treeViewName string, columnIndex int, callback func(row, col int, newValue string)) {
    cTreeViewName := C.CString(treeViewName)
    defer C.free(unsafe.Pointer(cTreeViewName))

    widget := C.gtk_builder_get_object(app.builder, cTreeViewName)
    if widget == nil {
        return
    }
    treeView := (*C.GtkTreeView)(unsafe.Pointer(widget))

    // ID más simple que incluye solo el nombre del treeview
    id := treeViewName
    cId := C.CString(id)
    defer C.free(unsafe.Pointer(cId))

    callbackMutex.Lock()
    // Almacenamos el índice de columna en el callback
    editedCallbacks[id] = func(row, _ int, newValue string) {
        callback(row, columnIndex, newValue)
    }
    callbackMutex.Unlock()

    C.gtk_tree_view_connect_edited_signal(treeView, C.gint(columnIndex), cId)
}

// SetCellValue actualiza el valor de una celda específica
func (app *GTKApp) SetCellValue(treeViewName string, row, column int, value string) {
    cTreeViewName := C.CString(treeViewName)
    defer C.free(unsafe.Pointer(cTreeViewName))

    widget := C.gtk_builder_get_object(app.builder, cTreeViewName)
    if widget == nil {
        return
    }
    treeView := (*C.GtkTreeView)(unsafe.Pointer(widget))

    cValue := C.CString(value)
    defer C.free(unsafe.Pointer(cValue))

    C.gtk_tree_view_set_cell_value(treeView, C.gint(row), C.gint(column), cValue)
}

// Helper function to convert Go bool to C gboolean
func boolToGboolean(b bool) C.gboolean {
    if b {
        return C.gboolean(1)
    }
    return C.gboolean(0)
}