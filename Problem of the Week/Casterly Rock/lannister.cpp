#include <iostream>

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

int n, m;
long s;

int ceil_to_long(const SolT &x) {
  double a = std::floor(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a - 1 >= x) a -= 1;
  return a;
}

int water_nob_small(int i) {return n + i;}
int water_nob_big(int i) {return  2*n + i;}

int comm(int i) {return 3*n + i;}
int water_comm_small(int i) {return 3*n + m + i;}
int water_comm_big(int i) {return 3*n + 2*m + i;}

int end() {return 3*n + 3*m;}

void test_case() {
  std::cin >> n >> m >> s;
  const int a = 0;
  const int b = 1;
  const int c = 2;
  const int d = 3;
  const int max_len = 4;

  long sum_x = 0, sum_y = 0, sum_c = 0;

  // create an LP with Ax <= b and no lower/upper bounds
  Program lp (CGAL::SMALLER, false, 0, false, 0); 

  // nobble houses, on the left
  for(int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    sum_x -= x;
    sum_y -= y;
    sum_c -= 1;
    lp.set_a(a, i, x); 
    lp.set_a(b, i, y);
    lp.set_a(c, i, 1);

    lp.set_a(b, water_nob_small(i), x);
    lp.set_a(a, water_nob_small(i), -y);
    lp.set_a(d, water_nob_small(i), 1);
    lp.set_a(max_len, water_nob_small(i), -1);

    lp.set_a(b, water_nob_big(i), -x);
    lp.set_a(a, water_nob_big(i), y);
    lp.set_a(d, water_nob_big(i), -1);
    lp.set_a(max_len, water_nob_big(i), -1);
  }

  // common houses, on the right
  for(int i = 0; i < m; ++i) {
    int x, y;
    std::cin >> x >> y;
    sum_x += x;
    sum_y += y;
    sum_c += 1;

    lp.set_a(a, comm(i), -x); 
    lp.set_a(b, comm(i), -y);
    lp.set_a(c, comm(i), -1);

    lp.set_a(b, water_comm_small(i), x);
    lp.set_a(a, water_comm_small(i), -y);
    lp.set_a(d, water_comm_small(i), 1);
    lp.set_a(max_len, water_comm_small(i), -1);

    lp.set_a(b, water_comm_big(i), -x);
    lp.set_a(a, water_comm_big(i), y);
    lp.set_a(d, water_comm_big(i), -1);
    lp.set_a(max_len, water_comm_big(i), -1);
  }

  lp.set_l(a, true, 1);
  
  lp.set_c(max_len, 1);

  Solution sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()) {
    std::cout << "Yuck!\n";
    return;
  }

  if(s == 0) {
    std::cout << "Bankrupt!\n";
    return;
  } else if(s == -1) {
    std::cout << ceil_to_long(sol.objective_value()) << "\n";
    return;
  }

  lp.set_a(a, end(), sum_x);
  lp.set_a(b, end(), sum_y);
  lp.set_a(c, end(), sum_c);
  lp.set_b(end(), s);

  sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()) {
    std::cout << "Bankrupt!\n";
  } else {
    std::cout << ceil_to_long(sol.objective_value()) << "\n";  
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;

  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
