# OEIS A046747: reference for singularity asymptotics (not yet submitted)

<!-- oeis-status:begin -->
**OEIS status: not submitted** (lab registry, 15 Nov 2026).

- [A046747](https://oeis.org/A046747), Hu, Song and Wu, arXiv:2609.39463 (preprint): **candidate** (2026-11-13: repository built (core c6)). Certificate: complete.

Rules and the full registry: [athanor-oeis](https://github.com/iwasborninbali/athanor-oeis/blob/main/REGISTRY.md).
<!-- oeis-status:end -->

## Definition

a(n) counts n by n matrices with entries 0 or 1 and determinant zero over the rationals, for n≥1. The offset is 1.

## Terms / result

No term changes. The live [A046747](https://oeis.org/A046747), read 2026-11-13, states: `The probability that a random n X n {0,1}-matrix is singular is conjectured to be asymptotic to C(n+1, 2)*(1/2)^(n-1). [Corrected by _N. J. A. Sloane_, Jan 02 2007]` The preprint below establishes this asymptotic.

## How it was obtained

Xuanang Hu, Zeyan Song and Xinglong Wu, *Sharp singularity asymptotics for discrete random matrices*, preprint [arXiv:2609.39463v2](https://arxiv.org/abs/2609.39463), 16 October 2026, [doi:10.48550/arXiv.2609.39463](https://doi.org/10.48550/arXiv.2609.39463). Read 2026-11-13, [Corollary 1.2](https://arxiv.org/html/2609.39463): “For independent uniform {0,1} entries, the corresponding formula is” P(singular)=(1+o(1))n²2^(−n). Since C(n+1,2)2^(1−n)=n(n+1)2^(−n) is asymptotic to n²2^(−n), this matches the entry. The matrix probability equals a(n)/2^(n²).

## Verification

The source corollary and elementary equivalence of the leading terms were checked directly. The preprint's proof and the sequence's tabulated values were not reverified. See [CERTIFICATE.md](CERTIFICATE.md).

## Prior art and credit

The preprint is by Hu, Song and Wu; the conjecture and earlier literature are recorded in the entry. See [PRIOR-ART.md](PRIOR-ART.md).

## Reproduce

Open the preprint's Corollary 1.2 and compare its {0,1} formula with the entry; the check takes approximately five minutes. No paper is bundled.

## Provenance

Source: `projects/science/athanor-oeis`, commit `11b7ea9cc6f4c0057731d8e36c023f8b36e7c27f`, `tasks/2026-11-12-A046747-singular-01-matrices/answers/2026-11-12-chatgpt.md`.

## Author, licence

Aleksei Kudriashov (ORCID 0009-0006-8885-5338), Athanor lab, with AI assistance (OpenAI Codex cores; Claude Code as the lab's guide). Code: MIT; data and text: CC BY 4.0 (see LICENSE.md).
