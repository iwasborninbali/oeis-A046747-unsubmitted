// Independent enumeration of singular {0,1} n-by-n matrices, n=1..6.
// All code newly written for verification; no OEIS counting program is used.
// Build: g++ -O3 -std=c++17 -Wall -Wextra -pedantic count_singular.cpp -o count_singular
// Run:   ./count_singular
//
// An invertible matrix has n distinct nonzero rows. Enumerate all increasing
// n-element subsets of {0,1}^n. A set contributes n! nonsingular matrices
// if its rows are independent over Q, otherwise zero.
// Test independence in F_1009. For n<=6, the Leibniz formula gives
// |det| <= n! <= 720 < 1009, for every square {0,1} submatrix;
// hence determinant is 0 over Q iff it is 0 modulo 1009.
// Prefixes of independent rows can be extended; a dependent prefix cannot.

#include <array>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>

static constexpr int PRIME = 1009;
static constexpr int MAX_N = 6;

struct Enumerator {
    int n = 0;
    int row_limit = 0;
    int inv[PRIME]{};
    int basis[MAX_N][MAX_N]{};
    unsigned int pivots = 0;
    std::uint64_t good_sets = 0;
    std::uint64_t prefixes = 0;

    explicit Enumerator(int size) : n(size), row_limit(1 << size) {
        inv[1] = 1;
        for (int i = 2; i < PRIME; ++i) {
            inv[i] = PRIME - (PRIME / i) * inv[PRIME % i] % PRIME;
        }
    }

    // Returns the pivot column newly installed, or -1 for dependence.
    // Existing basis rows are not changed; restoring pivots undoes the insertion.
    int insert_row(int row_bits) {
        int v[MAX_N]{};
        for (int k = 0; k < n; ++k) v[k] = (row_bits >> k) & 1;
        for (int j = 0; j < n; ++j) {
            const int c = v[j];
            if (c == 0) continue;
            if ((pivots >> j) & 1U) {
                for (int k = j; k < n; ++k) {
                    int t = (v[k] - c * basis[j][k]) % PRIME;
                    if (t < 0) t += PRIME;
                    v[k] = t;
                }
            } else {
                const int factor = inv[c];
                for (int k = j; k < n; ++k) {
                    basis[j][k] = v[k] * factor % PRIME;
                }
                pivots |= 1U << j;
                return j;
            }
        }
        return -1;
    }

    void enumerate(int start, int depth) {
        if (depth == n) {
            ++good_sets;
            return;
        }
        const int last = row_limit - (n - depth);
        for (int row = start; row <= last; ++row) {
            ++prefixes;
            const int pivot = insert_row(row);
            if (pivot >= 0) {
                enumerate(row + 1, depth + 1);
                pivots &= ~(1U << pivot);
            }
        }
    }
};

int main() {
    constexpr std::uint64_t reference[MAX_N + 1] = {
        0, 1, 10, 338, 42976, 21040112, 39882864736ULL
    };
    std::cout << "method=distinct-row-subsets,exact-determinant-via-F_1009; modulo test exact for n<=6\n";
    std::cout << "OEIS_ref=https://oeis.org/A046747/internal; offset=1\n";
    std::cout << "n,independent_unordered_row_sets,nonsingular_ordered,singular,total,oeis,match,prefix_candidates,cpu_wall_seconds\n";
    bool all_match = true;
    for (int n = 1; n <= MAX_N; ++n) {
        auto start = std::chrono::steady_clock::now();
        Enumerator e(n);
        e.enumerate(0, 0);
        std::uint64_t factorial = 1;
        for (int k = 2; k <= n; ++k) factorial *= k;
        const std::uint64_t good = e.good_sets * factorial;
        const std::uint64_t total = 1ULL << (n * n);
        const std::uint64_t singular = total - good;
        const bool match = singular == reference[n];
        all_match &= match;
        const std::chrono::duration<double> elapsed =
            std::chrono::steady_clock::now() - start;
        std::cout << n << ',' << e.good_sets << ',' << good << ',' << singular
                  << ',' << total << ',' << reference[n] << ','
                  << (match ? "PASS" : "FAIL") << ',' << e.prefixes << ','
                  << std::fixed << std::setprecision(6) << elapsed.count() << '\n';
    }
    std::cout << "overall=" << (all_match ? "PASS" : "FAIL") << '\n';
    return all_match ? 0 : 1;
}
