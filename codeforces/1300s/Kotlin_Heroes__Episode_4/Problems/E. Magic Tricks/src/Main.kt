import java.util.*
import kotlin.collections.ArrayDeque
import kotlin.math.min

private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles

const val INF = 2000000000

fun main() {
    val (n, m, k) = readInts()
    val moves = Array(n) { INF }

    moves[k-1] = 0
    for (t in 1..m) {
        var (x, y) = readInts()
        x--
        y--

        val xt = moves[x]
        val yt = moves[y]

        if (moves[x] == INF) moves[x] = yt
        else moves[x] = min(yt, moves[x] + 1)

        if (moves[y] == INF) moves[y] = xt
        else moves[y] = min(xt, moves[y] + 1)
    }

    val ans = moves.map { i -> if (i == INF) -1 else i }
    println(ans.joinToString(" "))
}