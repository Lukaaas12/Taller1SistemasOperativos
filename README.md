# Taller 1: Shell Simple en Linux

[cite_start]Este repositorio contiene la implementación de un intérprete de comandos básico en lenguaje C para la asignatura **Sistemas Operativos**[cite: 2, 76].

## 👥 Integrantes
* [cite_start]Felipe Zuñiga [cite: 63]
* [cite_start]Lukas Alvarado [cite: 63]
* [cite_start]Gustavo Fernandez [cite: 63]

## 🛠️ Arquitectura y Syscalls Utilizadas
[cite_start]El programa funciona bajo un ciclo REPL [cite: 87] y mapea los requerimientos mediante las siguientes llamadas al sistema:
* [cite_start]**Prompt:** Imprime `mi_shell>` y vacía el buffer[cite: 17, 87, 93]. [cite_start]Internamente interactúa con la syscall `write()`[cite: 93].
* [cite_start]**Lectura y Parseo:** Usa `getline()` (asociada a `read()`) y procesa argumentos de forma dinámica con `strtok()` y `realloc()`[cite: 19, 83, 96, 97].
* [cite_start]**Comando exit:** Detecta la palabra con `strcmp()`, libera memoria y finaliza usando la syscall `_exit()`[cite: 21, 100, 101].
* [cite_start]**Manejo de Errores:** Si el comando no existe, `execvp()` retorna `-1`[cite: 104]. [cite_start]Se despliega el error con `perror()` sin cerrar la shell[cite: 105].
* [cite_start]**Líneas Vacías:** Si se presiona Enter, se valida con `strcmp()` y un `continue` evita bifurcar procesos en el Kernel[cite: 24, 25].
* [cite_start]**Ejecución Concurrente:** Crea un proceso hijo con `fork()`, reemplaza su imagen con `execvp()` y el padre espera en foreground usando `waitpid()`[cite: 26, 27, 89].

## 🚀 Compilación y Ejecución (Google Cloud Shell)

### 1. Compilación
[cite_start]Ejecute el siguiente comando en la terminal para compilar el archivo fuente[cite: 14, 90]:
```bash
gcc -Wall -Wextra -o mi_shell src/mi_shell.c
