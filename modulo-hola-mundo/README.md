## Requisitos

    - Archivo miModulo.c
    - Archivo Makefile
    

## Compilación e instalación de un módulo del kernel en Linux

### Paso 1: Compilación del módulo del kernel

```bash
$ make
```

### Paso 2: Carga del módulo en el kernel

```bash
$ sudo insmod miModulo.ko
```

### Paso 3: Verificación de la carga del módulo
```bash
$ dmesg

```
Mensaje esperado:

```bash
UNGS : Driver registrado
```

### Paso 4: Desregistrar nuestro modulo de kernel recientemente creado
```bash
$ sudo rmmod miModulo
```

### Paso 5: Verificación desregistrado del modulo
```bash
$ dmesg
```

Mensaje esperado:
```bash
UNGS : Driver desregistrado
```

### Paso 6: Limpieza del directorio de trabajo
```bash
$ make clean
```
