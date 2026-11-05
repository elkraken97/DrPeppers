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