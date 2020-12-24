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

fn vec_equal(a: &Vec<i32>, b: &Vec<i32>) -> bool {
    a.len() == b.len() 
        && a.iter().zip(b.iter()).filter(|&(a,b)| a == b).count() == a.len()
}

fn check(a: i32, b: i32, c: i32, vec: &Vec<i32>) -> bool {
    let mut v = vec![a,b,c,a+b,b+c,a+c,a+b+c];
    v.sort();
    vec_equal(&v,vec)
}
 
fn solve<R: BufRead, W: Write>(scan: &mut Scanner<R>, w: &mut W) {
    let n = 7;
    let mut a: Vec<i32> = (0..n).map(|_| scan.token()).collect();
    a.sort();
    for i in 0..n-2 {
        for j in i+1..n-1 {
            for k in j+1..n {
                if check(a[i],a[j],a[k],&a) {
                    writeln!(w,"{} {} {}",a[i],a[j],a[k]);
                    return;
                }
            }
        }
    }
}
 
fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut scan = Scanner::new(stdin.lock());
    let mut out = io::BufWriter::new(stdout.lock());
    solve(&mut scan, &mut out);
}
