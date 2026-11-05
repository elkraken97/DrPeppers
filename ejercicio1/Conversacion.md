# Resolver problema B1 de sensores

> Resuelve el siguiente problema de programacion para un concurso>
>
> Problema B1
> Una estación tiene N sensores. Cada sensor reporta una lectura decimal (hasta 6 decimales, puede ser negativa) o ?
> si la lectura se perdió. Una racha es un tramo de sensores consecutivos que el sistema considera estable con
> tolerancia K.
> Para cada caso imprime la longitud de la racha más larga y la posición 1 a N donde empieza; si hay varias, la de
> menor posición.
> Lo que debes descubrir con la caja negra: qué significa exactamente “estable con tolerancia Kˮ, qué cuenta como
> sensores “consecutivosˮ y qué hace el sistema con las ?.
> Entrada: línea 1 T. Por caso: una línea N K y una línea con N lecturas (decimal o ?).
> Salida: por caso, una línea L P.
> Límites: 1  T  10^5; suma de N  10^6; |lectura|  9·10^12; 0  K  1.8·10^13; K y las lecturas tienen hasta 6
> decimales.
> Tiempo / memoria: 8 s / 256 MB.
> Ejemplo 1
> Entrada:
> 3
> 3 0.500000
> -2.5 -2.5 2.5
> 7 8142465172666.218048
> -512039822660.359888 -512039822660.35989 -512039822660.359889 -512039822660.359889 -512039822660
> .35989 -512039822660.359889 -8654504995326.577938
> 3 0.500000
> 1.500000 -1 -1.5
> Salida:
> 2 1
> 6 1
> 2 2
> Ejemplo 2
> Entrada:
> 2
> 5 5404369877138.611436
> -5118909480930.611125 -5118909480930.611125 -5118909480930.611125 285460396208.000314 2854603962
> 08.000314
> 5 0.0
> -7532612242812.331288 -6854978204203.068603 -2730587357333.559605 9000000000000.000000 900000000
> 0000
> Salida:
>
> 3
> 1
> 2
> 4
>
> Tu entorno es windows 11 con python 3.14.3
> Entrada por entrada estandar (consola) (o argumentos)
> Tenemos limites de memoria de 256B y tiempo de 8 segundos
>
> Requisitos del codigo
> Usa una manera de lectura rapida de los datos asi como la salida de datos utiliza funcionalidades de python para minimizar el tiempo de ejecucion por mas grande que llegue a ser la entrada
> No uses modo debug ni nada que pueda atrasar la manera en que se ejecuta el codigo
> Un solo archivo
>
> Formato de respuesta:
> 1Explica como interpretas el problema
> en caso de que alguna parte del problema o resolucion de la misma llegue a ser ambiguo mencionalo y menciona que suposiocion tomaste ante la ambiguedad
> 2Algoritmo y estructura elegidos menciona porque son adecuados de acuerdo a los limites necesarios para el problema
> 3EL codigo es necesario en un solo bloque
> 4Menciona la complejidad del codigo en espacio tiempo
> 5Traza a mano los ejemplos del enunciado a tu codigo
> 6. Entre 5 y 8 casos borde, cada uno con su entrada y su salida esperada
>    listas para copiar y pegar.

<details><summary>6 previous messages</summary>

