//SRM 522, Level 3
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int INF = 0x3f3f3f3f;
const int MAX_N = 64;

bool erase[MAX_N][MAX_N];
bool d[MAX_N][MAX_N];

class PointErasing {
public:
    vector<int> solve(vector<int> y) {
        if (y.size() <= 2) return vector<int>(1, 0);
        
        int n = 0;
        int ord[MAX_N] = {};

        for (size_t i = 0; i < y.size(); ++i)
            if (y[i] == y[0]) ord[i] = ++n;

        memset(erase, false, sizeof(erase));
        for (size_t i = 0; i < y.size(); ++i)
            for (size_t j = i + 1; j < y.size(); ++j)
                if ((y[i] < y[0] && y[0] < y[j]) || (y[j] < y[0] && y[0] < y[i])) {
                    int first = n + 1, last = -1;
                    for (size_t k = i + 1; k < j; ++k)
                        if (y[k] == y[0]) {
                            if (first == n + 1) first = ord[k];
                            last = ord[k];
                        }
                    if (first <= last)
                        erase[first][last] = true;
                }
        for (int j = 1; j < n; ++j)
            for (int i = 1; i + j <= n; ++i)
                for (int k = i; k < i + j; ++k)
                    erase[i][i + j] |= erase[i][k] && erase[k + 1][i + j];

        memset(d, false, sizeof(d));
        d[1][1] = true;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j)
                d[i][j + 1] |= d[i - 1][j];
            for (int j = 2; j <= i; ++j)
                if (erase[j][i]) {
                    for (int k = 1; k <= i; ++k)
                        d[i][k] |= d[j - 1][k];
                }
        }

        vector<int> sol;
        for (int i = 1; i <= n; ++i)
            if (d[n][i]) sol.push_back(i);
       
        return sol;
    }

    vector<int> getOutcomes(vector<int> y) {
        int min_y = INF, max_y = 0;
        FORIT(it, y) {
            min_y = min(min_y, *it);
            max_y = max(max_y, *it);
        }

        // min-max points will always stay
        int always = 0;
        FORIT(it, y)
            if (*it == min_y || *it == max_y)
                ++always;

        vector<int> v, sol_left, sol_right;

        // solve for left side of min-max rectangle
        for (int i = 0; i < (int)y.size(); ++i) {
            if (y[i] == max_y || y[i] == min_y) break;
            v.push_back(y[i]);
        }
        v.push_back(min_y); v.push_back(max_y);
        sol_left = solve(v);

        // solve for right side of min-max rectangle
        v.clear();
        for (int i = (int)y.size() - 1; i >= 0; --i) {
            if (y[i] == max_y || y[i] == min_y) break;
            v.push_back(y[i]);
        }
        v.push_back(min_y); v.push_back(max_y);
        sol_right = solve(v);

        // combine the left and right solutions
        vector<int> sol;
        for (int i = 0; i < (int)sol_left.size(); ++i)
            for (int j = 0; j < (int)sol_right.size(); ++j)
                sol.push_back(sol_left[i] + sol_right[j]);
        FORIT(it, sol)
            *it += always;
        sort(sol.begin(), sol.end());
        sol.resize(unique(sol.begin(), sol.end()) - sol.begin());
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
			int y[]                   = { 1, 2, 1, 1, 0, 4, 3 };
			int expected__[]          = {4, 6 };

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int y[]                   = { 0, 0, 4, 4, 8, 8, 4, 4 };
			int expected__[]          = {6 };

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int y[]                   = { 522 };
			int expected__[]          = {1 };

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int y[]                   = { 19, 19, 19, 19, 19, 19 };
			int expected__[]          = {6 };

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int y[]                   = { 0, 1, 2, 3, 4 };
			int expected__[]          = {2 };

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			int y[]                   = { 7, 8, 8, 7, 6, 7, 9, 3, 5, 0 };
			int expected__[]          = {3, 4, 5 };

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 6: {
			int y[]                   = { 3, 2, 3, 3, 4, 3, 4, 3, 3, 1, 5, 3 };
			int expected__[]          = {4, 5, 6, 7, 9 };

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 7: {
			int y[]                   = { 5, 5, 4, 4, 5, 8, 5, 5, 5, 5, 5, 9, 2, 0, 9, 4, 5, 5, 3, 4, 4, 4, 4, 7, 4 };
			int expected__[]          = {6, 7, 8, 10, 11, 12, 13, 15, 16, 17 };

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			int y[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 9: {
			int y[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 10: {
			int y[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
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
