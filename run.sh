set -e
cd /b
apt-get update -qq >/dev/null && apt-get install -y -qq python3 time >/dev/null
echo "== versions"; gcc --version|head -1; rustc --version; python3 --version; nproc; grep -m1 "model name" /proc/cpuinfo
gcc -O2 -o c_bin bench.c
rustc -C opt-level=3 -o rs_bin bench.rs
R=10
for w in fib sieve matmul; do ./c_bin $w $R; ./rs_bin $w $R; python3 bench.py $w $R; done > kernels.txt
echo "== mem"
for w in fib sieve matmul; do for p in "./c_bin" "./rs_bin" "python3 bench.py"; do
  m=$( { /usr/bin/time -f "%M" $p $w 1 >/dev/null; } 2>&1 ); echo "$w|$p|$m"; done; done | tee mem.txt
echo "== startup"
python3 - <<'PY' | tee startup.txt
import subprocess,time,statistics
for name,cmd in [("C",["./c_bin"]),("Rust",["./rs_bin"]),("Python",["python3","bench.py"])]:
    ts=[]
    for _ in range(50):
        t=time.perf_counter(); subprocess.run(cmd,stdout=subprocess.DEVNULL); ts.append((time.perf_counter()-t)*1000)
    print(name, f"{statistics.median(ts):.2f}", f"{min(ts):.2f}", f"{max(ts):.2f}")
PY
ls -l c_bin rs_bin | awk '{print $5, $9}' | tee size.txt
