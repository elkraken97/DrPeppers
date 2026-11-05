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