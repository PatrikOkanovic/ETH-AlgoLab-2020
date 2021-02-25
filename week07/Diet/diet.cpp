#include <iostream>
#include <vector>
#include <utility>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type
for solver (CGAL::Gmpz or CGAL::Gmpq)
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

void test_case(int n, int m) {
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp (CGAL::SMALLER, true, 0, false, 0); 
  for(int i = 0; i < n; ++i) {
    IT mini, maxi;
    std::cin >> mini >> maxi;
    lp.set_b(i, -mini);
    lp.set_b(n+i, maxi);
  }
  
  for(int j = 0; j < m; ++j) {
    IT pj; std::cin >> pj;
    lp.set_c(j, pj);
    for(int i = 0; i < n; ++i) {
      IT C_ji;
      std::cin >> C_ji;
      lp.set_a(j, i, -1*C_ji);
      lp.set_a(j, n+i, 1*C_ji);
    }
  }
  
  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  if(s.is_optimal()) std::cout << floor_to_double(s.objective_value()) << "\n";
  else std::cout << "No such diet.\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  while(true) {
    int n, m;
    std::cin >> n >> m;
    if (n == 0 && m == 0) break;
    test_case(n, m);
  }
  
  return 0;
}
