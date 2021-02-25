#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
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

void test_case(int n) {
  int d; std::cin >> d;
  const int R = d;
  std::vector<std::vector<int> > A(n, std::vector<int>(d));
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  std::vector<int> B(n);
  std::vector<int> norm(n, 0);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < d; ++j) {
      std::cin >> A[i][j];
      norm[i] += A[i][j] * A[i][j];
    }
    std::cin >> B[i];
    norm[i] = std::sqrt(norm[i]);
  }

  lp.set_l(R, true, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) {
      lp.set_a(j, i, A[i][j]);
    }

    lp.set_a(R, i, norm[i]);
    lp.set_b(i, B[i]);
  }

  lp.set_c(R, -1);

  Solution s = CGAL::solve_linear_program(lp, ET());

  if(s.is_unbounded()) std::cout << "inf\n";
  else if(s.is_infeasible()) std::cout << "none\n";
  else std::cout << floor_to_double(-s.objective_value()) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  while(true) {
    int n;
    std::cin >> n;
    if(n == 0) break;
    test_case(n);
  }

  return 0;
}
