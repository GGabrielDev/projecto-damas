# Proyecto Damas 🎮

Projecto para clase de Estructura de Datos I

## Requisitos

- CMake ≥ 3.10
- Compilador C++17 (g++/Clang en Linux, MSVC en Windows)

## Compilar y Ejecutar

### Linux/macOS

```bash
# Configurar y compilar
mkdir build && cd build
cmake .. && make

# Ejecutar programa principal
./bin/projecto-damas

# Ejecutar todas las pruebas
ctest --output-on-failure

# Ejecutar pruebas específicas
./bin/tests/TestBoard
```

### Windows

Abrir CMake GUI:

Source dir: Ruta/al/projecto-damas

Build dir: Ruta/al/projecto-damas/build

Configurar y Generar (usar generador de Visual Studio)

Abrir .sln en Visual Studio

Compilar solución (F7)

Ejecutar desde línea de comandos:

```cmd
# Programa principal
cd build\bin\Debug
projecto-damas.exe

# Todas las pruebas
cd build
ctest --output-on-failure -C Debug

# Prueba específica
cd bin\tests\Debug
TestBoard.exe
```

## Estructura de directorios

projecto-damas/
├── include/ # Headers
├── src/ # Código fuente
├── tests/ # Pruebas unitarias
└── build/ # Directorio de compilación