> Revisaré qué reglas permiten deducir los ejemplos y señalaré las que necesitan consultas a la caja negra. También cuidaré la precisión de los decimales y el uso de memoria.
>
> ¿Tienes acceso a la caja negra para probar entradas, o reglas adicionales sobre la estabilidad, la consecutividad y los «?»? Los ejemplos no determinan esas reglas de forma única.
>
> **¿Tienes acceso a la caja negra para probar entradas, o reglas adicionales sobre la estabilidad, la consecutividad y los «?»? Los ejemplos no determinan esas reglas de forma única.**
>
> Si tengo acceso a la caja negro
>
> Los ejemplos sí muestran que hay que conservar los decimales exactamente: una diferencia de millonésimas cambia el resultado incluso con números muy grandes. Con la caja negra podemos resolver las reglas faltantes antes de elegir el algoritmo. Esta batería distingue entre estabilidad por rango o por vecinos, posibles rachas circulares y distintos tratamientos de «?».
>
> Ejecuta esta entrada completa en la caja negra y pega aquí la salida, respetando su orden:
>
> ```text
> 10
> 4 1
> 0 1 2 3
> 3 0
> 5 8 5
> 4 0
> 7 ? 7 7
> 3 0
> ? ? ?
> 5 0
> ? 4 4 ? ?
> 5 0
> 4 4 ? 9 9
> 3 1
> 0 ? 2
> 4 1
> 0 ? ? 3
> 3 0.000001
> -0.000001 0 0.000001
> 2 18000000000000
> -9000000000000 9000000000000
> ```
>
> <details><summary>Ran 3 commands</summary>
>
> - Ran `python -c "import sys; from decimal import Decimal; print(sys.version); cases=[('8142465172666.218048','-512039822660.359888','-8654504995326.577938'),('5404369877138.611436','-5118909480930.611125','285460396208.000314')]; [(print('diferencia =',abs(Decimal(a)-Decimal(b)),'; K =',k,'; exceso =',abs(Decimal(a)-Decimal(b))-Decimal(k))) for k,a,b in cases]"`
> - Ran `Get-Command py,python3,python3.14 -ErrorAction SilentlyContinue | Select-Object Name,Source`
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\bin\python3.14.exe' -c "import sys; print(sys.version)"`
>
> </details>
</details>

Pega la salida de los **10 casos de prueba** que te envié. Es necesaria para determinar las reglas sin inventarlas y preparar la solución con el formato que pediste.

Interpretaré «256B» como **256 MB**, según el enunciado. Los decimales se manejarán como enteros en millonésimas: los ejemplos incluyen diferencias de apenas **0.000002** y **0.000003** respecto a K, por lo que usar `float` puede dar respuestas incorrectas.

> **Ejecuta esta entrada completa en la caja negra y pega aquí la salida, respetando su orden: 10 4 1 0 1 2 3 3 0 5 8 5 4 0 7 ? 7 7 3 0 ? ? ? 5 0 ? 4 4 ? ? 5 0 4 4 ? 9 9 3 1 0 ? 2 4 1 0 ? ? 3 3 0.000001 -0.000001 0 0.000001 2 18000000000000 -9000000000000 9000000000000**
>
> C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B1>caja_windows.exe < test.in.txt
> 2 1
> 2 3
> 4 1
> 3 1
> 5 1
> 3 1
> 2 1
> 3 1
> 2 1
> 2 1

<details><summary>5 previous messages</summary>

> Las respuestas indican que los sensores forman un círculo, que los «?» cuentan para la longitud sin restringir las lecturas y que la estabilidad exige `máximo − mínimo ≤ K`. Comprobaré los casos que cruzan del último sensor al primero y los desempates. También revisaré si puedo ejecutar la caja negra directamente desde la ruta que compartiste.
>
> <details><summary>Created 2 files, edited a file, ran 5 commands</summary>
>
> - Ran `Get-Item -LiteralPath 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B1\caja_windows.exe' -ErrorAction SilentlyContinue | Select-Object FullName,Length`
> - Ran `Get-ChildItem -Force -Name`
> - Wrote `./outputs/solucion_b1.py` (+88 -0)
> - Wrote `./work/validate_b1.py` (+61 -0)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\bin\python3.14.exe' work\validate_b1.py`
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\bin\python3.14.exe' -c "import subprocess; p=subprocess.run([r'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B1\caja_windows.exe'],input=b'2\n4 1\n0 1 2 3\n3 0\n5 8 5\n',capture_output=True); print(repr(p.stdout)); print(repr(p.stderr))"`
> - Wrote `./work/validate_b1.py` (+1 -1)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\bin\python3.14.exe' work\validate_b1.py`
>
> </details>
>
> Pude ejecutar la caja negra desde tu ruta. Las reglas inferidas coinciden con las pruebas iniciales, y el algoritmo ya pasó 12 000 casos pequeños comparados con una búsqueda exhaustiva. Ahora contrastaré una muestra con la caja negra y mediré una entrada de un millón de sensores en Python 3.14.3.
>
> <details><summary>Created 2 files, edited a file, ran 3 commands</summary>
>
> - Wrote `./work/benchmark_b1.py` (+40 -0)
> - Wrote `./work/validate_b1.py` (+13 -7)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\bin\python3.14.exe' work\validate_b1.py`
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\bin\python3.14.exe' work\benchmark_b1.py`
> - Wrote `./work/examples_b1.py` (+26 -0)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\bin\python3.14.exe' work\examples_b1.py`
>
> </details>
>
> La solución coincide con la caja negra en 200 casos aleatorios, los cinco casos del enunciado y los ocho casos borde que incluiré. En este equipo, la prueba de un millón de decimales largos tardó 1.29 s y usó un máximo de 134.6 MiB; la de 100 000 casos y un millón de sensores en total tardó 2.03 s.
</details>

