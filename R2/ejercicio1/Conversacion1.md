# Resolver problema BF en Python

> Resuelve este problema de concurso de programación.
>
> PROBLEMA:
> Problema BF
> Una cadena de tiendas entrega su registro de ventas: hasta 3 millones de líneas
> fecha,id_venta,producto_id,cantidad, con fecha en formato AAAA-MM-DD, id_venta de 1 a 4 000 000,
> producto_id de 1 a 100 000 y cantidad entera (las devoluciones son negativas). Debes reportar los 3 productos
> con mayor venta neta entre las fechas D1 y D2 (inclusive).
> El registro tiene líneas inválidas (se ignoran) y ventas repetidas (mismo id_venta, que deben contar una sola vez).
> Lo que debes descubrir con la caja negra: qué hace inválida una línea, cuál de las ventas repetidas es la que
> cuenta, y qué productos se reportan.
> Entrada: línea 1 D1 D2. Línea 2 N. Luego N líneas.
> Salida: hasta 3 líneas producto_id total, de mayor a menor total (empate: menor producto_id). Si no hay nada
> que reportar: SIN DATOS.
> Límites: N  3 000 000  90 MB de texto).
> Tiempo / memoria: 16 s / 64 MB.
> Ejemplo 1
> Entrada:
> 2028-02-25 2028-03-03
> 8
> 2028-02-27,4,3,5
> 2028-02-27,4,4,1,1
> 2028-03-01,6,1,9
> 2028-02-26,6,2,-2
> 2028-03-01,1,2,5
> 2028-03-03,9,4,5
> 2028-02-26,9,3,5
> 2028-02-23,4,4,8
> Salida:
> 1 9
> 2 5
> 3 5
>
> Ejemplo 2
> Entrada:
> 2026-03-01 2026-03-31
> 11
> 2026-03-29,6,4,5
> 2026-03-07,1,4,8
> 2026-03-25,5,1,4
> 2026-03-19,3,0,1
> 2026-03-29,6,4,5
> 2026-03-13,6,2,-5
> 2026-03-17,5,3,4
> 2000-02-29,3,3,-2
> 2026-03-17,5,3,4
> 2026-04-02,6,3,
> Salida:
> 4 13
> 1 4
>
> ENTORNO:
> - Windows, Java 21, codigo C
> - Entrada por entrada estándar y salida por salida estándar.
> - Límites de tiempo y memoria: 16 segundos de tiempo y memoria de 64MB
>
> Seran aproximadamente 90MB de texto que se pondran aprueba asi que usa manera eficiente que python pueda utilizar los 64Mb de RAM para leer los 90MB de manera justa en la memoria
> REQUISITOS DEL CÓDIGO:
> - Lectura rápida y/o lectura de bytes,
>   tolerante a espacios extra, saltos de línea CRLF y a que no haya salto
>   final.
> - Una sola impresión al final.
> - Sin modo debug, sin código extra o modos incesearios que alenten el codigo.
> - Un solo archivo.
>
> FORMATO DE LA RESPUESTA (en este orden y breve):
> 1. Cómo interpretas el problema en 2 o 3 líneas. Si algo del enunciado es
>    ambiguo, dilo y di qué suposición tomaste.
> 2. Algoritmo y estructura de datos elegidos, y por qué son adecuados para
>    estos límites.
> 3. Complejidad de tiempo y espacio, y por qué cabe en los límites.
> 4. El código completo en un solo bloque.
> 5. Traza a mano de los ejemplos del enunciado con tu código.
> 6. Entre 5 y 8 casos borde, cada uno con su entrada y su salida esperada
>    listas para copiar y pegar.
> Los datos son masivos y la memoria limitada utiliza las mejores funcionalidades de C par amanejar la memoria limitada a bajo nivel de ser necesario
> Si algo del problema es ambiguo mencionalo y menciona la solucion a la que llegaste
> Tengo acceso a la caja negro para pruebas esta en C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF

<details><summary>9 previous messages</summary>

