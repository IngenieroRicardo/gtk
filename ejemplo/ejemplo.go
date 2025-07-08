package main

import (
	"fmt"
	"os"
	"strconv"
	gui "github.com/IngenieroRicardo/gtk" 
)

func main() {
	/* Construimos la GUI de la APP */
	app := gui.NewGTKApp()
	defer app.Cleanup()
	err := app.LoadUI("./ejemplo.ui")
	if err != nil {
		fmt.Println("Error:", err)
		os.Exit(1)
	}
	window := app.GetWindow("window_main")
	app.ConnectSignalDirect("window_main", "destroy", 0, nil)


	/* GtkCheckMenuItem y GtkStatusbar */
	app.ConnectSignal(
	    "checkmenuitem_option",
	    "toggled",
	    func() {
	        if app.GetCheckMenuItemStatus("checkmenuitem_option") {
	            app.SetStatusBar("statusbar_main", "Opción de menú ACTIVADA")
	        } else {
	        	app.SetStatusBar("statusbar_main", "Opción de menú DESACTIVADA")
	        }
	    },
	)


	/* GtkMenuItem */
	app.ConnectSignal(
	    "menuitem_exit",
	    "activate",
	    func() {
	        app.Quit()
	    },
	)
	

	/* GtkEntry y GtkCheckButton */
	app.SetEntryVisibility("entry_pass", false)
	app.ConnectSignal(
		"checkbutton_active",
		"clicked",
		func() {
			if app.GetToggleButtonStatus("checkbutton_active") {
	    		app.SetEntryVisibility("entry_pass", true)
			} else {
				app.SetEntryVisibility("entry_pass", false)
			}
		},
	)


	/* GtkButton y GtkApplicationWindow */
	app.ConnectSignal(
		"button_saludar",
		"clicked",
		func() {
			app.SetLabelText("dialog1_nombre", app.GetEntryText("entry_name"))
			app.SetLabelText("dialog1_pass", app.GetEntryText("entry_pass"))
			app.ShowDialog("dialog1")
		},
	)
	app.ConnectSignal(
		"dialog1_ok",
		"clicked",
		func() {
			app.HideDialog("dialog1")
		},
	)


	/* GtkToggleButton y GtkStatusbar */
	app.SetToggleButtonActive("toggle_activar")
	app.ConnectSignal(
		"toggle_activar",
		"clicked",
		func() {
			if app.GetToggleButtonStatus("toggle_activar") {
	    		app.SetStatusBar("statusbar_main", "El boton está activado")

			} else {
				app.SetStatusBar("statusbar_main", "El boton está inactivado")
			}
		},
	)


	/* GtkSwitch y GtkSpinner */
	app.SetSwitchActive("switch_notifications")
	app.ConnectSwitchSignal("switch_notifications", func(active bool) {
	        if active {
        	    app.StartSpinner("spinner_main")
        	} else {
            	app.StopSpinner("spinner_main")
        	}
    	})


    /* GtkScale y GtkProgressBar */
	app.SetProgressBarValue("progressbar_main", 0.2)
	app.SetProgressBarDrawValue("progressbar_main", true)

	app.SetScaleRange("scale_volume", 0.0, 1.0)
	app.SetScaleDrawValue("scale_volume", true)
	app.SetScaleValue("scale_volume", 0.95)
	app.ConnectSignal("scale_volume", "value-changed", func() {
	    volume := app.GetScaleValue("scale_volume")
	    app.SetProgressBarValue("progressbar_main", volume)
	    //fmt.Println(app.GetProgressBarValue("progressbar_main"))
	})


	/* GtkComboBoxText y GtkImage */
	app.ComboBoxTextAppend("combobox_country", "SLV", "El Salvador")
	app.SetImageFromFile("image_logo", "./sv.png")

	app.ComboBoxTextSetSelected("combobox_country", 3)
	app.ConnectSignal(
	    "combobox_country",
	    "changed",
	    func() {
	        //activeIndex := app.ComboBoxTextGetSelected("combobox_country")
	        activeText := app.ComboBoxTextGetSelectedText("combobox_country")
	        //fmt.Printf("Combo cambió: Índice %d, Texto: %s\n", activeIndex, activeText)
	        if activeText == "Guatemala" {
	        	app.ImageCleanup("image_logo")
	        	app.SetImageFromFile("image_logo", "./gt.png")
	        } else if activeText == "Honduras" {
	        	app.ImageCleanup("image_logo")
	        	app.SetImageFromFile("image_logo", "./ho.png")
	        } else if activeText == "Mexico" {
	        	app.ImageCleanup("image_logo")
	        	app.SetImageFromFile("image_logo", "./mx.png")
	        } else {
	        	app.ImageCleanup("image_logo")
	        	app.SetImageFromFile("image_logo", "./sv.png")
	        }
	    },
	)


	/* GtkRadioButton y GtkStatusbar */
	app.SetRadioButtonActive("radio_btn1")
	app.ConnectSignal(
	    "radio_btn1",
	    "toggled",
	    func() {
	        if app.GetRadioButtonActive("radio_btn1") {
	        	app.SetStatusBar("statusbar_main", "Opción 1 seleccionada (Masculino)")
	        }
	    },
	)
	app.ConnectSignal(
	    "radio_btn2",
	    "toggled",
	    func() {
	        if app.GetRadioButtonActive("radio_btn2") {
	        	app.SetStatusBar("statusbar_main", "Opción 2 seleccionada (Femenino)")
	        }
	    },
	)
	app.ConnectSignal(
	    "radio_btn3",
	    "toggled",
	    func() {
	        if app.GetRadioButtonActive("radio_btn3") {
	            app.SetStatusBar("statusbar_main", "Opción 3 seleccionada (Otro)")
	        }
	    },
	)
	

	/* GtkFileChooserDialog y GtkTextView y GtkToolButton */
	app.ConnectSignal(
		"button_abrir",
		"clicked",
		func() {
			app.ShowDialog("dialog2")
		},
	)
	app.ConnectSignal(
		"btn_cancel",
		"clicked",
		func() {
			app.HideDialog("dialog2")
		},
	)
	app.ConnectSignal(
		"btn_accept",
		"clicked",
		func() {
			app.SetTextViewText("textview_main", app.GetSelectedFilePath("dialog2") + "\n" + app.GetTextViewText("textview_main"))
		    app.HideDialog("dialog2")
		},
	)


	/* GtkTreeView y GtkStatusbar y GtkToolButton */
	jsonData := `{
	    "columns": ["Name", "Value", "Active"],
	    "rows": [
	        {"Name": "textview_main", "Value": "Tiene datos multilinea", "Active": "true"},
	        {"Name": "entry_pass", "Value": "Tiene contraseña", "Active": "false"}
	    ]
	}`
	erro := app.SetupTreeView("treeview_main", jsonData)
	if erro != nil {
	    fmt.Println("Error setting up tree view:", erro)
	}
	app.SetColumnTreeViewEditable("treeview_main", 0, true)
	app.SetColumnTreeViewEditable("treeview_main", 1, true)
	app.SetColumnTreeViewEditable("treeview_main", 2, true)

	app.ConnectSignal(
		"button_agregar",
		"clicked",
		func() {
			app.AddRowTreeView("treeview_main")
			app.SetStatusBar("statusbar_main", "Se agrego una fila en la tabla")
		},
	)
	app.ConnectSignal(
		"button_eliminar",
		"clicked",
		func() {
			app.RemoveSelectedRowTreeView("treeview_main")
			app.SetStatusBar("statusbar_main", "Se elimino una fila en la tabla")
		},
	)
	app.ConnectSignal(
		"button_limpiar",
		"clicked",
		func() {
			app.ShowPopover("popover_limpiar")
			
		},
	)
	app.ConnectSignal(
		"popover_btn_confirmar",
		"clicked",
		func() {
			app.CleanTreeView("treeview_main")

			//Agregar Filas mediante un JSON:
			/*jsonRows := `[
			    {"Name": "nuevo_item", "Value": "valor_ejemplo", "Active": "true"},
			    {"Name": "otro_item", "Value": "otro_valor", "Active": "false"}
			]`
			err := app.AppendRowsTreeViewJSON("treeview_main", jsonRows)
			if err != nil {
			    fmt.Println("Error:", err)
			}*/
			app.HidePopover("popover_limpiar")
			app.SetStatusBar("statusbar_main", "Se limpio la tabla")
		},
	)
	
	app.ConnectTreeViewSignal("treeview_main", func(row, col int, newValue string) {
		rowStr, err := app.GetRowTreeViewJSON("treeview_main", row)
	    if err != nil {
	        app.SetStatusBar("statusbar_main", "Celda editada: fila="+strconv.Itoa(row)+", col="+strconv.Itoa(col)+", nuevo valor="+newValue)
	    } else {
	        app.SetStatusBar("statusbar_main", "Fila: "+rowStr+" Celda editada: fila="+strconv.Itoa(row)+", col="+strconv.Itoa(col)+", nuevo valor="+newValue)
	    }
	})
	
	
	/* Ejecutar la GUI de la APP sin cerrar hasta que se destruya */
	app.Run(window)
}

