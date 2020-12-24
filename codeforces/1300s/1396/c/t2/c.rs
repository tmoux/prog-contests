//Not mine!
//Taken from EbTech https://codeforces.com/contest/1396/submission/91419911

#![allow(dead_code)]
#![allow(unused)]

#![allow(unused_imports)]
use std::collections::{HashSet, HashMap};
use std::cmp::{min,max,Reverse};
use std::io::{self, prelude::*};
use std::str;
 
struct Scanner<R> {
    reader: R,
    buf_str: Vec<u8>,
    buf_iter: str::SplitWhitespace<'static>,
}
impl<R: BufRead> Scanner<R> {
    fn new(reader: R) -> Self {
        Self { reader, buf_str: vec![], buf_iter: "".split_whitespace() }
    }
    fn token<T: str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader.read_until(b'\n', &mut self.buf_str).expect("Failed read");
            self.buf_iter = unsafe {
                let slice = str::from_utf8_unchecked(&self.buf_str);
                std::mem::transmute(slice.split_whitespace())
            }
        }
    }
}
 
fn solve<R: BufRead, W: Write>(scan: &mut Scanner<R>, w: &mut W) {
    let n = scan.token::<usize>();
    let r1 = scan.token::<i64>();
    let r2 = scan.token::<i64>();
    let r3 = scan.token::<i64>();
    let d = scan.token::<i64>();
    let a: Vec<i64> = (0..n).map(|_| scan.token()).collect();

    let mut dp = vec![0];
    for i in 1..=n {
        let mut val = dp[i-1] + d + a[i-1] * r1 + r3;
        val = min(val, dp[i-1] + 3*d + min(r2, (a[i-1]+1)*r1) + r1);
        if i > 1 {
            val = min(val, dp[i-2] + 4*d + min(r2, (a[i-2]+1)*r1) + min(r2, (a[i-1]+1)*r1) + 2*r1);
            if i == n {
                val = min(val, dp[i-2] + 3*d + min(r2, (a[i-2]+1)*r1) + (a[i-1]+1)*r1 + r3);
            }
        }
        dp.push(val);
        //writeln!(w, "{} {}", i, dp[i] - d).ok();
    }

    writeln!(w, "{}", dp[n] - d).ok();
}
 
fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut scan = Scanner::new(stdin.lock());
    let mut out = io::BufWriter::new(stdout.lock());
    solve(&mut scan, &mut out);
}
