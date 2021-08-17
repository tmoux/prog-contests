predicate valid(a: int, b: int, n: int) {
    a + 2*b == n
}

function abs(x: int): int {
    if x < 0 then -x else x
}

predicate minimal(a: int, b: int, n: int) {
    !(exists c, d :: valid(c, d, n) && abs(c-d) < abs(a-b))
}

method get_coins(n: int) returns (a: int, b: int)
    ensures valid(a, b, n)
    ensures minimal(a, b, n)
{
    if n % 3 == 0 {
        a := n/3;
        b := n/3;
    }
    else if n % 3 == 1 {
        a := n/3+1;
        b := n/3;
    }
    else {
        assert(n % 3 == 2);
        a := n/3;
        b := n/3+1;
    }
}