**1. Interpretación del problema**

Las pruebas con la caja negra permiten deducir estas reglas:

- Los sensores están en un **círculo**: después del sensor `N` viene el sensor `1`.
- Una racha contiene como máximo `N` sensores, sin repetir ninguno.
- Es estable cuando las lecturas conocidas cumplen **`máximo − mínimo ≤ K`**.
- Los `?` **cuentan para la longitud**, pero no intervienen en el mínimo ni en el máximo.
- Una racha formada únicamente por `?` es estable.
- En caso de empate, se elige la menor posición inicial, numerada desde `1`.

Por ejemplo, para `5 8 5` con `K = 0`, la respuesta es `2 3`: la racha recorre los sensores **3 → 1**.

Estas reglas y la solución coinciden con **200 casos aleatorios ejecutados contra tu caja negra**.

Respecto a las ambigüedades del texto:

- Interpreto «256B» como **256 MB**, según el enunciado.
- Los números partidos por saltos de línea en los ejemplos deben reconstruirse como un solo token.
- La salida del ejemplo 2 se interpreta como dos líneas: `3 1` y `2 4`.

**2. Algoritmo y estructuras elegidas**

Utilizamos una **ventana deslizante con dos colas monótonas**.

Para trabajar con el círculo, duplicamos el arreglo. Así, una racha como `4 → 5 → 1 → 2` se convierte en un intervalo normal del arreglo duplicado.

Recorremos hasta `2N − 1` elementos y mantenemos una ventana `[left, right]`:

1. Limitamos su longitud a `N`.
2. Si la lectura es conocida, actualizamos:
   - Una cola con candidatos al **mínimo**, ordenados por valor creciente.
   - Una cola con candidatos al **máximo**, ordenados por valor decreciente.
3. Mientras `máximo − mínimo > K`, adelantamos `left` hasta excluir el más antiguo de esos dos extremos.
4. Actualizamos la respuesta únicamente si encontramos una longitud mayor.

Ese salto de `left` es correcto: cualquier ventana que conserve ambos extremos seguirá siendo inválida. Debemos eliminar, como mínimo, el que aparece primero.

Las colas guardan **índices**. Cada índice entra y sale como máximo una vez de cada cola, por lo que el recorrido completo es lineal.

Como `left` nunca retrocede, encontramos los inicios en orden creciente. Por eso, al actualizar solo ante una longitud estrictamente mayor, conservamos el menor inicio en los empates.

**Precisión y memoria**

Convertimos cada decimal en un entero multiplicándolo exactamente por `10⁶`:

- `-2.5` → `-2500000`
- `0.000001` → `1`
- `9000000000000` → `9000000000000000000`

La conversión se hace desde el texto, **sin usar `float`**.

Las lecturas escaladas caben en enteros con signo de 64 bits y se almacenan en `array('q')`, que consume 8 bytes por elemento. Las diferencias y `K` se calculan como enteros de Python, por lo que pueden superar el rango de 64 bits sin desbordarse.

La entrada se lee mediante `sys.stdin.buffer.read().split()` y las respuestas se escriben juntas.

**3. Código completo**

Archivo listo para descargar: [solucion_b1.py](./outputs/solucion_b1.py)

