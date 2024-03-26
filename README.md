# Trabajo Práctico - Char Device 
# Materia: Sistemas Operativos y Redes 2. 

En este trabajo se verán conceptos sobre cómo implementar un char device desde lo más básico hasta la implementación de funcionalidades adicionales más complejas.
--- 
Implementación de 3 módulos:
  - Modulo hola mundo.
  - Modulo Char Device (permite escribir y retonar lo último que fue escrito en el device).
  - Modulo Reverse Char Device (permite escribir y retonar lo último que fue escrito en el device pero al reves).


## Compilación e instalación de un módulo del kernel en Linux


## Requisitos

    - Archivo <nombre_modulo>.c
    - Archivo Makefile
    - Estar situado en un directorio que contenga ambos archivos.
    

### Paso 1: Compilación del módulo del kernel

```bash
$ make
```

### Paso 2: Carga del módulo en el kernel

```bash
$ sudo insmod <nombre_modulo>.ko
```

### Paso 3: Verificación de la carga del módulo
```bash
$ dmesg   // con este comando podremos ver los logs del kernel
```
Chequear que el log del kernel registre que el driver se cargo correctamente

### Paso 4: Desregistrar nuestro modulo de kernel recientemente creado
```bash
$ sudo rmmod miModulo
```

### Paso 5: Verificación desregistrado del modulo
```bash
$ dmesg
```

Chequear que el log del kernel registre que el driver se cargo correctamente

### Paso 6: Limpieza del directorio de trabajo
```bash
$ make clean
```

## Escritura y Lectura del dispositivo

## Requisitos
    - Haber cargado el modulo del device
    
### Crear un nodo de nuestro device de caracteres.

```bash
$ mknod /dev/chardevice c <mayor_number> <minor_number>
```

### Otorgar permisos de lectura y escritura
```bash
$ chmod 777 /dev/chardevice
```

### Escribir en el dispositivo.
```bash
 $ echo "texto de prueba" > /dev/chardevice
```

### Leer el dispositivo
```bash
 $ cat /dev/chardevice
```


