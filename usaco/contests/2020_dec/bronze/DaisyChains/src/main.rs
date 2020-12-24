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
    let n = scan.token();
    let mut a: Vec<i32> = (0..n).map(|_| scan.token()).collect();
    for i in 1..n {
        a[i] += a[i-1];
    }
    let mut ans = 0;
    for i in 0..n {
        for j in i..n {
            let sum = a[j] - (if i == 0 { 0 } else { a[i-1] });
            let len = j-i+1;
            let found = (i..=j).any(|k| (if k == 0 { a[k] } else { a[k]-a[k-1] })*(len as i32) == sum);
            if found {
                ans += 1;
            }
        }
    }
    writeln!(w,"{}",ans);
}
 
fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut scan = Scanner::new(stdin.lock());
    let mut out = io::BufWriter::new(stdout.lock());
    solve(&mut scan, &mut out);
}
