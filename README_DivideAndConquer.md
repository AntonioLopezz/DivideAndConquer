# Divide and Conquer — Best Substring Match 🔍

Implementation and full empirical analysis of a Divide and Conquer algorithm in C++ to solve a character-matching problem between two strings. The project includes a theoretical complexity analysis using the Master Theorem, experimental validation, and regression-based contrast.

## 📋 Problem Statement

Given two strings `A` and `B` of the same length `n`, and a natural number `m ≤ n`, find the substring of `A` of size `m` that maximizes the number of character matches with `B` at the same positions (`A[i] == B[i]`). Return the starting index and the number of matches found.

**Example:** `n = 10`, `m = 5`
```
A = c d d a b c d a c c
B = c a c d d b c a d c
Solution: start = 5, matches = 2
```

## 🧠 Algorithms Implemented

Two approaches are implemented and compared:

**Iterative algorithm** — O(n·m): straightforward sliding window that checks every possible substring.

**Divide and Conquer algorithm** — scans left and right halves recursively and handles the border-crossing substrings in the combine step. Includes an early-exit optimization: if a perfect match of size `m` is found, execution stops immediately.

| Case | Complexity |
|------|-----------|
| Worst case | Θ(n) |
| Best case | Θ(log n) |

Complexity derived via the Master Theorem and validated experimentally.

## 📂 Project Structure

```
DivideAndConquer/
├── Programas C++/
│   ├── Practica1.h              # Function declarations
│   ├── Practica1.cpp            # Core algorithm implementation
│   ├── casos_Practica1.cpp      # Manual test cases
│   ├── test_oraculo.cpp         # Random oracle testing (compares both algorithms)
│   ├── tiempos.cpp              # Best/worst case timing measurements
│   └── Makefile                 # Build rules
├── Estudio experimental/
│   ├── regresion.py             # Regression fitting and plot generation
│   ├── resultados_tiempos.csv   # Timing data
│   ├── scatter_plot.pdf         # Empirical time scatter plot
│   ├── scatter_plot_log.pdf     # Scatter plot with logarithmic x-axis
│   ├── ajuste_peor.pdf          # Linear regression fit — worst case Θ(n)
│   ├── ajuste_peor_log.pdf      # Logarithmic regression fit — worst case
│   └── ajuste_mejor_log.pdf     # Logarithmic regression fit — best case
└── AEDII_DyV.pdf                # Full technical report
```

## 🛠️ Build & Run

```bash
cd "Programas C++"
make
```

Run the test cases:
```bash
./casos_Practica1
```

Run the oracle (random comparison of both algorithms):
```bash
./test_oraculo
```

Run the timing analysis:
```bash
./tiempos
```

Generate regression plots (requires Python + matplotlib + numpy):
```bash
cd "../Estudio experimental"
python regresion.py
```

## ✅ Validation

Two independent validation methods were used:

**Manual test cases** — cover edge situations: matches at the start, at the end, crossing the midpoint, zero matches, and the example from the problem statement.

**Oracle testing** — randomly generates string pairs for sizes `n = 10, 20, 50, 150, 300` and verifies that both the iterative and DyV algorithms return identical results.

## 📊 Experimental Analysis

Input sizes follow a multiplicative spacing `nᵢ = 1000 · 2ⁱ` for `i = 0..10`, reaching up to `n = 1,024,000`. Each size was measured 10 times and the median was taken to reduce system noise.

- **Worst case** (strings with no matches): linear growth confirmed. Regression coefficient R² = 0.9983.
- **Best case** (identical strings, perfect match found immediately): execution time is so small it approaches the clock resolution of `std::chrono`, which validates the Θ(log n) complexity empirically.

## 🔧 Technologies

- C++17
- Python 3 (numpy, matplotlib, scipy)
- Make
