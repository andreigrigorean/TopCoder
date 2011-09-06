// SRM 513, Level 3

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_N = 22;

class Reflections {
public:
    int n;
    vector<long long> cost[MAX_N];

    long long bestMatch(vector<long long>& a, vector<long long>& b, int finish) {
      long long best = abs(finish);
      for (int i = 0; i < (int)a.size(); ++i) {
        int j = upper_bound(b.begin(), b.end(), a[i] - finish) - b.begin();
        if (j < (int)b.size()) best = min(best, abs(finish - a[i] + b[j]));
        if (j > 0) best = min(best, abs(finish - a[i] + b[j - 1]));
      }
      return best;
    }

    long long minCost(vector<int>& v, int finish) {
      n = v.size();
      for (int i = 0; i <= n; ++i)
        cost[i].clear();

      for (int conf = 0; conf < (1 << n); ++conf) {
        int bitCount = 0;
        long long sum = 0;
        for (int i = 0; i < n; ++i)
          if ((conf >> i) & 1) {
            ++bitCount;
            sum += v[i];
          }

        cost[bitCount].push_back(2 * sum);
      }
      for (int i = 0; i <= n; ++i)
        sort(cost[i].begin(), cost[i].end());

      long long best = abs(finish);
      for (int i = 0; i <= n; ++i) {
        if (i > 0) best = min(best, 2 * i - 1  + bestMatch(cost[i], cost[i - 1], finish));
        best = min(best, 2 * i + bestMatch(cost[i], cost[i], finish));
      }
      return best;
    }

    long long minimumMoves( vector <int> mirrorX, vector <int> mirrorY, vector <int> mirrorZ, vector <int> finalPosition )  {
      return minCost(mirrorX, finalPosition[0]) + minCost(mirrorY, finalPosition[1]) +
        minCost(mirrorZ, finalPosition[2]);
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
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
			int mirrorX[]             = {2};
			int mirrorY[]             = {};
			int mirrorZ[]             = {};
			int finalPosition[]       = {3, 0, 1};
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int mirrorX[]             = {-5, 1, 4, 2, 3, 6, -6};
			int mirrorY[]             = {};
			int mirrorZ[]             = {};
			int finalPosition[]       = {9, 0, 0};
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int mirrorX[]             = {5, 8};
			int mirrorY[]             = {};
			int mirrorZ[]             = {};
			int finalPosition[]       = {4, 0, 0};
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int mirrorX[]             = {5};
			int mirrorY[]             = {5};
			int mirrorZ[]             = {1, 2, 3};
			int finalPosition[]       = {10, 12, -1};
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int mirrorX[]             = {8, -3, 21};
			int mirrorY[]             = {4, 5};
			int mirrorZ[]             = {-7, -2, -1, 7, 14};
			int finalPosition[]       = {40, -4, 31};
			long long expected__      = 10;

			clock_t start__           = clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int mirrorX[]             = ;
			int mirrorY[]             = ;
			int mirrorZ[]             = ;
			int finalPosition[]       = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int mirrorX[]             = ;
			int mirrorY[]             = ;
			int mirrorZ[]             = ;
			int finalPosition[]       = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int mirrorX[]             = ;
			int mirrorY[]             = ;
			int mirrorZ[]             = ;
			int finalPosition[]       = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
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
