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
    let mut x = scan.token::<i32>();
    if x > 45 {
        writeln!(w,"-1");
    }
    else {
        let mut v: Vec<i32> = Vec::new();
        for i in (1..10).rev() {
            if x >= i {
                x -= i;
                v.push(i);
            }
        }
        for i in v.iter().rev() {
            write!(w,"{}",i);
        }
        writeln!(w,"");
    }
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
