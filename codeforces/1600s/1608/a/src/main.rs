#![allow(unused)]

use std::io::{self, prelude::*};

mod cp_io;
use cp_io::*;

fn solve<R: BufRead, W: Write>(scan: &mut Scanner<R>, w: &mut W) {
    let n = scan.token::<usize>();
    let a: Vec<usize> = (1..=n).map(|x| 2*x + 1).collect();
    for i in 0..n {
        write!(w, "{} ", a[i]);
    }
    writeln!(w,"");
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