> Voy a revisar la caja negra y probar las reglas ambiguas antes de preparar el código C y los casos de prueba.
>
> <details><summary>Ran 4 commands</summary>
>
> - Ran `Get-ChildItem -LiteralPath 'C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF' -Force | Select-Object Name,Length,Mode; Get-Location`
> - Ran `Get-Content -LiteralPath 'C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\enunciado.md'; Get-Content -LiteralPath 'C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\ejemplo2.in'; Get-Command python, gcc, clang, clang-cl, cl -ErrorAction SilentlyContinue | Select-Object Name,Source; Get-Content -Raw -LiteralPath 'C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\ejemplo1.in' | & 'C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'`
> - Ran `python --version; Get-Command wsl, zig, tcc -ErrorAction SilentlyContinue | Select-Object Name,Source; Get-ChildItem -LiteralPath 'C:\' -Directory | Select-Object Name; rg --files -g AGENTS.md -g '*gcc*.exe' -g '*clang*.exe' . 'C:\Program Files' 'C:\msys64' 'C:\mingw64' 2>$null`
> - Ran ``$bf='C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'
> $cases=[ordered]@{
> 'fuera_antes'="2026-03-01 2026-03-31`n2`n2026-02-01,1,1,7`n2026-03-01,1,2,8"
> 'invalida_antes'="2026-03-01 2026-03-31`n2`n2026-02-30,1,1,7`n2026-03-01,1,2,8"
> 'cero_negativos'="2026-03-01 2026-03-31`n3`n2026-03-01,1,1,0`n2026-03-01,2,2,-2`n2026-03-01,3,3,-1"
> 'primera'="2026-03-01 2026-03-31`n3`n2026-03-10,1,3,5`n2026-03-01,1,2,8`n2026-03-20,1,1,9"
> 'espacios'="2026-03-01 2026-03-31`n1`n 2026-03-01 , +001 , 0002 , +007 "
> 'fecha_flexible'="2026-03-01 2026-03-31`n2`n2026-3-1,1,1,5`n2026-03-2,2,2,6"
> 'cantidad_grande'="2026-03-01 2026-03-31`n3`n2026-03-01,1,1,2147483648`n2026-03-01,2,2,9223372036854775807`n2026-03-01,3,3,9223372036854775808"
> }
> foreach($c in $cases.GetEnumerator()){ "$($c.Key):"; $c.Value | & $bf }
> Get-ChildItem -LiteralPath 'C:\Users\abby9\AppData\Local\Programs' -Directory -ErrorAction SilentlyContinue | Select-Object Name
> wsl --list --quiet``
>
> </details>
>
> La caja negra confirma que cuenta la primera línea válida de cada `id_venta`, incluso si está fuera del intervalo: las repeticiones posteriores se descartan. También reporta únicamente productos con total positivo. El archivo original del ejemplo 2 incluye una línea vacía que no aparece en el texto pegado; por eso declara 11 líneas.
>
> <details><summary>Ran 4 commands</summary>
>
> - Ran ``$bf='C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'
> $lines=@('2026-03-01,1,1,2147483647','2026-03-01,1,1,1000000000','2026-03-01,1,1,1000000','2026-03-01,1,1,32768','2026-03-01,1,1,10000',' 2026-03-01,1,1,7 ','2026-03-01 ,1,1,7','2026-03-01, 1,1,7','2026-03-01,1 ,1,7','2026-03-01,1, 1 , 7 ','2026-03-01,+1,1,7','2026-03-01,01,01,007','2026-03-01,1,1,+7','2026-03-01,1,1,7x','2026-03-01,1,1,7,','2026-03-01,1,1,7.0','2026-03-01,1,1,1_000')
> foreach($line in $lines){ $out="2026-03-01 2026-03-31`n1`n$line" | & $bf; "$line => $out" }
> Get-ChildItem -LiteralPath 'C:\Users\abby9\.codex' -Directory | Select-Object Name
> Get-Command node, java -ErrorAction SilentlyContinue | Select-Object Name,Source``
> - Ran ``$bf='C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'
> $qtys=@('10001','20000','32767','-10000','-10001','-0','0','0000000000000000000000000000000000000000000000000007')
> foreach($q in $qtys){ $out="2026-03-01 2026-03-31`n2`n2026-03-01,1,1,$q`n2026-03-01,2,1,10000" | & $bf; "qty $q => $out" }
> $dates=@('0000-01-01','0001-01-01','0999-01-01','1899-12-31','1900-02-29','2000-02-29','2100-02-29','9999-12-31','2026-04-31','2026-00-01','2026-01-00','2026-13-01')
> foreach($d in $dates){ $out="0000-01-01 9999-12-31`n2`n$d,1,1,7`n2026-03-01,1,2,8" | & $bf; "date $d => $out" }
> $lines=@('2026-03-01,1,1,7 ','2026-03-01,1,1,7'+[char]9,'2026-03-01,1,1, 7','2026-03-01,1,1,-0007','2026-03-01,00000000000000000000000001,1,7')
> foreach($line in $lines){ $out="2026-03-01 2026-03-31`n1`n$line" | & $bf; "line [$line] => $out" }
> rg --files --hidden 'C:\Users\abby9\.codex' -g 'clang.exe' -g 'gcc.exe' -g 'tcc.exe' -g 'python.exe' -g 'zig.exe' 2>$null``
> - Ran ``$bf='C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'
> foreach($y in @(1899,1900,1969,1970,1999,2099,2100,2101,2200,9999)){ $out="0000-01-01 9999-12-31`n1`n$y-01-01,1,1,7" | & $bf; "year $y => $out" }
> foreach($len in @(4,5,6,7,8,9,10,11,12,18,19,20,21)){ $v=('0'*($len-1))+'1'; $out="2026-03-01 2026-03-31`n3`n2026-03-01,$v,1,7`n2026-03-01,2,$v,8`n2026-03-01,3,2,$v" | & $bf; "digits $len => $out" }
> $cases=[ordered]@{
> 'empty_consumes'="2026-03-01 2026-03-31`n2`n`n2026-03-01,1,1,5`n2026-03-01,2,2,6"
> 'zero_claims'="2026-03-01 2026-03-31`n2`n2026-03-01,1,1,0`n2026-03-01,1,2,5"
> 'reversed'="2026-03-31 2026-03-01`n1`n2026-03-10,1,1,7"
> 'header_spaces'=" 2026-03-01   2026-03-31 `r`n 1 `r`n2026-03-01,1,1,7"
> }
> foreach($c in $cases.GetEnumerator()){ "$($c.Key):"; $c.Value | & $bf }
> Get-ChildItem -LiteralPath 'C:\Program Files (x86)' -Directory | Select-Object Name
> Get-ChildItem -LiteralPath 'C:\Users\abby9\AppData\Local' -Directory | Where-Object Name -Match 'python|uv|mise|llvm|temp' | Select-Object Name``
> - Ran ``$bf='C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'
> foreach($q in @('0','-0','00','-00','-0007','0007','-10000','10000','-10001','10001')){ $out="2026-03-01 2026-03-31`n2`n2026-03-01,1,1,$q`n2026-03-01,1,2,9" | & $bf; "q [$q] => $out" }
> foreach($len in @(12,13,14,15,16,17)){ $v=('0'*($len-1))+'1'; foreach($f in @(1,2,3)){ $a=@('2026-03-01','1','1','7'); $a[$f]=$v; $line=$a -join ','; $out="2026-03-01 2026-03-31`n1`n$line" | & $bf; "digits $len field $f => $out" } }
> foreach($y in @(1999,2000,2001,2098,2099,2100)){ $out="0000-01-01 9999-12-31`n1`n$y-01-01,1,1,7" | & $bf; "year $y => $out" }
> rg --files 'C:\Users\abby9\AppData\Local\Python' 'C:\Program Files (x86)\Microsoft Visual Studio' -g python.exe -g cl.exe -g clang.exe -g vcvars64.bat 2>$null``
>
> </details>
>
> Encontré restricciones adicionales: fechas entre 2000 y 2099, cantidades entre −10000 y 10000 excluyendo cero, y campos numéricos de hasta 12 dígitos. La caja negra rechaza espacios dentro de los registros y el signo `+`; para coincidir con el juez, el código respetará esa regla y aceptará espacios extra en la cabecera.
>
> <details><summary>Created a file, ran 6 commands</summary>
>
> - Ran ``$bf='C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'
> foreach($q in @('-000000000001','-0000000000001','000000000001','0000000000001')){ $out="2026-03-01 2026-03-31`n2`n2026-03-01,1,1,$q`n2026-03-01,1,2,9" | & $bf; "q [$q] => $out" }
> Get-ChildItem -LiteralPath 'C:\Program Files\Microsoft Visual Studio','C:\Program Files (x86)\Microsoft Visual Studio','C:\Users\abby9\.cache','C:\Users\abby9\.rustup','C:\Users\abby9\.local' -Directory -ErrorAction SilentlyContinue | Select-Object FullName
> Get-ChildItem -LiteralPath 'C:\Users\abby9\.codex\.tmp','C:\Users\abby9\.codex\cache' -Directory -ErrorAction SilentlyContinue | Select-Object FullName
> & 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' --version``
> - Ran `rg --files --hidden 'C:\Users\abby9\.cache\codex-runtimes' 'C:\Users\abby9\AppData\Local\Programs' 'C:\Program Files\Android' 'C:\Users\abby9\AppData\Local\Android' -g '*clang*.exe' -g '*gcc*.exe' -g 'cl.exe' -g 'tcc.exe' -g 'zig.exe' 2>$null; Get-ChildItem -LiteralPath 'C:\Program Files\Git\mingw64\bin' -Filter '*cc*' -ErrorAction SilentlyContinue | Select-Object FullName`
> - Ran `New-Item -ItemType Directory -Path work,outputs -Force | Out-Null`
> - Wrote `./work/probe.py` (+18 -0)
> - Ran `& 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' work\probe.py`
> - Ran `& 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' -c "import sys; sys.path.insert(0,'work'); from probe import run; base=b'2026-03-01 2026-03-31\n1\n'; rows=[b'2026-03-01,1,1,7\r\r\r',b'2026-03-01,1,1,\r7',b'2026-03-01,1,1,7\v',b'2026-03-01,1,1,7\f',b'\r2026-03-01,1,1,7']; print([(r,run(base+r+b'\n')) for r in rows])"`
> - Ran `Get-ChildItem -LiteralPath 'C:\Program Files (x86)\Windows Kits\10\Include','C:\Program Files\Android\Android Studio\plugins\cidr-clangd\bin\clang\win\x64' -ErrorAction SilentlyContinue | Select-Object FullName; rg --files 'C:\Users\abby9\.cache\codex-runtimes' -g stdio.h -g 'libclang*' -g '*tcc*' 2>$null`
>
> </details>
>
> La solución leerá bloques pequeños, guardará los identificadores vistos en un mapa de bits de unos 489 KiB y acumulará los totales en enteros de 64 bits. Usará aproximadamente 2,3 MiB para sus estructuras principales, sin cargar los 90 MB completos. Estoy contrastando los casos borde, incluidos los registros inválidos que no deben reservar un identificador.
>
> <details><summary>Created 2 files, ran a command</summary>
>
> - Wrote `./outputs/solucion.c` (+140 -0)
> - Wrote `./work/verify.py` (+140 -0)
> - Ran `& 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' work\verify.py`
>
> </details>
>
> Los dos ejemplos y los ocho casos borde coinciden con la caja negra. También contrasté el modelo de estas reglas con 200 pruebas aleatorias de 150 registros, sin diferencias. El archivo C está preparado; no encontré un compilador C instalado para ejecutarlo aquí.
</details>

