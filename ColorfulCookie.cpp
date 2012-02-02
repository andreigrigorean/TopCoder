// SRM 528, Level 3

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int MAX_N = 52;
const int MAX_OP = 40;

int best[MAX_N * MAX_OP];

class ColorfulCookie {
public:
    int getMaximum(vector<int> cookies, int P1, int P2) {
        // binary search the result
        int left = 0, right = 1000;
        while (left < right) {
            int mid = (left + right + 1) / 2;
            if (can_get_cookies(cookies, P1, P2, mid))
                left = mid;
            else
                right = mid - 1;
        }
        return left * (P1 + P2);
    }

    bool can_get_cookies(vector<int>& cookies, int P1, int P2, int need) {
        memset(best, -1, sizeof(best));
        best[0] = 0;

        FORIT(it, cookies) {
            for (int i = need; i >= 0; --i) {
                if (best[i] == -1) continue;
                int aux = best[i];

                for (int type1 = 0; type1 * P1 <= *it; ++type1) {
                    int type2 = min((*it - type1 * P1) / P2, need - type1);
                    if (i + type1 <= need)
                        best[i + type1] = max(best[i + type1], aux + type2);
                }
            }
        }

        return best[need] >= need;
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
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
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
			int cookies[]             = {100, 100};
			int P1                    = 50;
			int P2                    = 50;
			int expected__            = 200;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int cookies[]             = {50, 250, 50};
			int P1                    = 50;
			int P2                    = 100;
			int expected__            = 300;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int cookies[]             = {2000};
			int P1                    = 100;
			int P2                    = 200;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int cookies[]             = {123, 456, 789, 555};
			int P1                    = 58;
			int P2                    = 158;
			int expected__            = 1728;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int cookies[]             = ;
			int P1                    = ;
			int P2                    = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int cookies[]             = ;
			int P1                    = ;
			int P2                    = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int cookies[]             = ;
			int P1                    = ;
			int P2                    = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
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
