#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool t_asc(const pair<long, long>& p1, const pair<long, long>& p2) {
  return p1.second < p2.second;
}

int find(const vector<pair<long, long> >& sub2, long t1, long T) {
  int L = 0, R = (int)sub2.size();

  while(L < R) {
    int mid = (L + R) / 2;
    
    if(sub2[mid].second + t1 < T) L = mid + 1;
    else R = mid;
  }

  return L - 1;
}

bool split_and_list(long gulp, vector<pair<long, long> >& movements_1, vector<pair<long, long> >& movements_2, long D, long T) {
  vector<pair<long, long> > sub1, sub2;
  
  for(int s = 0; s < 1<<(int)movements_1.size(); ++s) {
    long t = 0;
    long d = 0;
    for(int i = 0; i < (int)movements_1.size(); ++i) {
      if(s & 1<<i) {
        t += movements_1[i].second;
        if(t > T) break;
        d += movements_1[i].first + gulp;
      }
    }
    if(t < T) {
      sub1.push_back(make_pair(d, t));
      if(d >= D) return true;    
    }  
  }

  for(int s = 0; s < 1<<(int)movements_2.size(); ++s) {
    long t = 0;
    long d = 0;
    for(int i = 0; i < (int)movements_2.size(); ++i) {
      if(s & 1<<i) {
        t += movements_2[i].second;
        if(t > T) break;
        d += movements_2[i].first + gulp;
      }
    }
    if(t < T) {
      sub2.push_back(make_pair(d, t));
      if(d >= D) return true;    
    }  
  }

  sort(sub2.begin(), sub2.end(), t_asc);

  vector<long> partial_best(sub2.size());
  long current_best = sub2[0].first;
  partial_best[0] = current_best;
  for(int i = 1; i < (int)sub2.size(); ++i) {
    if(sub2[i].first > current_best) current_best = sub2[i].first;    
    partial_best[i] = current_best;  
  }

  for(int i = 0; i < (int)sub1.size(); ++i) {
    int index = find(sub2, sub1[i].second, T);
    if(index != (int)sub2.size() && partial_best[index] + sub1[i].first >= D) return true;
  }
  
  return false;
}

void test_case() {
  int n, m;
  long D, T;
  cin >> n >> m >> D >> T;
  
  vector<pair<long, long> > movements_1;
  vector<pair<long, long> > movements_2;
  //vector<pair<long, long> > movements;
  
  for (int i = 0; i < n; ++i) {
    long d, t;
    cin >> d >> t;
    //movements.push_back(make_pair(d, t));
    // Split list
    if (i % 2 == 0) movements_1.push_back(make_pair(d, t));
    else movements_2.push_back(make_pair(d, t));
  }
  
  vector<long> si(m+1, 0);
  for (int i = 1; i <= m; ++i) {
    cin >> si[i];
  }

  int L = 0;
  int R = si.size();

  while(L < R) {
    int mid = (L + R) / 2;
    if(split_and_list(si[mid], movements_1, movements_2, D, T)) R = mid;
    else L = mid + 1;
  }

  if(L == (int) si.size()) cout << "Panoramix captured\n";
  else cout << L << "\n";
  
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  
  for (int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