**1. Interpretación**

Consulté la caja negra: una venta válida exige fecha real entre **2000 y 2099**, identificadores dentro de sus rangos y cantidad entre **−10000 y 10000, excluyendo cero**. Debe tener exactamente cuatro campos; los números admiten ceros iniciales y hasta 12 dígitos, pero no signo `+`.

Cuenta la **primera aparición válida de cada `id_venta`, incluso si está fuera del intervalo**. Solo se reportan productos con total **estrictamente positivo**.

Hay una contradicción con la tolerancia a espacios solicitada: la caja negra rechaza espacios en los registros. Respetaré esa regla; aceptaré espacios adicionales en la cabecera, CRLF y ausencia de salto final.

**2. Algoritmo y estructuras**

- Leer mediante `fread`, en bloques de 1 MiB, sin almacenar todo el archivo.
- Validar cada línea antes de modificar cualquier estructura.
- Usar un **mapa de bits** para identificar ventas ya procesadas. Marcar cada venta válida **antes** de comprobar el intervalo.
- Acumular por producto en un arreglo de `int64_t`.
- Recorrer los productos una vez, manteniendo los tres mejores según total descendente e identificador ascendente.

Las líneas vacías consumen una de las `N` líneas. Las líneas demasiado largas se descartan completas, sin aumentar la memoria.

