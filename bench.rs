use std::time::Instant;
fn fib(n: u32) -> u64 { if n < 2 { n as u64 } else { fib(n - 1) + fib(n - 2) } }
fn sieve(n: usize) -> u64 {
    let mut s = vec![true; n + 1]; s[0] = false; s[1] = false;
    let mut i = 2; while i * i <= n { if s[i] { let mut j = i * i; while j <= n { s[j] = false; j += i; } } i += 1; }
    s.iter().filter(|&&b| b).count() as u64
}
fn matmul(n: usize) -> f64 {
    let mut a = vec![0.0f64; n * n]; let mut b = vec![0.0f64; n * n]; let mut c = vec![0.0f64; n * n];
    for i in 0..n { for j in 0..n { a[i*n+j] = ((i+j)%7) as f64; b[i*n+j] = ((i*j)%5) as f64; } }
    for i in 0..n { for k in 0..n { let x = a[i*n+k]; for j in 0..n { c[i*n+j] += x * b[k*n+j]; } } }
    c.iter().sum()
}
fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 { println!("ok"); return; }
    let reps: usize = args[2].parse().unwrap();
    for _ in 0..reps {
        let t0 = Instant::now();
        let res = match args[1].as_str() { "fib" => fib(32) as f64, "sieve" => sieve(5_000_000) as f64, _ => matmul(200) };
        println!("{} {:.6} {:.0}", args[1], t0.elapsed().as_secs_f64(), res);
    }
}
