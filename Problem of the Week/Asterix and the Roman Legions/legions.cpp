#include <iostream>
#include <cmath>
#include <algorithm>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> SolT;

double floor_to_double(const SolT &x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

IT l_sign(IT a, IT b, IT c, IT x, IT y) {
  if(a*x + b*y + c >= 0) return 1;
  return -1;
}

void test_case() {
  IT xs, ys, n;
  std::cin >> xs >> ys >> n;
  
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  const int time = 0, px = 1, py = 2;
  for(int i = 0; i < n; ++i) {
    IT a, b, c, v;
    std::cin >> a >> b >> c >> v;
    IT sign = l_sign(a, b, c, xs, ys);
    IT denominator = std::sqrt(std::pow(a, 2) + std::pow(b, 2));
    
    lp.set_a(time, i, v*denominator);
    lp.set_a(px, i, -a*sign);
    lp.set_a(py, i, -b*sign);
    lp.set_b(i, c*sign);
  }
  lp.set_l(time, true, 0);
  lp.set_c(time, -1);
  lp.set_c0(0);
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  std::cout << floor_to_double(-s.objective_value()) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  for(int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
