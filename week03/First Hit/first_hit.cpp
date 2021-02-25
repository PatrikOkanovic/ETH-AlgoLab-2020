#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

long floor_to_double(const K::FT &x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a + 1 <= x) a += 1;
  return std::lround(a);
}

void update(K::Ray_2 &ray, K::Point_2 &nearest_intersection,
            const K::Point_2 &intersection, bool &found, K::FT &min_distance,
            K::Segment_2 &s) {
  K::FT new_distance = CGAL::squared_distance(ray.source(), intersection);
  if (!found || new_distance < min_distance) {
    min_distance = new_distance;
    found = true;
    nearest_intersection = intersection;
    s = K::Segment_2(ray.source(), intersection);
  }
}

void update2(K::Segment_2 &s, K::Point_2 &nearest_intersection,
             const K::Point_2 &intersection, bool &found, K::FT &min_distance) {
  K::FT new_distance = CGAL::squared_distance(s.source(), intersection);
  if (!found || new_distance < min_distance) {
    min_distance = new_distance;
    found = true;
    nearest_intersection = intersection;
    s = K::Segment_2(s.source(), intersection);
  }
}

void test_case(int n) {
  long x, y, a, b;
  std::cin >> x >> y >> a >> b;
  K::Point_2 first(x, y);
  K::Point_2 second(a, b);
  K::Ray_2 ray(first, second);
  bool hit = false;
  K::FT min_distance;
  K::Point_2 p;
  std::vector<K::Segment_2> segments;

  for (int i = 0; i < n; ++i) {
    long r, s, t, u;
    std::cin >> r >> s >> t >> u;
    const K::Point_2 start(r, s);
    const K::Point_2 end(t, u);
    K::Segment_2 segment(start, end);
    segments.push_back(segment);
  }

  std::random_shuffle(segments.begin(), segments.end());
  K::Segment_2 s;
  for (auto &segment : segments) {
    if (!hit) {
      if (CGAL::do_intersect(ray, segment)) {
        auto o = CGAL::intersection(ray, segment);
        if (const K::Point_2 *op = boost::get<K::Point_2>(&*o)) {
          update(ray, p, *op, hit, min_distance, s);

        } else {  // segment intersection
          update(ray, p, segment[0], hit, min_distance, s);
          update(ray, p, segment[1], hit, min_distance, s);
        }
      }
    } else {
      if (CGAL::do_intersect(s, segment)) {
        auto o = CGAL::intersection(ray, segment);
        if (const K::Point_2 *op = boost::get<K::Point_2>(&*o)) {
          update2(s, p, *op, hit, min_distance);

        } else {  // segment intersection
          update2(s, p, segment[0], hit, min_distance);
          update2(s, p, segment[1], hit, min_distance);
        }
      }
    }
  }

  if (!hit)
    std::cout << "no\n";
  else
    std::cout << floor_to_double(p.x()) << " " << floor_to_double(p.y())
              << "\n";
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

