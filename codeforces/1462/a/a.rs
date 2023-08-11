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
    let a: Vec<i32> = (0..n).map(|_| scan.token()).collect();
    let mut ans: Vec<i32> = vec![0;n];
    for i in 0..n {
        if i % 2 == 0 {
            ans[i] = a[i/2];
        }
        else {
            ans[i] = a[n-1-i/2];
        }
    }
    for i in 0..n {
        write!(w,"{} ",ans[i]).ok();
    }
    write!(w,"\n").ok();
}
 
fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut scan = Scanner::new(stdin.lock());
    let mut out = io::BufWriter::new(stdout.lock());
    let t = scan.token::<usize>();
    for _ in 0..t {
        solve(&mut scan, &mut out);
    }
}
