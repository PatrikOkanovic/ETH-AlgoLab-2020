#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef double IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> SolT;

struct P {
  IT x, y, z;
  P(IT _x, IT _y, IT _z) : x(_x), y(_y), z(_z)  {}
};

int h, t;

double power(P& p, int i, int j, int k) {
    return std::pow(p.x, i) * std::pow(p.y, j) * std::pow(p.z, k);
}

std::vector<IT> combinations(P& p, int d) {
  std::vector<IT> polynom;
  for(int i = 0; i <= d; ++i) {
    for(int j = 0; j <= d; ++j) {
      for(int k = 0; k <= d; ++k) {
        if (i+j+k <= d) {
          polynom.push_back(power(p, i, j, k));
        } else break;
      }
    }
  }

  return polynom;
}



bool is_separable(std::vector<P>& healthy, std::vector<P>& tumor, int d) {
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  
  for(int i = 0; i < h; ++i) {
    std::vector<IT> polynom = combinations(healthy[i], d);
    for(int j = 0; j < polynom.size(); ++j) {
      lp.set_a(j, i, polynom[j]);
    }

    lp.set_b(i, -1);
  }

  for(int i = 0; i < t; ++i) {
    std::vector<IT> polynom = combinations(tumor[i], d);
    for(int j = 0; j < polynom.size(); ++j) {
      lp.set_a(j, h+i, -polynom[j]);
    }
    
    //lp.set_r(h + i, CGAL::LARGER);
    lp.set_b(h + i, -1);
  }


  CGAL::Quadratic_program_options options;
  options.set_pricing_strategy(CGAL::QP_BLAND);
  Solution s = CGAL::solve_linear_program(lp, ET(), options);
  return !s.is_infeasible();
}

void test_case() {

  std::cin >> h >> t;
  
  std::vector<P> healthy;
  for(int i = 0; i < h; ++i) {
    IT x, y, z;
    std::cin >> x >> y >> z;
    healthy.push_back(P(x, y, z));
  }

  std::vector<P> tumor;
  for(int i = 0; i < t; ++i) {
    IT x, y, z;
    std::cin >> x >> y >> z;
    tumor.push_back(P(x, y, z));
  }
  
  if(h == 0 || t == 0) {
    std::cout << "0\n";
    return;
  }

  for(int i = 1; i <= 30; ++i) {
    if(is_separable(healthy, tumor, i)) {
      std::cout << i << "\n";
      return;
    }
  }

  std::cout << "Impossible!\n";

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int N; std::cin >> N;
  for(int i = 0; i < N; ++i) {
    test_case();
  }

  return 0;
}
