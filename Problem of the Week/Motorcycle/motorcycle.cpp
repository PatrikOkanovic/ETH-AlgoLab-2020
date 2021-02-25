#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <algorithm>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel K;

typedef K::Point_2 Point;
typedef K::Ray_2 Ray;

vector<double> y0s;

bool asc_y0(int i, int j) {
    return y0s[i] < y0s[j];
}

void test_case() {
  int n; cin >> n; 
    
  vector<int> indices(n);
  vector<Ray> rays(n);
  vector<K::FT> slopes(n);
  y0s = vector<double> (n);
  for (int i = 0 ; i < n ; i++) {
        double x0 = 0, y0, x1, y1;
        std::cin >> y0 >> x1 >> y1;

        y0s[i] = y0;
        Ray r = Ray(Point(x0, y0), Point(x1, y1));
        indices[i] = i;
        rays[i] = r;
        slopes[i] = r.direction().dy() / r.direction().dx();
    }
    
    sort(indices.begin(), indices.end(), asc_y0);
    
    vector<int> riding(0);
    riding.push_back(indices[0]);
    int i = 1;
    while (i < n) {
        int bi = indices[i];
        
        bool ride = true;
        while (!riding.empty() && ride) {
            int bj = riding.back();
            if (do_intersect(rays[bi], rays[bj])) {
                if (slopes[bi] + slopes[bj] > 0) {
                    // Biker i has a smaller slope than biker j -> biker i is closer to a straight line -> biker i was here first
                    riding.pop_back();
                } else {
                    // Either the slopes are the same -> biker i came from above (i.e. left) and therefore stops,
                    // or biker i has a bigger slope -> biker j was here first
                    ride = false;
                }
            } else {
                break;
            }
        }
        if (ride) {
            riding.push_back(bi);
        }
        
        i++;
    }
    
    sort(riding.begin(), riding.end());
    for (auto& i : riding) {
        cout << i << " ";
    }
    cout << "\n";  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  for(int i = 0; i < t; ++i) {
    test_case();
  }
  
    return 0;
}