```python
import sys
from array import array
from collections import deque
from itertools import islice

SCALE = 1_000_000
POW10 = (1, 10, 100, 1_000, 10_000, 100_000, 1_000_000)
MISSING = 9_223_372_036_854_775_807

def scaled(token):
    negative = token[0] == 45
    if negative:
        token = token[1:]

    whole, _, fraction = token.partition(b'.')
    value = int(whole) * SCALE

    if fraction:
        value += int(fraction) * POW10[6 - len(fraction)]

    return -value if negative else value

def longest_run(values, n, k):
    values *= 2

    minimums = deque()
    maximums = deque()

    left = 0
    best_length = 0
    best_start = 0

    for right in range(2 * n - 1):
        # La ventana no puede contener más de N sensores.
        limit = right - n + 1
        if left < limit:
            left = limit

            if minimums and minimums[0] < left:
                minimums.popleft()

            if maximums and maximums[0] < left:
                maximums.popleft()

        value = values[right]

        # Los desconocidos cuentan, pero no afectan los extremos.
        if value != MISSING:
            while minimums and values[minimums[-1]] >= value:
                minimums.pop()
            minimums.append(right)

            while maximums and values[maximums[-1]] <= value:
                maximums.pop()
            maximums.append(right)

            # Excluir el extremo más antiguo hasta recuperar estabilidad.
            while values[maximums[0]] - values[minimums[0]] > k:
                if minimums[0] < maximums[0]:
                    left = minimums.popleft() + 1
                else:
                    left = maximums.popleft() + 1

        # Los inicios de la segunda copia ya fueron considerados.
        if left >= n:
            break

        length = right - left + 1

        if length > best_length:
            best_length = length
            best_start = left

            # Si todo el círculo es estable, el menor inicio es 1.
            if length == n:
                return n, 1

    return best_length, best_start + 1

def main():
    tokens = iter(sys.stdin.buffer.read().split())
    t = int(next(tokens))
    answers = []

    for _ in range(t):
        n = int(next(tokens))
        k = scaled(next(tokens))

        values = array('q', (
            MISSING if token == b'?' else scaled(token)
            for token in islice(tokens, n)
        ))

        length, start = longest_run(values, n, k)
        answers.append(f'{length} {start}')

    sys.stdout.write('\n'.join(answers))
    sys.stdout.write('\n')

if __name__ == '__main__':
    main()
```

En CMD puedes ejecutarlo como `python solucion_b1.py < entrada.txt`.

**4. Complejidad y validación**

Sea `S` la suma de todos los `N`.

- **Tiempo:** `O(S + T)`. Cada caso recorre como máximo `2N − 1` posiciones y realiza un número amortizado constante de operaciones por posición.
- **Espacio del algoritmo por caso:** `O(N)`.
- **Espacio total del programa:** `O(S + T)`, porque conserva los tokens de toda la entrada y acumula las respuestas.

Pruebas realizadas en este equipo con **Python 3.14.3**:

| Prueba | Tiempo | Pico de memoria observado |
|---|---:|---:|
| Un millón de decimales largos, con una cola monótona grande | 1.29 s | 134.6 MiB |
| 100 000 casos, un millón de sensores en total | 2.03 s | 39.1 MiB |

También pasó **12 000 casos aleatorios contra una solución exhaustiva**, además de los ejemplos y los casos borde siguientes. Las mediciones corresponden a este equipo; el tiempo del juez depende de su hardware.

**5. Traza manual de los ejemplos**

En las tablas, las posiciones están numeradas desde `1` y `Mejor` representa `L P`.

**Ejemplo 1, caso 1**

`K = 0.5`, lecturas: `-2.5 -2.5 2.5`.

| Sensor incorporado | Ventana estable después del ajuste | Mejor |
|---:|---|---|
| 1 | `[1]` | `1 1` |
| 2 | `[1, 2]`, diferencia `0` | `2 1` |
| 3 | `[3]`: mezclar ambos valores produce diferencia `5` | `2 1` |

El enlace circular `3 → 1` también tiene diferencia `5`, por lo que no mejora la respuesta.

Resultado: **`2 1`**.

**Ejemplo 1, caso 2**

Las primeras seis lecturas están entre:

- Mínimo: `-512039822660.359890`.
- Máximo: `-512039822660.359888`.

Su diferencia es `0.000002`, así que la ventana crece desde `[1]` hasta `[1, …, 6]`.

| Sensor incorporado | Ventana estable después del ajuste | Mejor |
|---:|---|---|
| 1 a 6 | `[1, …, r]` | `r 1` |
| 7 | `[7]` | `6 1` |

