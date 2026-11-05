# Resolver impresora con prioridades

> Resuelve el siguiente problema de programacion para un concurso>
> Problema B2
> Una impresora recibe trabajos con prioridad y procesa Q órdenes en orden:
> ADD id p: agrega el trabajo id con prioridad p (los id nunca se repiten en ADD. No imprime nada.
> BOOST id x: si el trabajo está pendiente, su prioridad sube x e imprime OK; si no, NO.
> CANCEL id: si está pendiente, lo elimina e imprime OK; si no, NO.
> PRINT k: imprime, en una línea separados por espacio, hasta k trabajos pendientes, de mayor a menor prioridad,
> y los elimina. Si no hay ninguno imprime VACIA.
> Lo que debes descubrir con la caja negra: cómo desempata la impresora cuando dos trabajos tienen la misma
> prioridad, si BOOST cambia algo más que la prioridad, y si las prioridades cambian con el tiempo.
> Entrada: línea 1 Q. Luego Q líneas, una orden cada una.
> Salida: una línea por cada BOOST, CANCEL y PRINT.
> Límites: Q  10^6; 1  id  2·10^6; 1  p  10^9; 1  x  10^18; 1  k  10^6.
> Tiempo / memoria: 10 s / 256 MB.
> Ejemplo 1
> Entrada:
> 17
> ADD 8 4
> CANCEL 8
> PRINT 2
> PRINT 2
> PRINT 1
> BOOST 8 1
> ADD 12 2
> PRINT 1
> PRINT 1
> ADD 26 4
> ADD 13 3
> CANCEL 21
> PRINT 3
> BOOST 26 1
> ADD 15 3
> BOOST 13 1000000000000000000
> BOOST 26 1000000000000000000
> Salida:
> OK
> VACIA
> VACIA
> VACIA
> NO
> 12
> VACIA
> NO
> 26 13
> NO
> NO
> NO
>
> Ejemplo 2
> Entrada:
> 18
> ADD 21 1
> BOOST 21 1000000000000000000
> CANCEL 1
> PRINT 1
> ADD 9 1
> BOOST 9 3
> PRINT 1000000
> BOOST 9 2
> PRINT 2
> PRINT 1000000
> BOOST 9 1
> ADD 28 1
> PRINT 1
> BOOST 21 1000000000000000000
> ADD 2 4
> ADD 1 2
> CANCEL 28
> PRINT 3
> Salida:
> OK
> NO
> 21
> OK
> 9
> NO
> VACIA
> VACIA
> NO
> 28
> NO
> NO
> 2 1
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
> listas para copiar y pegar.
> Tengo acceso a la caja negra por si es necesairo que la ejecutes o pruebes en C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2

<details><summary>8 previous messages</summary>

> Voy a revisar la caja negra y probar los desempates, el efecto de `BOOST` y los posibles cambios de prioridad con el tiempo. También comprobaré los ejemplos antes de preparar el código.
>
> <details><summary>Ran 5 commands</summary>
>
> - Ran `Get-ChildItem -Force 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2' | Select-Object Name,Length,Mode; Get-Command python | Select-Object Source`
> - Ran `Get-Content 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\enunciado.md'; python --version; Get-ChildItem -Path . -Filter AGENTS.md; Get-Item '..\AGENTS.md','..\..\AGENTS.md' -ErrorAction SilentlyContinue`
> - Ran `@'
> 4
> ADD 30 5
> ADD 10 5
> ADD 20 5
> PRINT 3
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
> Get-Command py,python3 -ErrorAction SilentlyContinue | Format-List Name,Source
> Get-ChildItem 'C:\Users\jazye\AppData\Local\Programs\Python','C:\Python314','C:\Users\jazye\.codex' -Filter '*python*' -ErrorAction SilentlyContinue | Select-Object FullName`
> - Ran `@'
> 3
> ADD 30 5
> ADD 10 6
> PRINT 2
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
> @'
> 4
> ADD 30 5
> ADD 10 6
> ADD 20 7
> PRINT 3
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
> @'
> 5
> ADD 30 5
> ADD 10 5
> BOOST 30 1
> BOOST 10 1
> PRINT 2
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
> Get-ChildItem 'C:\Users\jazye\AppData\Local\Python' -ErrorAction SilentlyContinue | Select-Object FullName
> Get-ChildItem 'C:\Users\jazye\.codex' -Directory | Select-Object Name`
> - Ran `@'
> 4
> ADD 30 5
> ADD 10 6
> BOOST 30 1
> PRINT 2
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
> @'
> 5
> ADD 30 5
> ADD 10 5
> BOOST 10 1
> BOOST 30 1
> PRINT 2
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
> $testOrders = @('ADD 30 5') + (@('CANCEL 2000000') * 100) + @('ADD 10 6','PRINT 2'); (@([string]$testOrders.Count) + $testOrders) | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe' | Select-Object -Last 1
> & 'C:\Users\jazye\AppData\Local\Python\pythoncore-3.14-64\python.exe' --version`
>
> </details>
>
> Las primeras pruebas indican que los empates favorecen al trabajo que lleva más tiempo sin actualizarse: un `BOOST` exitoso lo coloca al final de los trabajos con igual prioridad. No he observado cambios de prioridad por el paso de órdenes; voy a contrastar estas reglas con pruebas aleatorias.
>
> Interpreto el límite «256B» como **256 MB**, tal como aparece en el enunciado original; 256 bytes no permitirían ejecutar Python.
>
> <details><summary>Created a file, edited a file, ran 6 commands</summary>
>
> - Ran `New-Item -ItemType Directory -Force work,outputs | Out-Null; Get-Item 'C:\AGENTS.md','C:\Users\AGENTS.md','C:\Users\jazye\AGENTS.md','C:\Users\jazye\Documents\AGENTS.md','C:\Users\jazye\Documents\Codex\AGENTS.md','C:\Users\jazye\Documents\Codex\2026-11-05\AGENTS.md','.\AGENTS.md' -ErrorAction SilentlyContinue | ForEach-Object { $_.FullName; Get-Content -LiteralPath $_.FullName }`
> - Wrote `./work/probe.py` (+73 -0)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\pythoncore-3.14-64\python.exe' work/probe.py`
> - Wrote `./work/probe.py` (+5 -5)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\pythoncore-3.14-64\python.exe' work/probe.py`
> - Ran `Get-Content work/failure.in -TotalCount 70`
> - Ran `@'
> 5
> ADD 30 5
> ADD 99 100
> PRINT 1
> ADD 10 6
> PRINT 2
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
> @'
> 6
> ADD 30 5
> ADD 99 100
> ADD 98 100
> PRINT 2
> ADD 10 7
> PRINT 2
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
> @'
> 5
> ADD 30 5
> ADD 99 100
> CANCEL 99
> ADD 10 6
> PRINT 2
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'`
> - Wrote `./work/probe.py` (+1 -0)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\pythoncore-3.14-64\python.exe' work/probe.py`
>
> </details>
>
> La prueba aleatoria reveló la regla temporal: **después de cada `PRINT`, los trabajos que siguen pendientes ganan 1 de prioridad**, independientemente de cuántos se imprimieron. Junto con el desempate por la última operación `ADD` o `BOOST` exitosa, esta regla coincidió con la caja negra en 200 pruebas aleatorias, que suman 60 000 órdenes.
>
> La caja negra acepta como máximo 300 órdenes por ejecución. Probaré el rendimiento de la solución por separado con un millón de órdenes.
>
> <details><summary>Created 4 files, ran 3 commands</summary>
>
> - Wrote `./outputs/solucion.py` (+75 -0)
> - Wrote `./work/check_solution.py` (+45 -0)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\pythoncore-3.14-64\python.exe' work/check_solution.py`
> - Wrote `./work/benchmark.py` (+41 -0)
> - Wrote `./work/measure.py` (+24 -0)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\pythoncore-3.14-64\python.exe' work/benchmark.py`
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\pythoncore-3.14-64\python.exe' -u -c "from pathlib import Path; import subprocess; p=Path(r'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'); c=['ADD 2000000 1']+['BOOST 2000000 1000000000000000000']*10+['ADD 1 1','BOOST 1 1000000000000000000','PRINT 1000000','BOOST 2000000 1']; data=str(len(c))+'\n'+'\n'.join(c)+'\n'; print(data); print('OUTPUT:'); print(subprocess.run([str(p)],input=data,text=True,capture_output=True).stdout)"`
>
> </details>
>
> El código ya coincide con ambos ejemplos y con otras 200 pruebas aleatorias contra la caja negra. En tres pruebas de un millón de órdenes, con Python 3.14.3, tardó entre **1.1 y 2.7 segundos** y usó como máximo **110.4 MiB** de memoria.
>
> Usé enteros compactos en el montículo para reducir memoria y un contador global para aplicar el aumento de prioridad de `PRINT` sin recorrer todos los trabajos pendientes.
>
> <details><summary>Created a file, edited a file, ran a command</summary>
>
> - Wrote `./work/benchmark.py` (+1 -1)
> - Wrote `./work/edge_cases.py` (+34 -0)
> - Ran `& 'C:\Users\jazye\AppData\Local\Python\pythoncore-3.14-64\python.exe' work/edge_cases.py`
>
> </details>
</details>

**1. Interpretación y reglas descubiertas**

La impresora mantiene trabajos pendientes. `ADD` agrega uno, `BOOST` aumenta su prioridad, `CANCEL` lo elimina y `PRINT` extrae los trabajos que deben imprimirse primero.

Probé la caja negra y encontré estas reglas:

- Se imprime primero el trabajo con **mayor prioridad actual**.
- Si hay empate, gana el trabajo cuya última operación **`ADD` o `BOOST` exitosa ocurrió antes**.
- Un `BOOST` exitoso aumenta la prioridad y **renueva la antigüedad utilizada para desempatar**.
- Después de cada `PRINT`, **todos los trabajos que siguen pendientes aumentan su prioridad en 1**, independientemente de cuántos trabajos se imprimieron.
- Las demás órdenes no producen ese aumento global.

Por ejemplo, si dos trabajos terminan empatados porque se aplicó `BOOST` al más antiguo, gana el otro: su última actualización ocurrió antes.

Estas reglas coincidieron con 400 pruebas aleatorias de 300 órdenes: 200 para contrastar el modelo y otras 200 para verificar el código final.

**Ambigüedades:** interpreto «256B» como **256 MB**, de acuerdo con el enunciado original. Tomo **8 segundos** como límite de tiempo solicitado. La caja negra limita sus pruebas a `Q ≤ 300`; las pruebas de rendimiento con un millón de órdenes se hicieron directamente sobre la solución.

**2. Algoritmo y estructuras elegidos**

Utilizaremos un **montículo mínimo (`heapq`)**, una lista indexada por identificador y un contador global.

Para evitar recorrer todos los pendientes después de cada `PRINT`, mantenemos:

- `aging`: número de órdenes `PRINT` procesadas.
- Para cada trabajo, un valor `a` tal que:

\[
\text{prioridad actual} = aging-a
\]

Por tanto:

- `ADD id p`: asignamos `a = aging - p`.
- `BOOST id x`: cambiamos `a` por `a - x`.
- Después de `PRINT`: incrementamos `aging`.

Así, incrementar `aging` aumenta automáticamente en uno la prioridad efectiva de todos los pendientes, sin modificar sus entradas.

Como todos comparten el mismo `aging`, **menor `a` significa mayor prioridad**.

Para reducir memoria, cada entrada del montículo es un solo entero que representa:

\[
clave=a\cdot2^{41}+turno\cdot2^{21}+id
\]

Reservamos:

- **21 bits** para `id`, porque `2 000 000 < 2²¹`.
- **20 bits** para `turno`, porque `Q ≤ 1 000 000 < 2²⁰`.

Ordenar estas claves equivale a ordenar primero por `a` y después por el turno de la última actualización. El identificador permite recuperar el trabajo; no modifica el desempate porque los turnos de actualización son distintos.

La lista `current[id]` contiene la clave vigente del trabajo, o `0` si no está pendiente. Ninguna clave válida es cero, porque su identificador es positivo.

Para `BOOST`, insertamos una nueva clave y dejamos la anterior en el montículo. Para `CANCEL`, ponemos `current[id] = 0`. Durante `PRINT`, descartamos las entradas que ya no coincidan con `current[id]`. Esta técnica se llama **eliminación diferida**.

**Por qué es correcto:** cada trabajo pendiente conserva una entrada vigente en el montículo. Las entradas obsoletas se descartan; entre las vigentes, la menor clave corresponde exactamente a la mayor prioridad y, ante empate, a la actualización más antigua. Por eso cada extracción válida imprime el trabajo correcto. El incremento de `aging` aplica después el aumento global requerido.

La entrada se lee por líneas mediante `sys.stdin.buffer.readline`, y la salida se escribe en bloques de 8192 respuestas.

**3. Código**

También está disponible como archivo: [solucion.py](./outputs/solucion.py).

```python
import sys
from heapq import heappush, heappop

def main():
    read = sys.stdin.buffer.readline
    write = sys.stdout.write
    first = read()
    if not first:
        return
    q = int(first)

    ID_BITS = 21
    SHIFT = 41
    ID_MASK = (1 << ID_BITS) - 1

    # 0 significa que el trabajo no esta pendiente.
    current = [0] * 2_000_001
    heap = []
    output = []
    aging = 0
    push = heappush
    pop = heappop

    for turn in range(q):
        parts = read().split()
        op = parts[0]
        arg = int(parts[1])

        if op == b'ADD':
            priority = int(parts[2])
            key = ((aging - priority) << SHIFT) | (turn << ID_BITS) | arg
            current[arg] = key
            push(heap, key)

        elif op == b'BOOST':
            old = current[arg]
            if old:
                key = (((old >> SHIFT) - int(parts[2])) << SHIFT) | (turn << ID_BITS) | arg
                current[arg] = key
                push(heap, key)
                output.append('OK')
            else:
                output.append('NO')

        elif op == b'CANCEL':
            if current[arg]:
                current[arg] = 0
                output.append('OK')
            else:
                output.append('NO')

        else:  # PRINT
            printed = []
            remaining = arg
            while heap and remaining:
                key = pop(heap)
                job_id = key & ID_MASK
                if current[job_id] == key:
                    current[job_id] = 0
                    printed.append(str(job_id))
                    remaining -= 1
            output.append(' '.join(printed) if printed else 'VACIA')
            aging += 1

        if len(output) >= 8192:
            write('\n'.join(output) + '\n')
            output.clear()

    if output:
        write('\n'.join(output) + '\n')

if __name__ == '__main__':
    main()
```

Los enteros de Python permiten acumular prioridades superiores al máximo de un entero de 64 bits.

**4. Complejidad**

Sea `U = 2 000 000`, el máximo identificador.

- **Tiempo total: `O(U + Q log Q)`**, incluyendo la inicialización de la lista.
- **Espacio: `O(U + Q)`**.

Cada `ADD` o `BOOST` exitoso inserta una entrada. Hay como máximo `Q` inserciones y cada entrada se extrae como máximo una vez, aunque sea obsoleta. Además, cada trabajo solo puede imprimirse una vez.

En las pruebas realizadas con Windows y Python 3.14.3:

| Prueba de 1 000 000 de órdenes | Tiempo | Memoria máxima |
|---|---:|---:|
| 999 999 altas y una impresión completa | 2.71 s | 110.4 MiB |
| Un alta, 999 998 aumentos y una impresión | 1.31 s | 88.4 MiB |
| 400 000 altas, 400 000 aumentos, 199 999 cancelaciones y una impresión | 1.11 s | 77.0 MiB |

Los tiempos corresponden al equipo de prueba, con salida redirigida. También se verificó un caso de un millón de órdenes con muchos `PRINT` vacíos para comprobar los valores elevados del contador y los turnos.

**5. Traza a mano de los ejemplos**

En las tablas, `id:prioridad` representa un trabajo pendiente con su **prioridad efectiva**. `—` significa que la orden no genera salida. Usamos `H = 10¹⁸`.

**Ejemplo 1**

| Paso | Orden | Pendientes después | Salida |
|---:|---|---|---|
| 1 | `ADD 8 4` | `8:4` | — |
| 2 | `CANCEL 8` | Vacío | `OK` |
| 3 | `PRINT 2` | Vacío | `VACIA` |
| 4 | `PRINT 2` | Vacío | `VACIA` |
| 5 | `PRINT 1` | Vacío | `VACIA` |
| 6 | `BOOST 8 1` | Vacío | `NO` |
| 7 | `ADD 12 2` | `12:2` | — |
| 8 | `PRINT 1` | Vacío | `12` |
| 9 | `PRINT 1` | Vacío | `VACIA` |
| 10 | `ADD 26 4` | `26:4` | — |
| 11 | `ADD 13 3` | `26:4, 13:3` | — |
| 12 | `CANCEL 21` | `26:4, 13:3` | `NO` |
| 13 | `PRINT 3` | Vacío | `26 13` |
| 14 | `BOOST 26 1` | Vacío | `NO` |
| 15 | `ADD 15 3` | `15:3` | — |
| 16 | `BOOST 13 H` | `15:3` | `NO` |
| 17 | `BOOST 26 H` | `15:3` | `NO` |

En el paso 13 se piden tres trabajos, pero solamente hay dos. Se imprimen ambos, empezando por el de prioridad 4.

El contador `aging` termina en 6. El trabajo 15 se agregó cuando ya valía 6, por lo que su valor almacenado es `a = 6 - 3 = 3` y su prioridad efectiva sigue siendo `6 - 3 = 3`.

**Ejemplo 2**

| Paso | Orden | Pendientes después | Salida |
|---:|---|---|---|
| 1 | `ADD 21 1` | `21:1` | — |
| 2 | `BOOST 21 H` | `21:H+1` | `OK` |
| 3 | `CANCEL 1` | `21:H+1` | `NO` |
| 4 | `PRINT 1` | Vacío | `21` |
| 5 | `ADD 9 1` | `9:1` | — |
| 6 | `BOOST 9 3` | `9:4` | `OK` |
| 7 | `PRINT 1000000` | Vacío | `9` |
| 8 | `BOOST 9 2` | Vacío | `NO` |
| 9 | `PRINT 2` | Vacío | `VACIA` |
| 10 | `PRINT 1000000` | Vacío | `VACIA` |
| 11 | `BOOST 9 1` | Vacío | `NO` |
| 12 | `ADD 28 1` | `28:1` | — |
| 13 | `PRINT 1` | Vacío | `28` |
| 14 | `BOOST 21 H` | Vacío | `NO` |
| 15 | `ADD 2 4` | `2:4` | — |
| 16 | `ADD 1 2` | `2:4, 1:2` | — |
| 17 | `CANCEL 28` | `2:4, 1:2` | `NO` |
| 18 | `PRINT 3` | Vacío | `2 1` |

En el paso 7, el código imprime el trabajo 9 usando su clave actualizada y descarta su entrada anterior cuando la encuentra. No lo imprime dos veces.

Las salidas de ambas trazas coinciden exactamente con las del enunciado.

**6. Siete casos borde**

Todos estos casos se comprobaron tanto con la caja negra como con el código.

**Caso 1: cola vacía e identificadores inexistentes**

Entrada:

```text
5
PRINT 1000000
BOOST 1 1
CANCEL 2000000
PRINT 1
CANCEL 1
```

Salida esperada:

```text
VACIA
NO
NO
VACIA
NO
```

**Caso 2: empate por antigüedad, independientemente del identificador**

Entrada:

```text
6
ADD 30 7
ADD 10 7
ADD 20 7
PRINT 2
PRINT 5
PRINT 1
```

Salida esperada:

```text
30 10
20
VACIA
```

**Caso 3: `BOOST` renueva la antigüedad**

El trabajo 9 llega primero, pero al alcanzar prioridad 5 mediante `BOOST` pierde el desempate frente al trabajo 2.

Entrada:

```text
4
ADD 9 4
ADD 2 5
BOOST 9 1
PRINT 2
```

Salida esperada:

```text
OK
2 9
```

**Caso 4: aumento global de uno por `PRINT`**

El primer `PRINT` imprime dos trabajos, pero la prioridad del trabajo 30 aumenta solamente de 5 a 6. Después empata con el trabajo 10 y gana por antigüedad.

Entrada:

```text
7
ADD 30 5
ADD 99 100
ADD 98 100
PRINT 2
ADD 10 6
ADD 20 7
PRINT 3
```

Salida esperada:

```text
99 98
20 30 10
```

**Caso 5: otras órdenes no aumentan globalmente las prioridades**

Entrada:

```text
5
ADD 30 5
CANCEL 99
BOOST 99 10
ADD 10 6
PRINT 2
```

Salida esperada:

```text
NO
NO
10 30
```

**Caso 6: cancelación de un trabajo actualizado y entradas obsoletas**

Las dos entradas del trabajo 8 deben ignorarse después de cancelarlo.

Entrada:

```text
9
ADD 8 1
BOOST 8 3
ADD 2 3
CANCEL 8
BOOST 8 100
ADD 5 2
PRINT 10
CANCEL 2
PRINT 1
```

Salida esperada:

```text
OK
OK
NO
2 5
NO
VACIA
```

**Caso 7: prioridad acumulada superior a 64 bits e identificador máximo**

El trabajo 2000000 alcanza prioridad `10¹⁹ + 1`, superior al máximo de un entero con signo de 64 bits.

Entrada:

```text
15
ADD 2000000 1
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
ADD 1 1
BOOST 1 1000000000000000000
PRINT 1000000
BOOST 2000000 1
```

Salida esperada:

```text
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
2000000 1
NO
```

> para comprobar el funcionamiento del codigo limitalo de acuerdo a los limites establecidos que mencione en el problema
> Optamremos por pruebas de tres niveles
>
> . NIVEL 1: los ejemplos del enunciado, uno por llamada a Probar.
>
> . NIVEL 2: entre 6 y 8 casos borde (valores mínimos y máximos, N=1,
> todo igual, todo distinto, orden, desbordes de int) con su entrada y
> su salida esperada, uno por llamada a Probar.
>
> . NIVEL 3: generar con PowerShell un archivo grande con el caso máximo
> de los límites del enunciado (grande.txt, escrito en ASCII), y medir
>
> Entrega un único bloque de código listo para pegar en la terminal, sin
> explicaciones largas. Las salidas esperadas de los casos borde calcúlalas
> a mano con cuidado y marca con un comentario los que tengan alguna duda.
>
> Las salidas esperadas deben de ser de el output de la caja negra no los calcules por tu cuenta
> para ver si son ocrrectas o no

<details><summary>2 previous messages</summary>

> Prepararé un único bloque de PowerShell: cada prueba pequeña obtendrá su salida esperada de la caja negra, y la prueba de un millón de órdenes medirá tiempo y memoria frente a los límites de 8 segundos y 256 MB.
>
> <details><summary>Created a file, edited a file, ran 2 commands</summary>
>
> - Ran `Get-Content outputs/solucion.py -TotalCount 10
> @'
> 1
> PRINT 1
> '@ | & 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
> $PSVersionTable.PSVersion.ToString()`
> - Wrote `./outputs/pruebas.ps1` (+236 -0)
> - Ran `.\outputs\pruebas.ps1`
> - Wrote `./outputs/pruebas.ps1` (+3 -2)
>
> </details>
</details>

```powershell
$ErrorActionPreference = 'Stop'

$Solucion = 'C:\Users\jazye\Documents\Codex\2026-11-05\resuelve-el-siguiente-problema-de-programacion\outputs\solucion.py'
$Caja = 'C:\Users\jazye\OneDrive\Documentos\Ronda1_Basica\Ronda1_Basica\B2\caja_windows.exe'
$Python = 'C:\Users\jazye\AppData\Local\Python\pythoncore-3.14-64\python.exe'
$Carpeta = Split-Path -Parent $Solucion
$MaxSegundos = 8.0
$MaxMemoria = 256MB

foreach ($ruta in @($Solucion, $Caja, $Python)) {
    if (-not (Test-Path -LiteralPath $ruta)) {
        throw "No existe: $ruta"
    }
}

# Ejecuta sin ventana; vigila tiempo y memoria cada 10 ms.
# La memoria indicada es el pico observado del proceso.
function Ejecutar($Exe, $Argumentos, $Entrada, $Salida) {
    $info = [Diagnostics.ProcessStartInfo]::new()
    $info.FileName = $Exe
    $info.Arguments = $Argumentos
    $info.UseShellExecute = $false
    $info.CreateNoWindow = $true
    $info.RedirectStandardInput = $true
    $info.RedirectStandardOutput = $true
    $info.RedirectStandardError = $true

    $proceso = [Diagnostics.Process]::new()
    $proceso.StartInfo = $info
    $origen = [IO.File]::OpenRead($Entrada)
    $destino = [IO.File]::Create($Salida)
    $reloj = [Diagnostics.Stopwatch]::StartNew()
    $pico = 0L
    $limite = ''
    $cerrada = $false

    try {
        [void]$proceso.Start()
        $copiarSalida = $proceso.StandardOutput.BaseStream.CopyToAsync($destino)
        $leerError = $proceso.StandardError.ReadToEndAsync()
        $copiarEntrada = $origen.CopyToAsync($proceso.StandardInput.BaseStream)

        while (-not $proceso.HasExited) {
            if ($copiarEntrada.IsCompleted -and -not $cerrada) {
                $copiarEntrada.GetAwaiter().GetResult()
                $proceso.StandardInput.Close()
                $cerrada = $true
            }

            $proceso.Refresh()
            $pico = [Math]::Max($pico, $proceso.PeakWorkingSet64)

            if ($reloj.Elapsed.TotalSeconds -gt $MaxSegundos) {
                $limite = 'TIEMPO'
            }
            if ($pico -gt $MaxMemoria) {
                $limite = 'MEMORIA'
            }

            if ($limite) {
                if (-not $proceso.HasExited) { $proceso.Kill() }
                break
            }
            Start-Sleep -Milliseconds 10
        }

        $proceso.WaitForExit()
        $reloj.Stop()
        $proceso.Refresh()
        $pico = [Math]::Max($pico, $proceso.PeakWorkingSet64)

        try {
            $copiarEntrada.GetAwaiter().GetResult()
        }
        catch {
            if (-not $limite) { throw }
        }

        $copiarSalida.GetAwaiter().GetResult()
        $errores = $leerError.GetAwaiter().GetResult()

        if ($reloj.Elapsed.TotalSeconds -gt $MaxSegundos -and -not $limite) {
            $limite = 'TIEMPO'
        }
        if ($pico -gt $MaxMemoria) { $limite = 'MEMORIA' }

        if ($limite) { throw "Limite excedido: $limite" }
        if ($proceso.ExitCode -ne 0) {
            throw "Error de ejecucion: $errores"
        }

        [pscustomobject]@{
            Segundos = $reloj.Elapsed.TotalSeconds
            MiB = $pico / 1MB
        }
    }
    finally {
        if ($proceso.Id -and -not $proceso.HasExited) {
            $proceso.Kill()
            $proceso.WaitForExit()
        }
        $origen.Dispose()
        $destino.Dispose()
        $proceso.Dispose()
    }
}

function Probar($Nombre, $Texto) {
    $entrada = Join-Path $Carpeta "$Nombre.in"
    $esperada = Join-Path $Carpeta "$Nombre.esperada.txt"
    $obtenida = Join-Path $Carpeta "$Nombre.obtenida.txt"

    [IO.File]::WriteAllText(
        $entrada, $Texto.Trim() + "`n", [Text.Encoding]::ASCII
    )

    # La salida esperada se obtiene de la caja negra, sin calcularla.
    $null = Ejecutar $Caja '' $entrada $esperada
    $medida = Ejecutar $Python ('"' + $Solucion + '"') $entrada $obtenida

    $e = [IO.File]::ReadAllText($esperada).Replace("`r`n", "`n").TrimEnd([char[]]"`n")
    $o = [IO.File]::ReadAllText($obtenida).Replace("`r`n", "`n").TrimEnd([char[]]"`n")

    Write-Host "`n=== $Nombre ==="
    Write-Host "ENTRADA:`n$($Texto.Trim())"
    Write-Host "ESPERADA (caja negra):`n$e"

    if ($o -cne $e) {
        throw "FALLO. Salida obtenida:`n$o"
    }

    Write-Host ('OK | {0:F3} s | pico observado: {1:F1} MiB' -f `
        $medida.Segundos, $medida.MiB)
}

# NIVEL 1: una llamada por ejemplo.

Probar 'N1-ejemplo1' @'
17
ADD 8 4
CANCEL 8
PRINT 2
PRINT 2
PRINT 1
BOOST 8 1
ADD 12 2
PRINT 1
PRINT 1
ADD 26 4
ADD 13 3
CANCEL 21
PRINT 3
BOOST 26 1
ADD 15 3
BOOST 13 1000000000000000000
BOOST 26 1000000000000000000
'@

Probar 'N1-ejemplo2' @'
18
ADD 21 1
BOOST 21 1000000000000000000
CANCEL 1
PRINT 1
ADD 9 1
BOOST 9 3
PRINT 1000000
BOOST 9 2
PRINT 2
PRINT 1000000
BOOST 9 1
ADD 28 1
PRINT 1
BOOST 21 1000000000000000000
ADD 2 4
ADD 1 2
CANCEL 28
PRINT 3
'@

# NIVEL 2: ocho casos, una llamada por caso.

Probar 'N2-01-Q-minimo' @'
1
PRINT 1
'@

Probar 'N2-02-vacia-extremos' @'
5
PRINT 1000000
BOOST 1 1
CANCEL 2000000
PRINT 1
CANCEL 1
'@

Probar 'N2-03-prioridades-iguales' @'
6
ADD 30 7
ADD 10 7
ADD 20 7
PRINT 2
PRINT 5
PRINT 1
'@

Probar 'N2-04-boost-desempate' @'
4
ADD 9 4
ADD 2 5
BOOST 9 1
PRINT 2
'@

Probar 'N2-05-envejecimiento' @'
7
ADD 30 5
ADD 99 100
ADD 98 100
PRINT 2
ADD 10 6
ADD 20 7
PRINT 3
'@

Probar 'N2-06-distintas-y-prioridad-maxima' @'
6
ADD 30 1
ADD 10 1000000000
ADD 20 2
PRINT 1
PRINT 1
PRINT 1
'@

Probar 'N2-07-cancelacion-y-obsoletas' @'
9
ADD 8 1
BOOST 8 3
ADD 2 3
CANCEL 8
BOOST 8 100
ADD 5 2
PRINT 10
CANCEL 2
PRINT 1
'@

Probar 'N2-08-supera-int64' @'
15
ADD 2000000 1
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
BOOST 2000000 1000000000000000000
ADD 1 1
BOOST 1 1000000000000000000
PRINT 1000000
BOOST 2000000 1
'@

# NIVEL 3: Q=1000000; 999999 pendientes antes de PRINT.
# Alcanza los maximos de id, p y k; identificadores sin repeticion.
# ASCII. La generacion no se incluye en el tiempo de ejecucion.
$Grande = Join-Path $Carpeta 'grande.txt'
$SalidaGrande = Join-Path $Carpeta 'grande.salida.txt'

$archivo = [IO.StreamWriter]::new(
    $Grande, $false, [Text.Encoding]::ASCII, 1048576
)

try {
    $archivo.WriteLine('1000000')

    for ($i = 1; $i -le 999999; $i++) {
        $idTrabajo = if ($i -eq 999999) { 2000000 } else { $i }
        $prioridad = 1000000000 - 999999 + $i
        $archivo.WriteLine("ADD $idTrabajo $prioridad")
    }

    $archivo.WriteLine('PRINT 1000000')
}
finally {
    $archivo.Dispose()
}

Write-Host "`n=== NIVEL 3 ==="
Write-Host "Archivo: $Grande"

$medida = Ejecutar $Python ('"' + $Solucion + '"') $Grande $SalidaGrande

Write-Host ('DENTRO DE LIMITES | {0:F3} / 8 s | pico observado: {1:F1} / 256 MiB' -f `
    $medida.Segundos, $medida.MiB)

# Solo rendimiento: la caja negra rechaza Q > 300.
# No se inventa una salida esperada para este nivel.
Write-Host "Sin comparacion con caja negra para Q=1000000."
Write-Host "Salida guardada en: $SalidaGrande"
```
