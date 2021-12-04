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
    let m = scan.token::<usize>();
    let k = scan.token::<usize>();

    let mut right = vec![vec![0; m-1]; n];
    let mut down = vec![vec![0; m]; n-1];
    let mut len = vec![vec![vec![0; m]; n]];
    for i in 0..n {
        for j in 0..m-1 {
            right[i][j] = scan.token::<usize>();
        }
    }
    for i in 0..n-1 {
        for j in 0..m {
            down[i][j] = scan.token::<usize>();
        }
    }

    if k % 2 != 0 {
        for i in 0..n {
            for j in 0..m {
                write!(w, "-1 ").ok();
            }
            writeln!(w, "").ok();
        }
        return;
    }
    for kk in 1..=k/2 {
        len.push(vec![vec![1_000_000_000; m]; n]);
        for i in 0..n {
            for j in 0..m {
                if j > 0 {
                    len[kk][i][j] = min(len[kk][i][j], len[kk-1][i][j-1] + right[i][j-1]);
                }
                if i > 0 {
                    len[kk][i][j] = min(len[kk][i][j], len[kk-1][i-1][j] + down[i-1][j]);
                }
                if j < m-1 {
                    len[kk][i][j] = min(len[kk][i][j], len[kk-1][i][j+1] + right[i][j]);
                }
                if i < n-1 {
                    len[kk][i][j] = min(len[kk][i][j], len[kk-1][i+1][j] + down[i][j]);
                }
            }
        }
    }

    for i in 0..n {
        for j in 0..m {
            write!(w, "{} ", len[k/2][i][j] * 2).ok();
        }
        writeln!(w, "").ok();
    }
}
 
fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut scan = Scanner::new(stdin.lock());
    let mut out = io::BufWriter::new(stdout.lock());
    solve(&mut scan, &mut out);
}
