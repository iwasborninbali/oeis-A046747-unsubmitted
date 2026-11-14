# Independent verification — A046747 (2026-11-15)

Scope: repository `iwasborninbali/oeis-A046747-unsubmitted`, supplied archive at commit `6e693d3` (full GitHub SHA `6e693d3399cf7a8da013397ff10419847d2217b2`). Read `README.md`, `CERTIFICATE.md`, `PRIOR-ART.md`; the supplied archive contains no `verification/` directory or earlier verification files. This audit is independent of the lab's certificate and does not claim to reproduce the preprint's proof.

## Claim

**Exact CERTIFICATE.md claim:** “Hu, Song and Wu's Corollary 1.2 gives the singularity asymptotic conjectured in A046747.”

## Source check

**Primary source:** Xuanang Hu, Zeyan Song and Xinglong Wu, *Sharp singularity asymptotics for discrete random matrices*, [arXiv:2609.39463v2](https://arxiv.org/abs/2609.39463), revised 16 October 2026; [author's full text](https://arxiv.org/html/2609.39463).

**Exact location:** Section 1, **Corollary 1.2**, in the paragraph directly after its Rademacher (`{-1,1}`) formula, beginning “For independent uniform `{0,1}` entries, the corresponding formula is”. The displayed assertion is

\[\Pr(M_n\text{ is singular})=(1+o_n(1))n^2 2^{-n}.\]

Corollary 1.2 also gives `Pr(M_n singular) = a_n(S) + O_{S,epsilon}(n^(1+epsilon) q^(-n)) = (1+o(1)) a_n(S)` for `0 < epsilon < 1`. The paper defines `M_n` as an `n x n` matrix with **independent uniform entries in a fixed finite set** `S subset R` of cardinality `q >= 2`; here `S={0,1}`, `q=2`. In Section 5, **the final displayed calculation in the proof of Corollary 1.2** reads `a_n({0,1}) = (n^2+n)2^(-n) + n(n-1)4^(-n)`. The paper's `a_n(S)` is a probability sum over elementary singularity events, **not** OEIS's integer count `a(n)`.

**Matching conventions:** A046747 counts all singular `n x n` matrices with entries `{0,1}` over the rationals, offset **1**; its `%O` record is `1,2`. Singularity of a rational-entry matrix is identical over `Q` and `R` (the determinant is an integer). All `2^(n^2)` binary matrices are equally likely under the source's independence/uniformity assumption, so `Pr(singular)=A046747(n)/2^(n^2)`. The entry's conjectured leading term is `binomial(n+1,2)*(1/2)^(n-1) = n(n+1)2^(-n)`. Dividing the paper's `n^2 2^(-n)` by this gives `n/(n+1) -> 1`. Thus the source **supports the claimed asymptotic exactly**, though it does not assert equality to that leading term at finite `n`. This checks the *published statement*, not the correctness of its long proof.

## Independent computation

**Program:** [`count_singular.cpp`](count_singular.cpp), newly written here without importing OEIS code. For each `1 <= n <= 6`, enumerate distinct `n`-element subsets of the `2^n` possible binary rows in increasing order. A full-rank subset contributes `n!` nonsingular ordered matrices. Test linear independence incrementally over `F_1009`, pruning dependent prefixes. For `n <= 6`, every square `0/1` minor has `|det| <= n! <= 720 < 1009` by the Leibniz formula; therefore modular zero/nonzero tests are **exactly equivalent** to rational tests. Subtract the nonsingular count from `2^(n^2)`. The OEIS comparison numbers are read from the indexed A046747 `%S/%T` records, not derived from the source's theorem.

Build/run from this directory: `g++ -O3 -std=c++17 -Wall -Wextra -pedantic count_singular.cpp -o count_singular && ./count_singular`. The exact run is captured in [`output.log`](output.log).

| n | Independently computed A046747(n) | OEIS A046747(n) | Result |
|---:|---:|---:|:---|
| 1 | 1 | 1 | PASS |
| 2 | 10 | 10 | PASS |
| 3 | 338 | 338 | PASS |
| 4 | 42976 | 42976 | PASS |
| 5 | 21040112 | 21040112 | PASS |
| 6 | 39882864736 | 39882864736 | PASS |

**Runtime:** measured on the local verification container with `g++ -O3`: 3.72 seconds wall, 3.71 seconds user CPU (six values total), 1536 KB peak RSS, as recorded by `/usr/bin/time`; 64,074,018 row-prefix candidates considered for `n=6`. The finite-value check does not prove an `n -> infinity` asymptotic.

**SHA-256 (exact local program and run log, before upload):**

- `count_singular.cpp`: `ac3c3512e8b968175e89078aabef2740556bb320081feba7fcc9f9147756a8e6`
- `output.log`: `b0aed669890b1385675b724e77f4c482860288d065065551925fc6134a5b7b02`

## Entry check

**A046747:** The [OEIS entry](https://oeis.org/A046747) and [internal format](https://oeis.org/A046747/internal), available through search-engine-indexed OEIS text, show `#67` (`%I` timestamp **2026-07-02**), `%O 1,2`, the six counts above, and the `%F` sentence describing the `n(n+1)2^(-n)` singularity asymptotic as **conjectured** (with a 2007 correction). The indexed `%H` references do **not** list Hu–Song–Wu, and no line describes their proof. However, this A046747 snapshot was indexed approximately two months before this audit, so it is **not proof of the current 2026-11-15 state**.

**Access limit:** Direct attempts to open live `https://oeis.org/A046747`, `/internal`, and `/history` and `https://oeis.org/history?seq=A046747` were blocked (HTTP 403 or inaccessible via the retrieval interface). Therefore the **live revision history, post-crawl updates and pending edits were not inspected**. The newness of a *direct A046747 edit today* is **not established** and must be rechecked before submitting to OEIS.

**Significant prior art within OEIS:** [A057982/internal](https://oeis.org/A057982/internal), indexed with `%I` timestamp **2026-10-16**, **already cites Hu–Song–Wu, arXiv:2609.39463, Corollary 1.2** in `%H`, and gives `Pr(random n x n {-1,1} matrix singular) = (2+o(1)) n^2 2^(-n)` in `%F` (credit to David Radcliffe, 15 October 2026). Its `%C` says `A057982(m) = 2^(2m-1) * A046747(m-1)`. Dividing by the respective totals `2^(m^2)` and `2^((m-1)^2)` yields the **exact** identity between singularity probabilities `p_{±1}(m) = p_{0,1}(m-1)`. Hence A057982 already carries both the **same source** and an **equivalent sharp asymptotic**; the scientific result and reference are **not new to OEIS as a whole**, even though missing from the retrieved A046747 record.

**Other literature/newer source:** The same [arXiv abstract](https://arxiv.org/abs/2609.39463) identifies v2 (16 October 2026) as the latest revision found. [Bogdan Grechuk, “The singularity conjecture is proved,” 12 October 2026](https://functor.network/user/3333/entry/2008), is secondary commentary and is already cited by A057982. Earlier Tikhomirov work proved the sharp exponential rate, not this polynomial leading factor; Jain–Sah–Sawhney covered nonuniform finitely supported distributions. No newer peer-reviewed publication or superior primary source was found in searches performed on 15 November 2026; this is a search limit, not proof of nonexistence.

## Verdict

**PARTIAL (novelty unestablished; primary-source claim verified).** Corollary 1.2 explicitly and correctly **states** the `{0,1}` asymptotic relevant to A046747, with matching indexing and conventions; an exact independent finite calculation matches A046747 for `n=1..6`. The retrieved A046747 text lacks the citation and still calls the formula a conjecture, but the **live entry/history could not be opened**, so current absence cannot be certified. Moreover, equivalent content and the identical reference were placed in **A057982 by October 2026**, before this lab contribution. A direct A046747 correction may be editorially useful **if a live edit/history check confirms it remains absent**; it is not a new mathematical result or a first OEIS citation.
