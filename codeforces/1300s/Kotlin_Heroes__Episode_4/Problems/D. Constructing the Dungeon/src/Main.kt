import kotlin.math.*

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
    repeat(tc) {
        solve()
    }
}

fun solve() {
    val (n, m) = readInts()
    val a = IntArray(n) { 0 }
    val edges = mutableListOf<Edge>()
    repeat(m) {
        val (v, u, w) = readInts()
        edges.add(Edge(v-1, u-1, w))
    }
    for (e in edges) {
        a[e.u] = max(a[e.u], e.w)
        a[e.v] = max(a[e.v], e.w)
    }

    val poss = edges.all { e -> min(a[e.u], a[e.v]) == e.w }
    if (poss) {
        println("YES")
        println(a.joinToString(" "))
    }
    else println("NO")
}

data class Edge(val v: Int, val u: Int, val w: Int)