Al agregar el séptimo sensor, la diferencia respecto al máximo anterior es:

`8142465172666.218050 = K + 0.000002`.

El código elimina ese máximo, pero la lectura del sensor 6 todavía difiere del sensor 7 en:

`8142465172666.218049 = K + 0.000001`.

Por tanto, la ventana termina reduciéndose a `[7]`. El enlace circular `7 → 1` tampoco es estable.

Resultado: **`6 1`**.

**Ejemplo 1, caso 3**

`K = 0.5`, lecturas: `1.5 -1 -1.5`.

| Sensor incorporado | Ventana estable después del ajuste | Mejor |
|---:|---|---|
| 1 | `[1]` | `1 1` |
| 2 | `[2]`, porque `1.5 − (-1) = 2.5` | `1 1` |
| 3 | `[2, 3]`, porque `-1 − (-1.5) = 0.5` | `2 2` |

El enlace `3 → 1` tiene diferencia `3`, por lo que no permite ampliar la racha.

Salida completa del ejemplo 1:

```text
2 1
6 1
2 2
```

**Ejemplo 2, caso 1**

Llamemos:

- `A = -5118909480930.611125`.
- `B = 285460396208.000314`.

Las lecturas son `A A A B B`, y:

`B − A = 5404369877138.611439 = K + 0.000003`.

Por lo tanto, no se pueden mezclar ambos valores.

| Sensor incorporado | Ventana estable después del ajuste | Mejor |
|---:|---|---|
| 1 | `[1]` | `1 1` |
| 2 | `[1, 2]` | `2 1` |
| 3 | `[1, 2, 3]` | `3 1` |
| 4 | `[4]` | `3 1` |
| 5 | `[4, 5]` | `3 1` |

El enlace circular vuelve a mezclar `B` con `A`.

Resultado: **`3 1`**.

**Ejemplo 2, caso 2**

`K = 0`, así que todas las lecturas conocidas de una racha deben ser iguales.

| Sensor incorporado | Ventana estable después del ajuste | Mejor |
|---:|---|---|
| 1 | `[1]` | `1 1` |
| 2 | `[2]` | `1 1` |
| 3 | `[3]` | `1 1` |
| 4 | `[4]` | `1 1` |
| 5 | `[4, 5]`: ambos representan exactamente `9000000000000` | `2 4` |

Los sensores 5 y 1 tienen valores distintos, por lo que el recorrido circular no mejora la respuesta.

Salida completa del ejemplo 2:

```text
3 1
2 4
```

**6. Ocho casos borde**

Cada entrada es independiente e incluye su propio `T`. Todas estas salidas fueron verificadas con la caja negra.

**Caso 1: un único sensor desconocido**

Entrada:

```text
1
1 0
?
```

Salida:

```text
1 1
```

**Caso 2: todos los sensores desconocidos**

Entrada:

```text
1
4 0
? ? ? ?
```

Salida:

```text
4 1
```

**Caso 3: valores extremos y diferencia exactamente igual a K**

Entrada:

```text
1
2 18000000000000
-9000000000000 9000000000000
```

Salida:

```text
2 1
```

**Caso 4: la mejor racha cruza el final del arreglo**

La racha ganadora recorre `4 → 5 → 1 → 2`.

Entrada:

```text
1
5 0
7 7 9 7 7
```

Salida:

```text
4 4
```

**Caso 5: los desconocidos permiten contar todo el círculo**

Entrada:

```text
1
5 0
? 4 4 ? ?
```

Salida:

```text
5 1
```

**Caso 6: un desconocido entre valores incompatibles y empate**

Las rachas `1 → 2 → 3` y `3 → 4 → 5` tienen longitud 3. Gana el inicio 1.

Entrada:

```text
1
5 0
4 4 ? 9 9
```

Salida:

```text
3 1
```

**Caso 7: vecinos compatibles, pero rango completo demasiado grande**

Las diferencias entre vecinos son de una millonésima, pero el rango de los tres valores es de dos millonésimas.

Entrada:

```text
1
3 0.000001
-0.000001 0 0.000001
```

Salida:

```text
2 1
```

**Caso 8: números enormes separados por una millonésima**

Hay dos rachas de longitud 2: `2 → 3` y `4 → 1`. Gana el inicio 2.

