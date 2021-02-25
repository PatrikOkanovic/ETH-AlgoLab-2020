#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

struct Info {
  bool color;
  int network;
  bool visited;
  bool operator==(const Info &other) {
    return (this->color == other.color) &&
            (this->network == other.network) &&
           (this->visited == other.visited);
  }
};

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<Info, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;

typedef Triangulation::Vertex_handle Vertex;
typedef Triangulation::Vertex_circulator VertexC;

bool conflict_within_network(const Triangulation &t, K::FT &rr) {
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    if(t.segment(*e).squared_length() <= rr) {
      return true;
    }
  }
  return false;
}

bool is_colorable(const Triangulation &t, K::FT &rr) {
  Triangulation network0, network1;
  int component = 0;
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
    if(!(v->info().visited)) {
      v->info().visited = true;
      v->info().network = component;
      
      std::vector<Vertex> stack;
      stack.push_back(v);
      
      while(!stack.empty()) {
        Vertex u = stack.back();
        stack.pop_back();
        
        VertexC c = t.incident_vertices(u);

        do {
          if(!t.is_infinite(c)) {
            if(CGAL::squared_distance(u->point(), c->point()) <= rr) {
              if(c->info() == u->info()) {
                return false;
              }
              
              if(!c->info().visited) {
                stack.push_back(c);
                c->info() = {!u->info().color, component, true};
              }
            }
          }
        } while(++c != t.incident_vertices(u));
      }
      component++;
    }


    if(v->info().color) {
      network0.insert(v->point());
    } else {
      network1.insert(v->point());
    }
  }


  return !conflict_within_network(network0, rr) && !conflict_within_network(network1, rr);
}


void test_case() {
  int n, m; K::FT r;
  std::cin >> n >> m >> r;
  K::FT rr = r*r;

  Info init = {false, 0, false};
  
  std::vector<std::pair<K::Point_2, Info>> stations;
  for(int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    stations.push_back(std::make_pair(K::Point_2(x, y), init));
  }

  Triangulation t(stations.begin(), stations.end());
  bool colorable = is_colorable(t, rr);

  for(int i = 0; i < m; ++i) {
    int x, y;
    std::cin >> x >> y;
    K::Point_2 holmes(x, y);
    std::cin >> x >> y;
    K::Point_2 watson(x, y);

    if(!colorable) {
      std::cout << "n";
    } else {
      if(CGAL::squared_distance(holmes, watson) <= rr) {
        std::cout << "y";      
      } else {
        auto station_holmes = t.nearest_vertex(holmes);
        auto station_watson = t.nearest_vertex(watson);
        if (CGAL::squared_distance(holmes, station_holmes->point()) > rr || CGAL::squared_distance(watson, station_watson->point()) > rr) {
          std::cout << "n";
        } else {
          if (station_holmes->info().network == station_watson->info().network) {
            std::cout << "y";
          } else {
            std::cout << "n";
          }
        }

        
      }

    }
  }
  
  std::cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;

  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