**3. Complejidad**

Para `B` bytes de entrada y `P = 100000` productos:

- **Tiempo:** `O(B + P)`, además de la inicialización de los arreglos.
- **Memoria principal:** aproximadamente **2,24 MiB**: entrada, mapa de bits y acumuladores.

El total puede alcanzar `3 000 000 × 10000 = 30 000 000 000`, por eso se necesitan 64 bits. No hay ordenamiento general, tablas hash ni asignaciones por registro.

Contrasté las reglas con ambos ejemplos, ocho casos borde y 200 pruebas aleatorias. No encontré un compilador C instalado para ejecutar este código aquí.

**4. Código completo**

También disponible como [solucion.c](./outputs/solucion.c).

```c
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_ID 4000000
#define MAX_PRODUCT 100000
#define INPUT_SIZE (1u << 20)

static unsigned char input[INPUT_SIZE];
static size_t pos, available;
static unsigned char seen[(MAX_ID + 8) / 8];
static int64_t total[MAX_PRODUCT + 1];

static inline int next_byte(void) {
    if (pos == available) {
        available = fread(input, 1, sizeof input, stdin);
        pos = 0;
        if (!available) return EOF;
    }
    return input[pos++];
}

/* -1: EOF; -2: linea demasiado larga, ya consumida completa. */
static int read_line(char *s, size_t capacity) {
    size_t n = 0;
    int c, overflow = 0;

    while ((c = next_byte()) != EOF && c != '\n') {
        if (n + 1 < capacity) s[n++] = (char)c;
        else overflow = 1;
    }

    if (c == EOF && n == 0 && !overflow) return -1;
    if (overflow) return -2;

    if (n && s[n - 1] == '\r') --n;
    s[n] = '\0';
    return (int)n;
}

static int digit(char c) {
    return c >= '0' && c <= '9';
}

/* El llamador garantiza que hay diez caracteres disponibles. */
static int date_key(const char *s) {
    static const int days[] = {
        0,31,28,31,30,31,30,31,31,30,31,30,31
    };

    if (s[4] != '-' || s[7] != '-') return -1;

    for (int i = 0; i < 10; ++i)
        if (i != 4 && i != 7 && !digit(s[i])) return -1;

    int y = (s[0]-'0')*1000 + (s[1]-'0')*100
          + (s[2]-'0')*10 + s[3]-'0';
    int m = (s[5]-'0')*10 + s[6]-'0';
    int d = (s[8]-'0')*10 + s[9]-'0';

    if (m < 1 || m > 12) return -1;

    int leap = y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
    if (d < 1 || d > days[m] + (m == 2 && leap)) return -1;

    return y*10000 + m*100 + d;
}

static int number(const char **p, const char *end,
                  int limit, int *out) {
    uint64_t value = 0;
    int digits = 0;

    while (*p < end && digit(**p)) {
        if (++digits > 12) return 0;
        value = value*10 + (unsigned)(**p - '0');
        ++*p;
    }

    if (!digits || value > (uint64_t)limit) return 0;
    *out = (int)value;
    return 1;
}

static int parse_sale(const char *s, int n,
                      int *date, int *id,
                      int *product, int *quantity) {
    if (n < 16 || s[10] != ',') return 0;

    *date = date_key(s);
    if (*date < 20000101 || *date > 20991231) return 0;

    const char *p = s + 11, *end = s + n;

    if (!number(&p, end, MAX_ID, id) || !*id) return 0;
    if (p == end || *p++ != ',') return 0;

    if (!number(&p, end, MAX_PRODUCT, product) || !*product)
        return 0;
    if (p == end || *p++ != ',') return 0;

    int sign = 1;
    if (p < end && *p == '-') {
        sign = -1;
        ++p;
    }

    if (!number(&p, end, 10000, quantity) ||
        !*quantity || p != end)
        return 0;

    *quantity *= sign;
    return 1;
}

static int better(int a, int b) {
    return b == 0 || total[a] > total[b]
        || (total[a] == total[b] && a < b);
}

int main(void) {
    char line[256], d1[11] = {0}, d2[11] = {0};
    unsigned n;

    if (read_line(line, sizeof line) < 0 ||
        sscanf(line, "%10s %10s", d1, d2) != 2)
        return 0;

    int begin = date_key(d1), end = date_key(d2);
    if (begin < 0 || end < 0) return 0;

    if (read_line(line, sizeof line) < 0 ||
        sscanf(line, "%u", &n) != 1)
        return 0;

    for (unsigned i = 0; i < n; ++i) {
        int length = read_line(line, sizeof line);
        if (length == -1) break;
        if (length < 0) continue;

        int date, id, product, quantity;
        if (!parse_sale(line, length,
                        &date, &id, &product, &quantity))
            continue;

        unsigned mask = 1u << (id & 7);
        unsigned index = (unsigned)id >> 3;

        if (seen[index] & mask) continue;
        seen[index] |= (unsigned char)mask;

        if (date >= begin && date <= end)
            total[product] += quantity;
    }

    int best[3] = {0, 0, 0};

    for (int product = 1; product <= MAX_PRODUCT; ++product) {
        if (total[product] <= 0) continue;

        for (int j = 0; j < 3; ++j) {
            if (better(product, best[j])) {
                for (int k = 2; k > j; --k)
                    best[k] = best[k - 1];
                best[j] = product;
                break;
            }
        }
    }

    char output[128];
    size_t used = 0;

    for (int j = 0; j < 3 && best[j]; ++j)
        used += (size_t)snprintf(
            output + used, sizeof output - used,
            "%d %" PRId64 "\n", best[j], total[best[j]]
        );

    if (!used)
        used = (size_t)snprintf(
            output, sizeof output, "SIN DATOS\n"
        );

    fwrite(output, 1, used, stdout);
    return 0;
}
```

