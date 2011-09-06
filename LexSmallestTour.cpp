// SRM 516, Level 3

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int MAX_N = 64;

class LexSmallestTour {
public:
    int N;
    bool visited[MAX_N];
    int deg[MAX_N];

    void DFS(vector<string>& roads, int node) {
      visited[node] = true;
      for (int i = 0; i < N; ++i)
        if (roads[node][i] != '.' && !visited[i])
          DFS(roads, i);
    }
    
    bool existsTour(vector<string>& roads, int start, char lastRoad) {
      for (int i = 0; i < N; ++i) {
        int total = 0, best = 0;
        map<char, int> count;

        for (int j = 0; j < N; ++j)
          if (roads[i][j] != '.') {
            ++count[roads[i][j]];
            ++total;
            best = max(best, count[roads[i][j]]);
          }
        if (i == start) {
          ++count[lastRoad];
          ++total;
          best = max(best, count[lastRoad]);
        }

        if (i == 0) {
          if ((total & 1) == 0) return false;
          if (2 * best > total + 1) return false;
        } else {
          if ((total & 1) == 1) return false;
          if (2 * best > total) return false;
        }

        deg[i] = total;
      }

      // check connectivity
      memset(visited, false, sizeof(visited));
      DFS(roads, start);
      for (int i = 0; i < N; ++i)
        if (!visited[i] && deg[i] > 0)
          return false;

      // everything is fine
      return true;
    }

    vector<int> getLexFirstTour(vector<string>& roads) {
      N = roads.size();

      // no solution
      if (!existsTour(roads, 0, '?'))
        return vector<int>();

      // determine the lex first tour
      vector<int> tour;
      tour.push_back(0);

      int node = 0;
      char lastRoad = '?';
      bool foundRoad = false;
      while (true) {
        foundRoad = false;

        for (int i = 0; i < N; ++i)
          if (roads[node][i] != '.' && roads[node][i] != lastRoad) {
            char newRoad = roads[node][i];
            roads[node][i] = roads[i][node] = '.';

            if (existsTour(roads, i, newRoad)) {
              tour.push_back(i);
              node = i;
              lastRoad = newRoad;
              foundRoad = true;
              break;
            }

            roads[node][i] = roads[i][node] = newRoad;
          }
        
        if (!foundRoad) break;
      }

      return tour;
    }

    vector<int> determineTour(vector<string> roads, vector<int> queries) {
      vector<int> tour = getLexFirstTour(roads);
      
      if ((int)tour.size() == 0)
        return vector<int>();

      vector<int> sol;
      FORIT(it, queries)
        sol.push_back(tour[*it]);
      return sol;
    }
};

// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum) {
		switch (casenum) {
		case 0: {
			string roads[]            = {".AB"
,"A.C"
,"BC."};
			int queries[]             = {0, 1, 2, 3};
			int expected__[]          = {0, 1, 2, 0 };

			clock_t start__           = clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string roads[]            = {".A..C"
,"A.ABB"
,".A.C."
,".BC.."
,"CB..."};
			int queries[]             = {0, 1, 2, 3, 4, 5, 6};
			int expected__[]          = {0, 1, 3, 2, 1, 4, 0 };

			clock_t start__           = clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string roads[]            = {".aa"
,"a.A"
,"aA."};
			int queries[]             = {3, 2, 1};
			int expected__[]          = {0, 2, 1 };

			clock_t start__           = clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string roads[]            = {"..A.A"
,"...A."
,"A...A"
,".A..."
,"A.A.."};
			int queries[]             = {1, 2};
			int expected__[]          = { };

			clock_t start__           = clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string roads[]            = ;
			int queries[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			string roads[]            = ;
			int queries[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string roads[]            = ;
			int queries[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  if (argc == 1) {
    for (int test = 0; test < 10; ++test) {
      string command = string(argv[0]) + " ";
      command.push_back('0' + test);
      if (system(command.c_str()))
        cerr << "TEST FAILED!" << endl;
    }
  } else {
    moj_harness::run_test(atoi(argv[1]));
  }
  return 0;
}
// END CUT HERE 
