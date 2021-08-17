private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles

fun solve() {
    val (n, k) = readInts()
    val n1 = n / (1 + k + k*k + k*k*k)
    val n2 = n1 * k
    val n3 = n2 * k
    val n4 = n3 * k
    assert(n1 + n2 + n3 + n4 == n)
    println("$n1 $n2 $n3 $n4")
}


fun main() {
    val tc = readInt()
    for (k in 1..tc) {
        solve()
    }
}