#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Face_handle Face_handle;

const K::FT INF(std::numeric_limits<long>::max());

using namespace std;

void test_case(int n) {
  std::vector<K::Point_2> pts;

  for (int i = 0; i < n; ++i) {
    double x, y;
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }

  Triangulation t;
  t.insert(pts.begin(), pts.end());

  std::priority_queue<std::pair<K::FT, Face_handle> > Q;

  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) {
    if (t.is_infinite(f)) {
      f->info() = INF;
      Q.emplace(INF, f);
    } else {
      f->info() = 0;
    }
  }

  while (!Q.empty()) {
    K::FT dist = Q.top().first;
    Face_handle f = Q.top().second;
    Q.pop();

    for (int i = 0; i < 3; ++i) {
      Face_handle neighbor = f->neighbor(i);
      // if (neighbor.is_infinite()) continue;

      K::FT gate = CGAL::squared_distance(f->vertex((i + 1) % 3)->point(),
                                          f->vertex((i + 2) % 3)->point());

      // K::FT gate2 = t.segment(f, i).squared_length();

      K::FT curr = std::min(gate, f->info());

      if (curr > neighbor->info()) {
        neighbor->info() = curr;
        Q.emplace(neighbor->info(), neighbor);
      }
    }
  }

  int m;
  cin >> m;

  for (int i = 0; i < m; ++i) {
    double x, y;
    double s;
    std::cin >> x >> y >> s;
    K::Point_2 p(x, y);

    K::FT d = s;

    Face_handle f = t.locate(p);
    K::Point_2 near_point = t.nearest_vertex(p, f)->point();

    if (CGAL::squared_distance(near_point, p) < d)
      std::cout << "n";
    else {
      if (4 * d <= f->info())
        std::cout << "y";
      else
        std::cout << "n";
    }
  }
  std::cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  while (true) {
    int n;
    cin >> n;
    if (n == 0) break;
    test_case(n);
  }

  return 0;
}