**5. Traza de los ejemplos**

**Ejemplo 1:**

| Línea | Acción |
|---|---|
| 1 | Primera venta válida con ID 4: producto 3 suma 5. |
| 2 | Inválida: contiene cinco campos. |
| 3 | Primera venta válida con ID 6: producto 1 suma 9. |
| 4 | ID 6 repetido: se ignora. |
| 5 | Primera venta válida con ID 1: producto 2 suma 5. |
| 6 | Primera venta válida con ID 9: producto 4 suma 5. |
| 7 | ID 9 repetido: se ignora. |
| 8 | ID 4 repetido: se ignora. |

Totales: `1→9`, `2→5`, `3→5`, `4→5`. El desempate deja fuera al producto 4.

```text
1 9
2 5
3 5
```

**Ejemplo 2:**

- ID 6 aporta `5` al producto 4; sus repeticiones se ignoran.
- ID 1 aporta `8` al producto 4.
- ID 5 aporta `4` al producto 1; sus repeticiones se ignoran.
- El producto 0 y la cantidad vacía invalidan sus respectivas líneas.
- La venta de 2000 no aporta al intervalo consultado.

El archivo original contiene una línea vacía después del primer registro: esa es la undécima línea que falta en el texto pegado. El código también termina correctamente si encuentra EOF antes de completar `N`.

