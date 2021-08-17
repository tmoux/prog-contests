import kotlin.math.min

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
    for (i in 0 until tc) solve()
}

fun solve() {
    val (n, k, x, y) = readInts()
    val a = readLongs().sortedDescending().toTypedArray()
    var sum = a.sum()
    val targetSum = n.toLong()*k.toLong()
    var ans = 0.toLong()

    for (i in 0 until n) {
        if (sum > targetSum) {
            sum -= a[i]
            a[i] = 0.toLong()
            ans += x
        }
        else break
    }
    val costToElim = a.count { it > k } * x
    val costToBalance = if (a.maxOrNull()!! > k) y else 0
    ans += min(costToElim, costToBalance)
    println(ans)
}
