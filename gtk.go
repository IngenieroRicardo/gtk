package gtk

/*
#cgo pkg-config: gtk+-3.0
#include <gtk/gtk.h>
#include <stdlib.h>

// Solo declaración (no definición)
extern void goCallbackProxy(gpointer data);

// Declaración de la función puente (definición en otro archivo)
extern void go_callback_bridge(GtkWidget *widget, gpointer data);
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