Entrada:

```text
1
4 0
-9000000000000 -8999999999999.999999 -8999999999999.999999 -9000000000000
```

Salida:

```text
2 2
```

> para comprobar el funcionamiento del codigo limitalo de acuerdo a los limites establecidos que mencione en el problema
> Optamremos por pruebas de tres niveles
>
> . NIVEL 1: los ejemplos del enunciado, uno por llamada a Probar.
>
> . NIVEL 2: entre 6 y 8 casos borde (valores mínimos y máximos, N=1,
>    todo igual, todo distinto, orden, desbordes de int) con su entrada y
>    su salida esperada, uno por llamada a Probar.
>
> . NIVEL 3: generar con PowerShell un archivo grande con el caso máximo
>    de los límites del enunciado (grande.txt, escrito en ASCII), y medir
>
> Entrega un único bloque de código listo para pegar en la terminal, sin
> explicaciones largas. Las salidas esperadas de los casos borde calcúlalas
> a mano con cuidado y marca con un comentario los que tengan alguna duda.

```powershell
$ErrorActionPreference = 'Stop'

# Ajusta estas rutas si moviste Python o la solución.
$Python = 'C:\Users\jazye\AppData\Local\Python\bin\python3.14.exe'
$Codigo = 'C:\Users\jazye\Documents\Codex\2026-11-05\ne\outputs\solucion_b1.py'

foreach ($Ruta in @($Python, $Codigo)) {
    if (-not (Test-Path -LiteralPath $Ruta -PathType Leaf)) {
        throw "No existe: $Ruta"
    }
}

function Probar {
    param(
        [string]$Nombre,
        [string]$Entrada,
        [string]$Esperada
    )

    $Resultado = $Entrada | & $Python $Codigo
    if ($LASTEXITCODE -ne 0) {
        throw "$Nombre : Python terminó con código $LASTEXITCODE"
    }

    $Actual = (($Resultado -join "`n").Trim() -replace '\s+', ' ')
    $Correcta = ($Esperada.Trim() -replace '\s+', ' ')

    if ($Actual -ne $Correcta) {
        throw "$Nombre : esperado [$Correcta], obtenido [$Actual]"
    }

    Write-Host "OK - $Nombre : $Actual" -ForegroundColor Green
}

# NIVEL 1: cada ejemplo completo en una llamada independiente.

Probar 'Ejemplo 1' @'
3
3 0.500000
-2.5 -2.5 2.5
7 8142465172666.218048
-512039822660.359888 -512039822660.35989 -512039822660.359889 -512039822660.359889 -512039822660.35989 -512039822660.359889 -8654504995326.577938
3 0.500000
1.500000 -1 -1.5
'@ @'
2 1
6 1
2 2
'@

Probar 'Ejemplo 2' @'
2
5 5404369877138.611436
-5118909480930.611125 -5118909480930.611125 -5118909480930.611125 285460396208.000314 285460396208.000314
5 0.0
-7532612242812.331288 -6854978204203.068603 -2730587357333.559605 9000000000000.000000 9000000000000
'@ @'
3 1
2 4
'@

# NIVEL 2: ocho casos independientes.
# Salidas calculadas a mano con las reglas de la caja negra; sin dudas.

# N mínimo y lectura mínima.
Probar 'Borde 1: N=1' @'
1
1 0
-9000000000000
'@ '1 1'

# Todos los desconocidos cuentan.
Probar 'Borde 2: todos desconocidos' @'
1
4 0
? ? ? ?
'@ '4 1'

# Distintas representaciones del mismo valor.
Probar 'Borde 3: todo igual' @'
1
5 0
-7 -7.0 -7.000000 -7.000 -7
'@ '5 1'

# Con K=0 ninguna pareja es válida, tampoco al cerrar el círculo.
Probar 'Borde 4: todo distinto y ordenado' @'
1
5 0
-2 -1 0 1 2
'@ '1 1'

# La racha ganadora recorre 4 -> 5 -> 1 -> 2.
Probar 'Borde 5: racha circular' @'
1
5 0
7 7 9 7 7
'@ '4 4'

# Diferencia = K. Escalada, supera el máximo entero de 64 bits.
Probar 'Borde 6: extremos y desbordamiento' @'
1
2 18000000000000
-9000000000000 9000000000000
'@ '2 1'

