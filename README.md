## Reproductor (Proyecto de Programación Estructurada)

Descripción
---------
Este proyecto contiene un reproductor simple (escrito en C) llamado `Reproductor.c` que utiliza un archivo de texto `Biblioteca.txt` como catálogo o lista de recursos. El repositorio incluye el código fuente y el archivo de datos necesario para probar el programa.

Estructura de archivos
----------------------
- `Reproductor.c`  : Código fuente en C del reproductor.
- `Biblioteca.txt`  : Archivo de texto que contiene la lista de items (por ejemplo, canciones). Formato esperado: una entrada por línea.

Requisitos
----------
- Windows con compilador de Visual C (cl.exe) disponible en PATH. Generalmente es más sencillo compilar desde el "Developer Command Prompt for VS".
- Alternativamente, usar la tarea de VS Code incluida para compilar el archivo activo (ver abajo).

Cómo compilar
-------------
1) Usando la tarea de VS Code (recomendado si ya está configurado):

   - En VS Code: menú `Terminal` → `Run Task...` → seleccionar `C/C++: cl.exe build active file`.

2) Desde PowerShell con `cl.exe` (asegúrate de ejecutar desde el Developer Command Prompt o tener `cl.exe` en PATH):

```powershell
cl.exe /Zi /EHsc /nologo /Fe:"Reproductor.exe" "Reproductor.c"
```

Cómo ejecutar
-------------
Después de compilar, ejecuta el binario generado en la misma carpeta:

```powershell
.
\Reproductor.exe
# o
.\Reproductor.exe
```

Notas sobre `Biblioteca.txt`
---------------------------
- El programa lee `Biblioteca.txt` para obtener la lista de recursos.
- Suposición razonable: cada línea corresponde a un registro (por ejemplo: Título - Artista - Ruta). Si tu `Reproductor.c` espera otro formato, ajusta `Biblioteca.txt` en consecuencia.
- Si quieres probar rápidamente, crea una `Biblioteca.txt` con contenido de ejemplo, por ejemplo:

```
Canción A - Autor A - C:\Music\cancionA.mp3
Canción B - Autor B - C:\Music\cancionB.mp3
```

Consejos y solución de problemas
--------------------------------
- Si al ejecutar `cl.exe` obtienes error "command not found", abre el "Developer Command Prompt for VS" o ejecuta el script de entorno (por ejemplo, `vcvarsall.bat`) para agregar las herramientas a PATH.
- Si el programa no encuentra `Biblioteca.txt`, confirma que el archivo está en la misma carpeta que `Reproductor.exe` o proporciona la ruta correcta al programa (según cómo esté implementado en `Reproductor.c`).

Contribuciones
--------------
- Pull requests y mejoras son bienvenidas. Para cambios en el código fuente, añade comentarios claros y actualiza este README si cambias el comportamiento esperado o el formato de `Biblioteca.txt`.
