#include <iostream>
#include <vector>
#include <cmath>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel EK;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SK;

typedef CGAL::Min_circle_2_traits_2<EK> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

typedef CGAL::Min_circle_2_traits_2<SK> Traits_Sqrt;
typedef CGAL::Min_circle_2<Traits_Sqrt> Min_circle_sqrt;

double ceil_to_double(const SK::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a - 1 >= x) a -= 1;
  return a;
}

double floor_to_double(const EK::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a + 1 <= x) a += 1;
  return a;
}

void test_case(int n) {
  std::vector<EK::Point_2> p;

  for (int i = 0; i < n; i++) {
    long x, y;
    std::cin >> x >> y;
    p.push_back(EK::Point_2(x, y));
  }

  Min_circle mc(p.begin(), p.end(), true);
  Traits::Circle c = mc.circle();

  std::vector<SK::Point_2> sqrt_p;

  for (auto it = mc.support_points_begin(); it != mc.support_points_end();
       ++it) {
    sqrt_p.push_back(
        SK::Point_2(floor_to_double((*it).x()), floor_to_double((*it).y())));
  }

  Min_circle_sqrt mc_sqrt(sqrt_p.begin(), sqrt_p.end(), true);
  Traits_Sqrt::Circle c_sqrt = mc_sqrt.circle();

  std::cout << ceil_to_double(CGAL::sqrt(c_sqrt.squared_radius())) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  while (true) {
    int n;
    std::cin >> n;
    if (n == 0) break;
    test_case(n);
  }

  return 0;
}
