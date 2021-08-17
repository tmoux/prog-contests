private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles


fun main() {
    val tc = readInt()
    for (t in 1..tc) solve()
}

fun solve() {
    val (n, k1, k2) = readInts()
    val s = readLn()
    val ans = IntArray(n) { 0 }
    for (i in 0 until n) {
        if (s[i] == '1') {
            ans[i] = kotlin.math.min(k1, k2 - (if (i > 0) ans[i - 1] else 0))
        }
    }
    val tot = ans.sum()
    println(tot)
}
