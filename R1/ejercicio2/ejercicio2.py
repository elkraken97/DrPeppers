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