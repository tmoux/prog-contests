// l       v     r
// T T T T F F F F
template <class Integer, class F>
Integer find_first_false(Integer l, Integer r, F &&f) {
  return *ranges::partition_point(ranges::views::iota(l, r), f);
}
