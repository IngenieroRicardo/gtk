# Go-GTK Wrapper

Enlace: https://github.com/IngenieroRicardo/gtk

Este proyecto proporciona un **binding personalizado** entre Go y GTK+ 3 usando `cgo`, facilitando la creación de interfaces gráficas (GUIs) en Go. Ideal para desarrollar aplicaciones nativas multiplataforma.

---

## 📦 Instalación

### Requisitos

- **Go** ≥ 1.24.1  
- **GTK+ 3** y herramientas asociadas (`pkg-config`, compiladores C/C++)
- Sistema compatible con `cgo`

#### Debian / Ubuntu y derivados

```bash
sudo apt update
sudo apt install -y glade pkgconf gcc libgtk-3-dev
```

#### FreeBSD / GhostBSD

```bash
sudo pkg install -g 'GhostBSD*-dev'
sudo pkg install pkgconf gcc gtk3
```

#### macOS (Homebrew)

```bash
brew install gtk+3 pkg-config
```

#### MXE (compilación cruzada a Windows)

```bash
git clone https://github.com/IngenieroRicardo/mxe.git
cd mxe
make gtk3 -j 8 MXE_TARGETS='x86_64-w64-mingw32.static'
cd ..
find $PWD/mxe/usr/x86_64-w64-mingw32.static/lib/pkgconfig -name '*.pc'   -exec sed -i 's/-Wl,//g' {} \;
GO_LDFLAGS="-luuid" PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1 PKG_CONFIG_ALLOW_SYSTEM_LIBS=1 GOOS=windows GOARCH=amd64 CGO_ENABLED=1 CXX=$PWD/mxe/usr/bin/x86_64-w64-mingw32.static-g++ CC=$PWD/mxe/usr/bin/x86_64-w64-mingw32.static-gcc PKG_CONFIG=$PWD/mxe/usr/bin/x86_64-w64-mingw32.static-pkg-config go build -o main.exe main.go

```

---

## ⚙️ Compilación

Para compilar la aplicación principal en sistemas Unix (Linux, macOS, FreeBSD):

```bash
cd ejemplo
go build ejemplo.go
```

Después de instalar dependencias, esto generará un ejecutable listo para usar.

---

## 🛠️ Funcionalidades principales

- **Widgets GTK soportados**: Entry, Label, Button, ToggleButton, ComboBoxText, Switch, Scale, TextView, TreeView (editable/dinámico), FileChooser, Image, Spinner, Statusbar, Popover...
- Eventos y señales conectables desde Go.
- Manipulación de propiedades: visibilidad, sensibilidad, texto, estado activo, selección, etc.
- Gestión de `GtkTreeView` editable con exportación de datos a JSON.
- Wrapper en C (`gtk.c`) e integración `cgo` (`gtk.go`) con manejo seguro de callbacks usando `sync.Mutex`.
- Utilidades adicionales: descarga y extracción ZIP, corrección de rutas y dependencias en Windows.

---

## 📁 Estructura del proyecto

| Archivo       | Descripción |
|---------------|-------------|
| `gtk.go`      | Wrappers en Go para GTK+ 3, conversión de tipos y lógica de callbacks |
| `gtk.c`       | Envoltorios en C que usan la API de GTK para exponerla a Go |
| `ejemplo/ejemplo.go`     | Ejemplo de uso e inicialización de la interfaz gráfica |

---

## 🔧 Contribuir

- Abre *Issues* para reportar bugs o sugerir nuevas funciones.
- Haz *Fork*, desarrolla nuevas características y envía *Pull Requests*.
- Porfavor sigue buenas prácticas de Go y agrega tests si es posible.

---

## 📜 Licencia

Distribuido bajo la **MIT License**. Consulta el archivo `LICENSE` para más detalles.

---

## ¿Qué sigue?

- Traducir al inglés para audiencia internacional.
- Documentar con `pkg.go.dev` y ejemplos más completos.
- Ampliar soporte para más widgets y señales.

---