```text
4 13
1 4
```

**6. Casos borde**

**Caso 1: ningún registro.**

Entrada:
```text
2026-03-01 2026-03-31
0
```

Salida:
```text
SIN DATOS
```

**Caso 2: la primera venta válida está fuera del intervalo; una fecha inválida no reserva el ID.**

Entrada:
```text
2026-03-01 2026-03-31
4
2026-02-28,1,1,9
2026-03-01,1,2,10
2026-02-30,2,3,8
2026-03-31,2,2,7
```

Salida:
```text
2 7
```

**Caso 3: se excluyen totales cero y negativos.**

Entrada:
```text
2026-03-01 2026-03-31
6
2026-03-01,1,1,7
2026-03-02,2,1,-7
2026-03-03,3,2,-4
2026-03-04,4,3,2
2026-03-05,5,3,-5
2026-03-06,6,4,1
```

Salida:
```text
4 1
```

**Caso 4: cinco productos empatados.**

Entrada:
```text
2026-03-01 2026-03-31
5
2026-03-01,1,5,8
2026-03-01,2,3,8
2026-03-01,3,1,8
2026-03-01,4,4,8
2026-03-01,5,2,8
```

Salida:
```text
1 8
2 8
3 8
```

**Caso 5: año bisiesto y límites de años permitidos en los registros.**

Entrada:
```text
1999-01-01 2100-12-31
6
1999-12-31,1,9,9
2000-02-29,1,1,5
2000-02-30,2,2,9
2000-03-01,2,2,4
2099-12-31,3,3,3
2100-01-01,4,4,10
```

Salida:
```text
1 5
2 4
3 3
```

**Caso 6: cantidades cero, fuera de rango y devoluciones válidas.**

Entrada:
```text
2026-03-01 2026-03-31
6
2026-03-01,1,1,0
2026-03-01,1,2,10000
2026-03-01,2,3,10001
2026-03-01,2,2,-10000
2026-03-01,3,3,-10001
2026-03-01,3,4,1
```

Salida:
```text
4 1
```

**Caso 7: formato estricto, ceros iniciales y límites de identificadores.**

Entrada:
```text
2026-03-01 2026-03-31
8
2026-03-01,4000001,1,9
2026-03-01,1,100001,9
2026-03-01,+1,1,9
2026-03-01,1,1, 9
2026-03-01,1,1,9,0
2026-03-01,0000000000001,1,9
2026-03-01,000000000001,0001,0008
2026-03-01,4000000,100000,10
```

Salida:
```text
100000 10
1 8
```

**Caso 8: espacios en la cabecera, línea vacía y extremos inclusivos.** También funciona guardándolo con CRLF y sin salto final.

Entrada:
```text
  2026-03-01   2026-03-31
  4

2026-03-01,1,1,3
2026-03-31,2,2,4
2026-04-01,3,3,9
```

Salida:
```text
2 4
1 3
```

> OK ahora bien tengo en mi windows msyc2 UCRT64  entregame un codigo para esta consola (bash) para testear los casos limite de este problema usando el .c en la carpeta actual
> NEcesito para probar el codigo utilzia la caja negra para obtener los resultados esperados y despues testear el codigo con los mismo inputs y obtener la respeusta asic omo que no exceda la memoria ni el tiempo solicitado

<details><summary>8 previous messages</summary>

