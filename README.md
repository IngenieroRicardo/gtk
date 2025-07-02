### 🛠️ Compilar

| BSD/Linux | MXE |
| --- | --- |
| `go build -o main.bin main.go` | `git clone https://github.com/mxe/mxe.git` |
|  | `cd mxe` |
|  | `make gtk3 -j 8 MXE_TARGETS='x86_64-w64-mingw32.static'` |
|  | `cd ..` |
|  | `GO_LDFLAGS="-luuid" PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1 PKG_CONFIG_ALLOW_SYSTEM_LIBS=1 GOOS=windows GOARCH=amd64 CGO_ENABLED=1 CXX=$PWD/mxe/usr/bin/x86_64-w64-mingw32.static-g++ CC=$PWD/mxe/usr/bin/x86_64-w64-mingw32.static-gcc PKG_CONFIG=$PWD/mxe/usr/bin/x86_64-w64-mingw32.static-pkg-config go build -o main.exe main.go` |
