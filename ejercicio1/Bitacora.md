# Pruebas de `solucion_b1.py` (Prompt & Code Challenge)

## Explicación breve

Para probar el algoritmo varias veces y confirmar que daba los resultados esperados usé un **script de PowerShell** que ejecuta `solucion_b1.py` con **Python 3.14** y compara su salida contra respuestas calculadas de antemano. El script se organiza en tres niveles:

1. **Nivel 1: ejemplos del enunciado.** Se alimentan por la entrada estándar (stdin) y se comparan con la salida oficial.
2. **Nivel 2: casos borde.** Ocho casos independientes con salida calculada a mano a partir de las reglas de la caja negra (N mínimo, todos desconocidos, valores iguales, rachas circulares, desbordamiento de 64 bits, precisión de una millonésima y desempates).
3. **Nivel 3: prueba de estrés con N = 1 000 000.** Se genera un archivo `grande.txt` en ASCII y se ejecuta el programa midiendo **tiempo** (límite 8 s) y **pico de memoria** (límite 256 MiB) con la API `GetProcessMemoryInfo` de Windows.

**Cómo funciona la comparación:** la función `Probar` envía la entrada al programa, normaliza los espacios en blanco de la salida y lanza una excepción si no coincide con lo esperado. Si todo pasa, imprime `OK` en verde.

## Resultados

| Prueba | Resultado |
|---|---|
| Ejemplo 1 | `2 1 6 1 2 2` OK |
| Ejemplo 2 | `3 1 2 4` OK |
| Borde 1: N=1 | `1 1` OK |
| Borde 2: todos desconocidos | `4 1` OK |
| Borde 3: todo igual | `5 1` OK |
| Borde 4: todo distinto y ordenado | `1 1` OK |
| Borde 5: racha circular | `4 4` OK |
| Borde 6: extremos y desbordamiento | `2 1` OK |
| Borde 7: precisión de una millonésima | `2 2` OK |
| Borde 8: desconocidos y desempate | `3 1` OK |
| Nivel 3: N = 1 000 000 | `999999 1` OK |

**Rendimiento en el Nivel 3:**

- Tiempo: **1.213 s** de 8 s permitidos
- Pico de memoria: **134.86 MiB** de 256 MiB permitidos

## Script completo

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

## Salida de la consola

```text
OK - Ejemplo 1 : 2 1 6 1 2 2
OK - Ejemplo 2 : 3 1 2 4
OK - Borde 1: N=1 : 1 1
OK - Borde 2: todos desconocidos : 4 1
OK - Borde 3: todo igual : 5 1
OK - Borde 4: todo distinto y ordenado : 1 1
OK - Borde 5: racha circular : 4 4
OK - Borde 6: extremos y desbordamiento : 2 1
OK - Borde 7: precision de una millonesima : 2 2
OK - Borde 8: desconocidos y desempate : 3 1
Generando grande.txt en ASCII...
Tiempo: 1.213 s / 8 s
Pico de memoria: 134.86 MiB / 256 MiB
OK - Nivel 3: 999999 1, dentro de los límites locales.
Archivo generado: C:\Users\jazye\OneDrive\Documentos\prompting competencia\grande.txt
```