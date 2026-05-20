# Taller 1: Shell Simple en Linux

Este repositorio contiene la implementación de un intérprete de comandos básico en lenguaje C para el Taller 1 de **Sistemas Operativos**.

##  Integrantes
* Felipe Zuñiga
* Lukas Alvarado
* Gustavo Fernandez

##  Arquitectura y Syscalls Utilizadas
El programa funciona bajo un ciclo REPL y mapea los requerimientos mediante las siguientes llamadas al sistema:
* **Prompt:** Imprime `mi_shell>` y vacía el buffer. Internamente interactúa con la syscall `write()`.
* **Lectura y Parseo:** Usa `getline()` (asociada a `read()`) y procesa argumentos de forma dinámica con `strtok()` y `realloc()`.
* **Comando exit:** Detecta la palabra con `strcmp()`, libera memoria y finaliza usando la syscall `_exit()`.
* **Manejo de Errores:** Si el comando no existe, `execvp()` retorna `-1`. Se despliega el error con `perror()` sin cerrar la shell.
* **Líneas Vacías:** Si se presiona Enter, se valida con `strcmp()` y un `continue` evita bifurcar procesos en el Kernel.
* **Ejecución Concurrente:** Crea un proceso hijo con `fork()`, reemplaza su imagen con `execvp()` y el padre espera en foreground usando `waitpid()`.

##  Compilación y Ejecución (Google Cloud Shell)

### 1. Compilación
Ejecute el siguiente comando en la terminal para compilar el archivo fuente:
```bash
gcc -Wall -Wextra -o mi_shell src/mi_shell.c
```
### 2. Ejecución
Para iniciar la shell, ejecute:

```bash
./mi_shell
```
### 3. Comandos de prueba

```bash
ls -la /tmp
```
```bash
comando_falso_test
```
```bash
exit
```
