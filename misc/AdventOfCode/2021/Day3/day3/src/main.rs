use std::io::{self, BufRead};



fn main() {
    let stdin = io::stdin();
    let mut bits: Vec<Vec<bool>> = vec![];
    for line in stdin.lock().lines() {
        let bitstring: Vec<bool> = line.unwrap().chars().map(|c| c == '1').collect();
        bits.push(bitstring)
    }
    println!("{:?}", bits)
}