> Prepararé un bloque para pegar en Bash de UCRT64: compilará el `.c` de la carpeta actual, comparará sus salidas con la caja negra y medirá tiempo y memoria en pruebas de hasta 3 millones de registros.
>
> <details><summary>Created a file, ran 7 commands</summary>
>
> - Ran `Get-Item -LiteralPath 'C:\msys64\ucrt64\bin\gcc.exe','C:\msys64\usr\bin\bash.exe','C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' -ErrorAction SilentlyContinue | Select-Object FullName; Get-ChildItem -LiteralPath . -Force | Select-Object Name,Mode; Test-Path -LiteralPath 'C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'`
> - Ran `Get-Location; Get-ChildItem -LiteralPath . -Name; Get-Item -LiteralPath 'outputs\solucion.c' -ErrorAction SilentlyContinue | Format-List FullName,Length; & 'C:\msys64\ucrt64\bin\gcc.exe' --version`
> - Ran `& 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' -c "import ctypes as c, subprocess as s; from ctypes import wintypes as w; class_body=''; P=type('P',(c.Structure,),{'_fields_':[('cb',w.DWORD),('faults',w.DWORD)]+[(x,c.c_size_t) for x in ['peakws','ws','q1','q2','q3','q4','page','peakpage','private']]}); f=c.WinDLL('psapi',use_last_error=True).GetProcessMemoryInfo; f.argtypes=[w.HANDLE,c.POINTER(P),w.DWORD]; f.restype=w.BOOL; p=s.Popen(['C:/Windows/System32/cmd.exe','/c','exit','0'],stdout=s.DEVNULL); p.wait(); a=P(); a.cb=c.sizeof(a); print('ok=', f(w.HANDLE(int(p._handle)),c.byref(a),a.cb),'peak=',a.peakws,'commit_peak=',a.peakpage,'err=',c.get_last_error())"`
> - Wrote `./outputs/probar_bf.sh` (+254 -0)
> - Ran `New-Item -ItemType Directory -Path 'work\ensayo_ucrt64' -Force | Out-Null; Copy-Item -LiteralPath 'outputs\solucion.c' -Destination 'work\ensayo_ucrt64\solucion.c'`
> - Ran `& 'C:\msys64\usr\bin\bash.exe' --noprofile --norc -c 'export PATH=/ucrt64/bin:/usr/bin:$PATH; bash ../../outputs/probar_bf.sh ./solucion.c'`
> - Ran `& 'C:\msys64\usr\bin\bash.exe' --noprofile --norc -c 'export PATH=/ucrt64/bin:/usr/bin:$PATH; bash ../../outputs/probar_bf.sh ./solucion.c'`
> - Ran `& 'C:\msys64\usr\bin\bash.exe' --version; & 'C:\msys64\usr\bin\bash.exe' --noprofile --norc -c 'pwd'; Get-Item -LiteralPath 'C:\msys64\ucrt64\bin\gcc.exe' | Select-Object Length`
>
> </details>
>
> El script ya incluye pruebas masivas de acumulación de 64 bits, 100 000 productos y duplicados con líneas inválidas. Guardará las entradas y ambas salidas para revisar cualquier diferencia. Medirá únicamente el programa C, sin incluir la generación de datos ni la ejecución de la caja negra.
>
> <details><summary>Ran 4 commands</summary>
>
> - Ran `& 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' -c "import subprocess; p=subprocess.run(['C:/msys64/usr/bin/bash.exe','--version'],capture_output=True); print(p.returncode,repr(p.stdout),repr(p.stderr))"; & 'C:\msys64\ucrt64\bin\gcc.exe' -std=c11 -O2 -Wall -Wextra outputs\solucion.c -o work\ensayo_ucrt64\solucion.exe`
> - Ran `$env:PATH='C:\msys64\ucrt64\bin;C:\msys64\usr\bin;'+$env:PATH; & 'C:\msys64\ucrt64\bin\gcc.exe' -std=c11 -O2 -Wall -Wextra outputs\solucion.c -o work\ensayo_ucrt64\solucion.exe; Get-Item -LiteralPath 'work\ensayo_ucrt64\solucion.exe' -ErrorAction SilentlyContinue | Select-Object Length; & 'C:\msys64\usr\bin\bash.exe' --version`
> - Ran `& 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' -c "from pathlib import Path; s=Path('outputs/probar_bf.sh').read_text(); Path('work/ensayo_ucrt64/verificar.py').write_text(s.split(\"<<'PYTHON'\n\",1)[1].split('\nPYTHON\n',1)[0],encoding='utf-8')"`
> - Ran `$harnessText=Get-Content -Raw -LiteralPath 'outputs\probar_bf.sh'; $pythonPart=($harnessText -split "<<'PYTHON'\r?\n",2)[1]; $pythonPart=($pythonPart -split '\r?\nPYTHON\r?\n',2)[0]; [System.IO.File]::WriteAllText((Join-Path $PWD 'work\ensayo_ucrt64\verificar.py'),$pythonPart); & 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' -u work\ensayo_ucrt64\verificar.py 'C:\Users\abby9\Documents\Codex\2026-11-05\aqu-va-una-plantilla-para-guardar\work\ensayo_ucrt64' 'C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'`
>
> </details>
>
> Encontré una limitación de la caja negra: rechaza entradas con más de 300 registros. Ajustaré las pruebas grandes para obtener la referencia con casos pequeños y ampliarlos mediante transformaciones que permiten calcular exactamente la salida esperada. Las pruebas pequeñas sí compararán ambos programas con la misma entrada.
>
> <details><summary>Created 2 files, edited a file, ran 2 commands</summary>
>
> - Wrote `./outputs/probar_bf.sh` (+70 -28)
> - Ran `$harnessText=Get-Content -Raw -LiteralPath 'outputs\probar_bf.sh'; $pythonPart=($harnessText -split "<<'PYTHON'\r?\n",2)[1]; $pythonPart=($pythonPart -split '\r?\nPYTHON\r?\n',2)[0]; [System.IO.File]::WriteAllText((Join-Path $PWD 'work\ensayo_ucrt64\verificar.py'),$pythonPart); & 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' -u work\ensayo_ucrt64\verificar.py 'C:\Users\abby9\Documents\Codex\2026-11-05\aqu-va-una-plantilla-para-guardar\work\ensayo_ucrt64' 'C:\Users\abby9\Downloads\Ronda2_Basica\Ronda2_Basica\BF\caja_windows.exe'`
> - Wrote `./work/ensayo_ucrt64/check_meter.py` (+20 -0)
> - Wrote `./work/ensayo_ucrt64/meter_probe.c` (+12 -0)
> - Ran `$env:PATH='C:\msys64\ucrt64\bin;'+$env:PATH; & 'C:\msys64\ucrt64\bin\gcc.exe' -O2 work\ensayo_ucrt64\meter_probe.c -o work\ensayo_ucrt64\meter_probe.exe; & 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' work\ensayo_ucrt64\check_meter.py; Copy-Item -LiteralPath 'work\ensayo_ucrt64\resultados.tsv' -Destination 'outputs\resultados_bf.tsv'`
>
> </details>
>
> El programa C compilado con GCC de UCRT64 pasó las 27 pruebas. Las tres masivas tuvieron 3 millones de registros cada una; la mayor ocupó unos 96 MB. En esta ejecución, el máximo fue aproximadamente 0,30 segundos y 6,35 MiB de RAM. El script conserva un informe con los resultados de cada prueba.
>
> <details><summary>Edited a file, ran a command</summary>
>
> - Wrote `./outputs/probar_bf.sh` (+1 -1)
> - Ran `$harnessText=Get-Content -Raw -LiteralPath 'outputs\probar_bf.sh'; $pythonPart=($harnessText -split "<<'PYTHON'\r?\n",2)[1]; $pythonPart=($pythonPart -split '\r?\nPYTHON\r?\n',2)[0]; [System.IO.File]::WriteAllText((Join-Path $PWD 'work\ensayo_ucrt64\verificar.py'),$pythonPart); & 'C:\Users\abby9\AppData\Local\Python\pythoncore-3.14-64\python.exe' work\ensayo_ucrt64\check_meter.py`
>
> </details>
</details>

