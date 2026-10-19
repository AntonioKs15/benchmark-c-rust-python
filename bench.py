import sys, time
def fib(n): return n if n < 2 else fib(n-1) + fib(n-2)
def sieve(n):
    s = bytearray([1])*(n+1); s[0]=s[1]=0
    i = 2
    while i*i <= n:
        if s[i]:
            for j in range(i*i, n+1, i): s[j] = 0
        i += 1
    return sum(s)
def matmul(n):
    a=[[float((i+j)%7) for j in range(n)] for i in range(n)]
    b=[[float((i*j)%5) for j in range(n)] for i in range(n)]
    c=[[0.0]*n for _ in range(n)]
    for i in range(n):
        ci=c[i]; ai=a[i]
        for k in range(n):
            x=ai[k]; bk=b[k]
            for j in range(n): ci[j]+=x*bk[j]
    return sum(map(sum,c))
if len(sys.argv)<2: print("ok"); sys.exit()
w, reps = sys.argv[1], int(sys.argv[2])
f = {"fib": lambda: fib(32), "sieve": lambda: sieve(5_000_000), "matmul": lambda: matmul(200)}[w]
for _ in range(reps):
    t0=time.perf_counter(); r=f(); print(f"{w} {time.perf_counter()-t0:.6f} {r:.0f}")
