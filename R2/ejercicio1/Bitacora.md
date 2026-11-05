Se comprobo mediante un codigo Bash los casos limite en nuestro algoritmo
Comparando los resultados de la caja negra con los resultados de nuestor algoritmo para ganarantizar resultados correctos 
Codigo bash:
#!/usr/bin/env bash
set -euo pipefail
shopt -s nullglob

BOX=${BOX:-/c/Users/abby9/Downloads/Ronda2_Basica/Ronda2_Basica/BF/caja_windows.exe}
if (($#)); then
    SOURCE=$1
else
    sources=(./*.c)
    if ((${#sources[@]} != 1)); then
        echo 'Uso: bash probar_bf.sh nombre.c (hay cero o varios .c).' >&2
        exit 1
    fi
    SOURCE=${sources[0]}
fi
[[ -f "$SOURCE" && -f "$BOX" ]] || {
    echo 'No se encuentra el archivo C o la caja negra. Revisa SOURCE/BOX.' >&2
    exit 1
}
command -v gcc >/dev/null || { echo 'Falta GCC de UCRT64.' >&2; exit 1; }

PY=()
if command -v py >/dev/null && py -3 -c 'import sys; assert sys.platform == "win32"' 2>/dev/null; then
    PY=(py -3)
else
    localapp=$(cygpath -u "${LOCALAPPDATA:-C:/Users/abby9/AppData/Local}")
    for candidate in python3 python "$localapp"/Python/pythoncore-*/python.exe "$localapp"/Programs/Python/Python*/python.exe; do
        if "$candidate" -c 'import sys; assert sys.platform == "win32"' >/dev/null 2>&1; then
            PY=("$candidate")
            break
        fi
    done
fi
((${#PY[@]})) || { echo 'Se necesita Python 3 nativo de Windows para el medidor.' >&2; exit 1; }

DIR=$(mktemp -d "$PWD/pruebas_bf.XXXXXX")
echo "Compilando: $SOURCE"
gcc -std=c11 -O2 -Wall -Wextra "$SOURCE" -o "$DIR/solucion.exe"

cat > "$DIR/verificar.py" <<'PYTHON'
import ctypes as C
from ctypes import wintypes as W
import os
from pathlib import Path
import random
import re
import subprocess
import sys
import time

ROOT, BOX = map(Path, sys.argv[1:3])
EXE = ROOT / 'solucion.exe'
TIME_LIMIT = float(os.environ.get('TIME_LIMIT', '16'))
MEM_LIMIT = int(os.environ.get('MEM_MIB', '64')) * 1024**2
ORACLE_TIMEOUT = 180

class Memory(C.Structure):
    _fields_ = [('cb', W.DWORD), ('faults', W.DWORD)] + [
        (name, C.c_size_t) for name in (
            'peak_ws', 'ws', 'peak_paged', 'paged', 'peak_nonpaged',
            'nonpaged', 'pagefile', 'peak_commit', 'private')]

get_memory = C.WinDLL('psapi', use_last_error=True).GetProcessMemoryInfo
get_memory.argtypes = [W.HANDLE, C.POINTER(Memory), W.DWORD]
get_memory.restype = W.BOOL
get_times = C.WinDLL('kernel32', use_last_error=True).GetProcessTimes
get_times.argtypes = [W.HANDLE] + [C.POINTER(W.FILETIME)] * 4
get_times.restype = W.BOOL

def memory(handle):
    m = Memory()
    m.cb = C.sizeof(m)
    if not get_memory(handle, C.byref(m), m.cb):
        raise C.WinError(C.get_last_error())
    return m.peak_ws, m.peak_commit

def duration(handle):
    stamps = [W.FILETIME() for _ in range(4)]
    if not get_times(handle, *(C.byref(x) for x in stamps)):
        raise C.WinError(C.get_last_error())
    values = [(x.dwHighDateTime << 32) | x.dwLowDateTime for x in stamps]
    return (values[1] - values[0]) / 10_000_000

def execute(inp, out, err):
    with inp.open('rb') as fi, out.open('wb') as fo, err.open('wb') as fe:
        p = subprocess.Popen([str(EXE)], stdin=fi, stdout=fo, stderr=fe)
        start = time.perf_counter()
        handle = W.HANDLE(int(p._handle))
        reason = None
        peak_ws = peak_commit = 0
        try:
            while p.poll() is None:
                ws, commit = memory(handle)
                peak_ws, peak_commit = max(peak_ws, ws), max(peak_commit, commit)
                if max(peak_ws, peak_commit) > MEM_LIMIT:
                    reason = 'MEMORIA'
                elif time.perf_counter() - start > TIME_LIMIT:
                    reason = 'TIEMPO'
                if reason:
                    p.kill()
                    break
                time.sleep(0.005)
            p.wait()
            ws, commit = memory(handle)
            peak_ws, peak_commit = max(peak_ws, ws), max(peak_commit, commit)
            elapsed = duration(handle)
        finally:
            if p.poll() is None:
                p.kill()
                p.wait()
        if reason is None:
            if max(peak_ws, peak_commit) > MEM_LIMIT:
                reason = 'MEMORIA'
            elif elapsed > TIME_LIMIT:
                reason = 'TIEMPO'
            elif p.returncode != 0:
                reason = f'ERROR({p.returncode})'
        return reason, elapsed, peak_ws, peak_commit

def normalized(path):
    with path.open('rb') as f:
        data = f.read(4097)
    if len(data) > 4096:
        return None
    return data.replace(b'\r\n', b'\n').rstrip(b'\n')

passed = failed = 0
report = (ROOT / 'resultados.tsv').open('w', encoding='utf-8')
report.write('caso\treferencia\tbytes\tsegundos\tpico_ws_MiB\tpico_commit_MiB\testado\n')

def oracle_pairs(path):
    data = normalized(path)
    if data == b'SIN DATOS':
        return []
    if data is None or not data or len(data.splitlines()) > 3:
        raise RuntimeError(f'Salida no valida de la caja negra: {path}')
    pairs = []
    for row in data.splitlines():
        if not re.fullmatch(rb'[1-9][0-9]* [1-9][0-9]*', row):
            raise RuntimeError(f'La caja negra rechazo la prueba: {data!r}')
        pairs.append(tuple(map(int, row.split())))
    return pairs

def test(name, inp, expanded=None):
    global passed, failed
    expected = ROOT / f'{name}.esperado'
    actual = ROOT / f'{name}.obtenido'
    source = 'caja directa' if expanded is None else 'caja + ampliacion exacta'
    print(f'{name}: {source}...', end='', flush=True)
    if expanded is None:
        with inp.open('rb') as fi, expected.open('wb') as fo, (ROOT / f'{name}.caja.err').open('wb') as fe:
            oracle = subprocess.run([str(BOX)], stdin=fi, stdout=fo, stderr=fe,
                                    timeout=ORACLE_TIMEOUT)
        if oracle.returncode != 0:
            raise RuntimeError(f'La caja negra fallo en {name}.')
    else:
        expected.write_text(''.join(f'{p} {q}\n' for p, q in expanded) or 'SIN DATOS\n', encoding='ascii')
    pairs = oracle_pairs(expected)
    state, seconds, ws, commit = execute(inp, actual, ROOT / f'{name}.programa.err')
    if state is None:
        expected_data, actual_data = normalized(expected), normalized(actual)
        state = 'OK' if expected_data is not None and actual_data == expected_data else 'SALIDA INCORRECTA'
    passed += state == 'OK'
    failed += state != 'OK'
    print(f' {state:17} {seconds:7.3f} s | WS {ws/1024**2:6.2f} MiB | commit {commit/1024**2:6.2f} MiB')
    report.write(f'{name}\t{source}\t{inp.stat().st_size}\t{seconds:.6f}\t{ws/1024**2:.3f}\t{commit/1024**2:.3f}\t{state}\n')
    report.flush()
    if state != 'OK':
        print('  Entrada:', inp)
        print('  Esperado:', repr(normalized(expected)))
        print('  Obtenido:', repr(normalized(actual)))
    return pairs

def small(name, rows, dates='2026-03-01 2026-03-31', crlf=False, final=True):
    text = dates + '\n' + str(len(rows)) + '\n' + '\n'.join(rows)
    if final:
        text += '\n'
    if crlf:
        text = text.replace('\n', '\r\n')
    inp = ROOT / f'{name}.in'
    inp.write_bytes(text.encode('ascii'))
    return test(name, inp)

print(f'Limites por prueba: {TIME_LIMIT:g} s, {MEM_LIMIT/1024**2:g} MiB. Carpeta: {ROOT}')
for name in ('ejemplo1', 'ejemplo2'):
    original = BOX.parent / f'{name}.in'
    if original.exists():
        inp = ROOT / f'{name}.in'
        inp.write_bytes(original.read_bytes())
        test(name, inp)

small('vacio', [])
small('duplicados_globales', [
    '2026-02-28,1,1,9', '2026-03-01,1,2,10',
    '2026-02-30,2,3,8', '2026-03-31,2,2,7'])
small('netos_no_positivos', [
    '2026-03-01,1,1,7', '2026-03-02,2,1,-7',
    '2026-03-03,3,2,-4', '2026-03-04,4,3,2', '2026-03-05,5,3,-5'])
small('empates', [f'2026-03-01,{i},{p},8' for i, p in enumerate([5,3,1,4,2], 1)])
small('fechas', [
    '1999-12-31,1,9,9', '2000-02-29,1,1,5', '2000-02-30,2,2,9',
    '2000-03-01,2,2,4', '2099-12-31,3,3,3', '2100-01-01,4,4,10',
    '2026-02-29,5,5,10', '2024-02-29,5,5,2'], '1999-01-01 2100-12-31')
small('cantidades', [
    '2026-03-01,1,1,0', '2026-03-01,1,2,10000',
    '2026-03-01,2,3,10001', '2026-03-01,2,2,-10000',
    '2026-03-01,3,3,-10001', '2026-03-01,3,4,1'])
small('formato_limites', [
    '2026-03-01,4000001,1,9', '2026-03-01,1,100001,9',
    '2026-03-01,+1,1,9', '2026-03-01,1,1, 9', '2026-03-01,1,1,9,0',
    '2026-03-01,0000000000001,1,9', '2026-03-01,000000000001,0001,0008',
    '2026-03-01,4000000,100000,10', '2026-03-01,0,1,9', '2026-03-01,2,0,9',
    '2026-03-01,3,2,+9', '2026-03-01,3,2,-000000000001'])
small('crlf_sin_salto_final', ['', '2026-03-01,1,1,3',
    '2026-03-31,2,2,4', '2026-04-01,3,3,9'],
    dates='  2026-03-01   2026-03-31  ', crlf=True, final=False)
small('linea_invalida_larga', ['x' * (2**20 + 17), '2026-03-01,1,1,7'])

rng = random.Random(731)
for case in range(1, 11):
    rows = []
    for _ in range(300):
        fields = [rng.choice(['2026-03-01','2026-03-31','2026-02-28',
                              '2026-04-01','2026-02-30']),
                  str(rng.randint(1, 250)), str(rng.randint(1, 30)),
                  str(rng.choice([rng.randint(-10000,10000),0,10001,-10001]))]
        kind = rng.randrange(12)
        if kind == 0:
            fields[rng.randint(1,3)] = '0' * rng.randint(1,14) + '1'
        elif kind == 1:
            fields[rng.randint(0,3)] += ' '
        elif kind == 2:
            fields.append('1')
        elif kind == 3:
            fields[rng.randint(1,3)] = ''
        rows.append(','.join(fields))
    small(f'aleatorio_{case:02}', rows, crlf=(case % 2 == 0), final=(case % 3 != 0))

N = 3_000_000
COPIES = 10000
for kind in ('suma_64_bits', 'productos_distintos', 'duplicados_invalidos'):
    base = []
    if kind == 'suma_64_bits':
        base = [('2026-03-01', j, 1, 10000) for j in range(1, 301)]
    elif kind == 'productos_distintos':
        for product in range(1, 101):
            for k, q in enumerate((10000, -10000, 10000)):
                sale = (product - 1) * 3 + k + 1
                if sale == 300:
                    sale = 400
                base.append(('2026-03-01', sale, product, q))
    else:
        for product in range(1, 101):
            sale = product if product < 100 else 400
            date = ['2026-02-30', '2026-02-28', '2026-03-01'][product % 3]
            base.extend([(date, sale, product*1000, 10000),
                         ('2026-03-01', sale, product*1000, 10000),
                         ('2026-03-31', sale, product*1000, -10000)])
    pairs = small('base_' + kind, [f'{d},{s},{p},{q}' for d, s, p, q in base])
    if kind == 'productos_distintos':
        # 1000 grupos de productos disjuntos, con diez copias cada uno.
        # Basta el top 3 de cada grupo para hallar el top 3 global.
        candidates = [(p + 100*g, q * (COPIES//1000))
                      for g in range(1000) for p, q in pairs]
        expected_pairs = sorted(candidates, key=lambda x: (-x[1], x[0]))[:3]
    else:
        expected_pairs = [(p, q * COPIES) for p, q in pairs]
    name = 'masivo_' + kind
    inp = ROOT / f'{name}.in'
    print(f'Generando {name}: {N:,} registros...', flush=True)
    with inp.open('wb', buffering=1024**2) as f:
        f.write(f'2026-03-01 2026-03-31\n{N}\n'.encode())
        written = 0
        for copy in range(COPIES):
            for date, sale, product, q in base:
                sale += copy * 400
                if kind == 'productos_distintos':
                    product += (copy % 1000) * 100
                written += 1
                ending = '\r\n' if kind == 'duplicados_invalidos' else '\n'
                if written == N:
                    ending = ''
                f.write(f'{date},{sale},{product},{q}{ending}'.encode('ascii'))
    print(f'  Tamano: {inp.stat().st_size/1_000_000:.2f} MB', flush=True)
    test(name, inp, expanded=expected_pairs)

report.close()
print(f'\nRESULTADO: {passed} OK; {failed} fallos.')
print('Entradas, salidas, errores y resultados.tsv conservados en:', ROOT)
sys.exit(1 if failed else 0)
PYTHON

MSYS2_ARG_CONV_EXCL='*' "${PY[@]}" -u \
    "$(cygpath -w "$DIR/verificar.py")" \
    "$(cygpath -w "$DIR")" \
    "$(cygpath -w "$BOX")"
