#![allow(unused)]
use std::io::{self, prelude::*};
mod cp_io {
    use std::io::{self, prelude::*};
    use std::str;
    pub struct Scanner<R> {
        reader: R,
        buf_str: Vec<u8>,
        buf_iter: str::SplitWhitespace<'static>,
    }
    impl<R: BufRead> Scanner<R> {
        pub fn new(reader: R) -> Self {
            Self {
                reader,
                buf_str: vec![],
                buf_iter: "".split_whitespace(),
            }
        }
        pub fn token<T: str::FromStr>(&mut self) -> T {
            loop {
                if let Some(token) = self.buf_iter.next() {
                    return token.parse().ok().expect("Failed parse");
                }
                self.buf_str.clear();
                self.reader
                    .read_until(b'\n', &mut self.buf_str)
                    .expect("Failed read");
                self.buf_iter = unsafe {
                    let slice = str::from_utf8_unchecked(&self.buf_str);
                    std::mem::transmute(slice.split_whitespace())
                }
            }
        }
    }
}
use cp_io::*;
fn solve<R: BufRead, W: Write>(scan: &mut Scanner<R>, w: &mut W) {
    let n = scan.token::<usize>();
    let a: Vec<usize> = (1..=n).map(|x| 2 * x + 1).collect();
    for i in 0..n {
        write!(w, "{} ", a[i]);
    }
    writeln!(w, "");
}
fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut scan = Scanner::new(stdin.lock());
    let mut out = io::BufWriter::new(stdout.lock());
    let test_cases = scan.token::<usize>();
    for _ in 0..test_cases {
        solve(&mut scan, &mut out);
    }
}

