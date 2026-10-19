# Benchmark: C vs Rust vs Python

Código e resultados brutos do estudo comparativo de tempo de resposta entre C, Rust e Python (trabalho acadêmico).

## Cargas de trabalho

| Carga | Parâmetro | O que mede |
| --- | --- | --- |
| Fibonacci recursivo | fib(32) | custo de chamadas de função |
| Crivo de Eratóstenes | n = 5.000.000 | acesso a memória |
| Multiplicação de matrizes | 200 × 200, `double` | aritmética de ponto flutuante |

Também são medidos o tempo de inicialização (50 execuções de um programa que só imprime "ok") e o pico de memória (RSS, via `/usr/bin/time`).

## Resultados (mediana de 10 execuções, ms)

| Carga | C | Rust | Python | Python / C | Rust / C |
| --- | ---: | ---: | ---: | ---: | ---: |
| Fibonacci | 2,75 | 4,05 | 192,89 | 70× | 1,47× |
| Crivo | 5,33 | 6,94 | 357,21 | 67× | 1,30× |
| Matrizes | 1,88 | 2,36 | 250,47 | 133× | 1,26× |

| Métrica | C | Rust | Python |
| --- | ---: | ---: | ---: |
| Inicialização (ms) | 2,54 | 5,52 | 17,15 |
| Executável (KB) | 16 | 4.470 | – |

Ambiente: Docker `rust:1-slim-trixie` (Debian 13) sobre WSL 2, AMD Ryzen 7 5700X; GCC 14.2.0 `-O2`, rustc 1.99.1 `-C opt-level=3`, CPython 3.13.5. Saídas brutas em [`resultados/`](resultados/).

## Como reproduzir

Com Docker instalado, na pasta do repositório:

```bash
docker run --rm -v "$PWD:/b" rust:1-slim-trixie bash /b/run.sh
```

O script instala Python, compila os programas em C e Rust, roda todos os testes e grava os arquivos `kernels.txt`, `mem.txt`, `startup.txt` e `size.txt`.

Para rodar uma carga isoladamente: `./c_bin fib 10`, `./rs_bin sieve 10` ou `python3 bench.py matmul 10` (carga e número de repetições).