Preparé el [script probar_bf.sh](./outputs/probar_bf.sh).

**Desde UCRT64, situado en la carpeta de tu `.c`, pega:**

```bash
SCRIPT="/c/Users/abby9/Documents/Codex/2026-11-05/aqu-va-una-plantilla-para-guardar/outputs/probar_bf.sh"
bash "$SCRIPT"
```

Detecta automáticamente el archivo si solo hay un `.c`. Si hay varios, indica cuál:

```bash
bash "$SCRIPT" "./solucion.c"
```

El script:

- Compila con `gcc -std=c11 -O2 -Wall -Wextra`.
- Ejecuta **27 pruebas**, incluyendo tres de **3 millones de registros**.
- Compara la salida obtenida con la esperada.
- Comprueba **16 segundos y 64 MiB por ejecución**; detiene el programa si detecta un exceso.
- Mide los picos de RAM y memoria comprometida mediante Windows. La memoria del generador no cuenta.
- Conserva entradas, salidas y `resultados.tsv` en una carpeta `pruebas_bf.*`. Necesita aproximadamente **270 MB de disco**.

**Limitación comprobada:** tu caja negra solo acepta `N ≤ 300`. Para las pruebas pequeñas utiliza exactamente la misma entrada en ambos programas. Para las masivas consulta primero casos base y obtiene la respuesta mediante ampliaciones matemáticamente exactas, conservando las reglas de duplicados.

Ya compilé tu solución con GCC de UCRT64 y ejecuté las pruebas: **27 correctas**, con máximos locales aproximados de **0,30 segundos y 6,35 MiB de RAM**. Puedes consultar el [informe de esta ejecución](./outputs/resultados_bf.tsv).
