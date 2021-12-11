#![allow(unused)]

use std::io::{self, prelude::*};

mod cp_io;
use cp_io::*;

fn solve<R: BufRead, W: Write>(scan: &mut Scanner<R>, w: &mut W) {
    let n = scan.token::<usize>();
    let mut a: Vec<usize> = (0..n).map(|_| scan.token()).collect();
    a.sort();
    for i in 1..1+n/2 {
        writeln!(w, "{} {}", a[i], a[0]);
    }
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
