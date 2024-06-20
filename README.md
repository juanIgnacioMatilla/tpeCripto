
# Trabajo práctico de implementación sobre estenografía 

Este proyecto implementa un programa stegobmp en lenguaje C que efectúa las siguientes operaciones:

- Oculta un archivo cualquiera en un archivo de extensión “.bmp”, mediante un método de
esteganografiado elegido, con o sin password.
- Descubre un archivo oculto en un archivo de extensión “.bmp” que haya sido previamente
esteganografiado con uno de los métodos provistos.
- Estegoanaliza un archivo de extensión “.bmp” para determinar si tiene un archivo
incrustado y lo extrae correctamente.

## Requisitos

- `make`: Asegúrate de tener `make` instalado en tu sistema.

## Compilación

Para compilar el proyecto, ejecuta el siguiente comando:

```bash
make all
```

## Ejecución

Una vez compilado, puedes ejecutar el programa `stegobmp` con las siguientes configuraciones:

```bash
./stegobmp -MODE [-in filename] -p filename -out filename -steg <LSB1|LSB4|LSBI> [-a <aes128|aes192|aes256|des>] [-m <ecb|cfb|ofb|cbc>] [-pass password] [-help]
```


### Opciones:

Los parámetros admitidos por el programa son los siguientes:
| Comandos |  Descripcion | 
|----| ------------------ |
| -in filename                      | Archivo que se va a ocultar. |
| -p filename                       | Archivo bmp que será el portador. |
| -out filename                     | Archivo de salida obtenido. |
| -steg <LSB1\|LSB4\|LSBI>          | Algoritmo de esteganografiado: LSB de 1 bit, LSB de 4 bits, LSB Improved. |
| -a <aes128\|aes192\|aes256\|des>  | Algoritmo de encripción: aes128, aes192, aes256, des. Se asume aes128 por default. |
| -m <ecb\|cfb\|ofb\|cbc>           | Modo de encripción: ecb, cfb, ofb, cbc. Se asume CBC por default. |
| -pass password                    | Contraseña de encripción. Si no se pasa este parámetro sólo se esteganografía. |
| -help                             | Imprime el manual de uso del programa. |

| Modos |  Descripcion | 
|----| ------------------ |
| -embed    | Indica que se va a ocultar información. |
| -extract  | Indica que se va a extrar información. |

### Ejemplos:

1. Para ocultar un mensaje:

    ```bash
    ./stegobmp -embed -in ./ejemploInforme/itba.png -p ./ejemploInforme/example_for_report.bmp -out ./ejemploInforme/output_lsbi.p
ng -steg LSBI
    ```

2. Para extraer un mensaje:

    ```bash
    ./stegobmp -extract -p ./ejemplo2024/ladoLSBIdescfb.bmp -out ./salida.png -a des -m cfb -pass margarita -steg LSBI
    ```

## Limpieza

Para limpiar todos los archivos generados durante la compilación, ejecuta:

```bash
make clean
```

Este comando eliminará todos los archivos objetos y el ejecutable generado.

## Autores

- [Matilla Juan Ignacio](https://github.com/juanIgnacioMatilla)
- [Escudeiro Patricio](https://github.com/pescudeiro)

