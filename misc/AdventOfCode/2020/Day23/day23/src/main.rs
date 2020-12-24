struct Deck {
    start: usize,
    next: Vec<usize>,
}

impl Deck {
    fn debug(&self) {
        let sz = self.next.len() - 1;
        let mut cur = self.start;
        for _ in 0..sz {
            print!("{} ",cur);
            cur = self.next[cur];
        }
        println!("");
    }

    fn find_2(&self) {
        let mut cur = self.start;
        while cur != 1 {
            cur = self.next[cur];
        }
        let a = self.next[cur];
        let b = self.next[a];
        println!("{} {}: {}",a,b,(a as u64) * (b as u64));
    }
}

fn make_deck(s: String, n: usize) -> Deck {
    let mut list : Vec<usize> = s.chars().map(|c| c.to_digit(10).unwrap() as usize).collect();
    if 10 <= n {
        for i in 10..=n {
            list.push(i);
        }
    }
    let sz = list.len();

    //println!("{:?}",list);
    let mut next : Vec<usize> = vec![0; sz+1];
    for i in 0..sz {
        next[list[i]] = list[(i+1)%sz];
    }
    /*
    for i in 1..sz {
        println!("{}: {}",i,next[i]);
    }
    */
    Deck {
        start: list[0],
        next: next,
    }
}

fn main() {
    let n = 1000000;
    let iter = 10000000;
    //let n = 9;
    //let iter = 10;
    let s = String::from("685974213");
    let mut deck = make_deck(s,n);
    for _ in 0..iter {
        //deck.debug();

        let cur = deck.start;
        let a = deck.next[cur];
        let b = deck.next[a];
        let c = deck.next[b];

        let ncur = deck.next[c];
        deck.next[cur] = ncur;
        deck.start = ncur;

        let mut place = cur-1;
        if place < 1 { place = n };
        while place == a || place == b || place == c {
            place -= 1;
            if place < 1 { place = n };
        }
        //println!("next: {}",place);

        let save = deck.next[place];
        deck.next[place] = a;
        deck.next[c] = save;
    }
    deck.find_2();
}
