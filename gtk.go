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
*/
import "C"
import (
	"errors"
	"sync"
	"unsafe"
)

var (
	callbackMutex   sync.Mutex
	callbackCounter uintptr
	callbacks       = make(map[uintptr]func())
)

//export goCallbackProxy
func goCallbackProxy(data unsafe.Pointer) {
	id := uintptr(data)
	callbackMutex.Lock()
	cb, ok := callbacks[id]
	callbackMutex.Unlock()
	if ok {
		cb()
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

	cFilename := C.CString(filename)
	defer C.free(unsafe.Pointer(cFilename))

	if C.gtk_builder_add_from_file(app.builder, cFilename, nil) == 0 {
		C.g_object_unref(C.gpointer(unsafe.Pointer(app.builder)))
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
	callbackMutex.Lock()
	callbackCounter++
	id := callbackCounter
	callbacks[id] = callback
	callbackMutex.Unlock()

	C.g_signal_connect_data(
		C.gpointer(widget),
		cSignal,
		C.GCallback(C.go_callback_bridge),
		C.gpointer(unsafe.Pointer(id)),
		nil,
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
	callbacks = make(map[uintptr]func())
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