# Empatan las rachas 2 -> 3 y 4 -> 1; gana el inicio 2.
Probar 'Borde 7: precision de una millonesima' @'
1
4 0
-9000000000000 -8999999999999.999999 -8999999999999.999999 -9000000000000
'@ '2 2'

# Empatan 1 -> 2 -> 3 y 3 -> 4 -> 5; gana el inicio 1.
Probar 'Borde 8: desconocidos y desempate' @'
1
5 0
4 4 ? 9 9
'@ '3 1'

# NIVEL 3: N = suma de N = 1 000 000.
# T=1: no puede combinarse N=1 000 000 con otros casos sin exceder la suma.
# Valores: 9000000000000 - i/1000000, para i=0..999999.
# Rango total: 0.999999; K: 0.999998.
# Los primeros 999999 sensores son estables. El círculo completo no lo es.
# Salida esperada, sin duda: 999999 1.
# Esta distribución también mantiene una cola monótona grande.

$Grande = Join-Path $PWD.Path 'grande.txt'
$SalidaGrande = Join-Path $PWD.Path 'grande.salida.txt'
$ErrorGrande = Join-Path $PWD.Path 'grande.error.txt'
$N = 1000000
$Cultura = [System.Globalization.CultureInfo]::InvariantCulture

Write-Host 'Generando grande.txt en ASCII...'

$Escritor = [System.IO.StreamWriter]::new(
    $Grande, $false, [System.Text.Encoding]::ASCII, 1048576
)

try {
    $Escritor.WriteLine('1')
    $Escritor.WriteLine('1000000 0.999998')
    $Escritor.Write('9000000000000.000000')

    $Bloque = [System.Text.StringBuilder]::new(131072)

    for ([int]$i = 1; $i -lt $N; $i++) {
        [void]$Bloque.Append(' 8999999999999.')
        [void]$Bloque.Append((1000000 - $i).ToString('D6', $Cultura))

        if ($Bloque.Length -ge 65536) {
            $Escritor.Write($Bloque.ToString())
            [void]$Bloque.Clear()
        }
    }

    if ($Bloque.Length -gt 0) {
        $Escritor.Write($Bloque.ToString())
    }
    $Escritor.WriteLine()
}
finally {
    $Escritor.Dispose()
}

# Consulta el pico real del conjunto de trabajo del proceso en Windows.
if (-not ('B1MedidorMemoria' -as [type])) {
    Add-Type -TypeDefinition @'
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

public static class B1MedidorMemoria
{
    [StructLayout(LayoutKind.Sequential)]
    private struct Contadores
    {
        public uint cb, fallos;
        public UIntPtr picoTrabajo, trabajo;
        public UIntPtr picoPaged, paged, picoNonPaged, nonPaged;
        public UIntPtr pagefile, picoPagefile;
    }

    [DllImport("psapi.dll", SetLastError = true)]
    private static extern bool GetProcessMemoryInfo(
        IntPtr proceso, ref Contadores datos, uint longitud);

    public static ulong Pico(IntPtr proceso)
    {
        Contadores datos = new Contadores();
        datos.cb = (uint)Marshal.SizeOf(typeof(Contadores));
        if (!GetProcessMemoryInfo(proceso, ref datos, datos.cb))
            throw new Win32Exception(Marshal.GetLastWin32Error());
        return datos.picoTrabajo.ToUInt64();
    }
}
'@
}

$LimiteSegundos = 8.0
$LimiteBytes = 256MB
$PicoBytes = [uint64]0
$Motivo = $null

