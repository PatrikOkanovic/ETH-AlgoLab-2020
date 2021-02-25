#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

void test_case(int n) {
  long x, y, a, b;
  std::cin >> x >> y >> a >> b;
  K::Point_2 first(x, y);
  K::Point_2 second(a, b);
  K::Ray_2 ray(first, second);
  bool hit = false;

  for (int i = 0; i < n; ++i) {
    long r, s, t, u;
    std::cin >> r >> s >> t >> u;
    K::Point_2 start(r, s);
    K::Point_2 end(t, u);
    K::Segment_2 segment(start, end);
    if (hit) continue;
    if (CGAL::do_intersect(ray, segment)) hit = true;
  }

  std::cout << (hit ? "yes\n" : "no\n");
}

int main() {
  std::ios_base::sync_with_stdio(false);

  while (true) {
    int n;
    std::cin >> n;
    if (n == 0) break;
    test_case(n);
  }

  return 0;
}