# La generación del archivo y la compilación del medidor quedan fuera del tiempo.
$Reloj = [System.Diagnostics.Stopwatch]::StartNew()
$Proceso = Start-Process `
    -FilePath $Python `
    -ArgumentList ('"{0}"' -f $Codigo) `
    -RedirectStandardInput $Grande `
    -RedirectStandardOutput $SalidaGrande `
    -RedirectStandardError $ErrorGrande `
    -WindowStyle Hidden `
    -PassThru

try {
    # Mantener el handle permite consultar el pico incluso después de terminar.
    $HandleProceso = $Proceso.Handle

    while (-not $Proceso.HasExited) {
        $PicoBytes = [B1MedidorMemoria]::Pico($HandleProceso)

        if ($PicoBytes -gt $LimiteBytes) {
            $Motivo = 'MEMORIA: superó 256 MiB'
            break
        }
        if ($Reloj.Elapsed.TotalSeconds -gt $LimiteSegundos) {
            $Motivo = 'TIEMPO: superó 8 segundos'
            break
        }

        Start-Sleep -Milliseconds 10
    }

    if ($null -ne $Motivo -and -not $Proceso.HasExited) {
        $Proceso.Kill()
    }

    $Proceso.WaitForExit()
    $Reloj.Stop()
    $PicoBytes = [B1MedidorMemoria]::Pico($HandleProceso)
    $CodigoSalida = $Proceso.ExitCode
}
finally {
    if (-not $Proceso.HasExited) {
        $Proceso.Kill()
        $Proceso.WaitForExit()
    }
    $Proceso.Dispose()
}

$Segundos = $Reloj.Elapsed.TotalSeconds
$PicoMiB = $PicoBytes / 1MB

Write-Host ("Tiempo: {0:F3} s / 8 s" -f $Segundos)
Write-Host ("Pico de memoria: {0:F2} MiB / 256 MiB" -f $PicoMiB)

if ($null -ne $Motivo) {
    throw $Motivo
}
if ($Segundos -gt $LimiteSegundos) {
    throw 'TIEMPO: superó 8 segundos'
}
if ($PicoBytes -gt $LimiteBytes) {
    throw 'MEMORIA: superó 256 MiB'
}
if ($CodigoSalida -ne 0) {
    $Detalle = Get-Content -LiteralPath $ErrorGrande -Raw
    throw "Python terminó con código ${CodigoSalida}: $Detalle"
}

$ResultadoGrande = [System.IO.File]::ReadAllText($SalidaGrande).Trim()
if (($ResultadoGrande -replace '\s+', ' ') -ne '999999 1') {
    throw "Resultado incorrecto: esperado [999999 1], obtenido [$ResultadoGrande]"
}

Write-Host 'OK - Nivel 3: 999999 1, dentro de los límites locales.' -ForegroundColor Green
Write-Host "Archivo generado: $Grande"
```

> Peuge el codigo a powershell para testearlo comrpueba si la salida es correcta de acuerdo a los casos de prueba
>
> User context
>
> Attachments:
> - PS C:\Users\jazye\OneDrive\Documentos\prompting competencia> $ErrorActionPrefer…: `~/.codex/attachments/3148521b-a3ae-4d81-adfb-d3dc38688d8e/Texto pegado.txt`

<details><summary>2 previous messages</summary>

> Revisaré la salida que pegaste y la compararé con los resultados esperados de los tres niveles.
>
> <details><summary>Explored a file</summary>
>
> - Read `~/.codex/attachments/3148521b-a3ae-4d81-adfb-d3dc38688d8e/Texto pegado.txt`
>
> </details>
</details>

**Sí: todas las salidas que pegaste coinciden con las esperadas.**

| Prueba | Resultado esperado y obtenido | Estado |
|---|---|---|
| Ejemplo 1 | `2 1`, `6 1`, `2 2` | Correcto |
| Ejemplo 2 | `3 1`, `2 4` | Correcto |
| Borde 1: N=1 | `1 1` | Correcto |
| Borde 2: desconocidos | `4 1` | Correcto |
| Borde 3: todos iguales | `5 1` | Correcto |
| Borde 4: todos distintos | `1 1` | Correcto |
| Borde 5: circular | `4 4` | Correcto |
| Borde 6: extremos | `2 1` | Correcto |
| Borde 7: precisión | `2 2` | Correcto |
| Borde 8: desempate | `3 1` | Correcto |
| Un millón de sensores | `999999 1` | Correcto |

La prueba grande también quedó dentro de los límites:

- **Tiempo:** 1.213 s, frente a 8 s.
- **Memoria máxima:** 134.86 MiB, por debajo de 256 MB incluso interpretados como unidades decimales.

No aparecen errores de ejecución. Los resultados confirman que el programa pasa esta batería; no constituyen por sí solos una garantía sobre todas las pruebas ocultas del concurso.
