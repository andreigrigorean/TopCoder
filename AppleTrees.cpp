// SRM 489, Level 3

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

const int MOD = 1000000007;
const int MAX_D = 100005;
const int MAX_N = 42;
const int MAX_R = 42;

int64 dp[2][MAX_N][2 * MAX_N * MAX_R];
int64 fact[MAX_D], invFact[MAX_D];

class AppleTrees {
public:
    inline void addMod(int64& a, int64 b) { a = (a + b) % MOD; }

    int64 modPow(int base, int exp) {
        if (exp == 0) return 1;
        int64 half = modPow(base, exp / 2);
        return half * half % MOD * (exp & 1 ? base : 1) % MOD;
    }

    int64 comb(int n, int k) {
        if (k < 0 || k > n) return 0;
        if (n < 0) return 0;
        return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
    }

    int theCount(int D, vector<int> r) {
        int n = r.size();
        sort(r.begin(), r.end(), greater<int>());

        // dp time
        // consider you want to build it circular 
        dp[0][1][0] = 1;
        int p = 0;
        for (int i = 0; i < n; ++i) {
            memset(dp[p ^ 1], 0, sizeof(dp[p ^ 1]));
            for (int j = 1; j <= i + 1; ++j)
                for (int k = 0; k <= (i + 1) * 2 * MAX_R; ++k) {
                    if (dp[p][j][k] == 0) continue;

                    // connect two components
                    addMod(dp[p ^ 1][j - 1][k], dp[p][j][k] * j);

                    // add to an existing component
                    addMod(dp[p ^ 1][j][k + r[i] - 1], dp[p][j][k] * 2 * j);

                    // create a new component
                    addMod(dp[p ^ 1][j + 1][k + 2 * (r[i] - 1)], dp[p][j][k] * j);
                }
            p ^= 1;
        }

        // factorials
        fact[0] = 1;
        for (int i = 1; i <= D; ++i)
            fact[i] = fact[i - 1] * i % MOD;
        invFact[D] = modPow(fact[D], MOD - 2);
        for (int i = D - 1; i >= 0; --i)
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;

        int64 ans = 0;
        for (int i = 0; i <= n * 2 * MAX_R; ++i)
            addMod(ans, dp[p][0][i] * comb(D - i, n));
        return ans;
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
			int D                     = 10;
			int r[]                   = {40};
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = AppleTrees().theCount(D, vector <int>(r, r + (sizeof r / sizeof r[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int D                     = 4;
			int r[]                   = {1, 1, 1, 1};
			int expected__            = 24;

			clock_t start__           = clock();
			int received__            = AppleTrees().theCount(D, vector <int>(r, r + (sizeof r / sizeof r[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int D                     = 4;
			int r[]                   = {1, 1, 2};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = AppleTrees().theCount(D, vector <int>(r, r + (sizeof r / sizeof r[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int D                     = 58;
			int r[]                   = {5, 8};
			int expected__            = 2550;

			clock_t start__           = clock();
			int received__            = AppleTrees().theCount(D, vector <int>(r, r + (sizeof r / sizeof r[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int D                     = 47;
			int r[]                   = {4, 8, 9};
			int expected__            = 28830;

			clock_t start__           = clock();
			int received__            = AppleTrees().theCount(D, vector <int>(r, r + (sizeof r / sizeof r[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			int D                     = 100000;
			int r[]                   = {21, 37, 23, 13, 32, 22, 9, 39};
			int expected__            = 923016564;

			clock_t start__           = clock();
			int received__            = AppleTrees().theCount(D, vector <int>(r, r + (sizeof r / sizeof r[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int D                     = ;
			int r[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AppleTrees().theCount(D, vector <int>(r, r + (sizeof r / sizeof r[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int D                     = ;
			int r[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AppleTrees().theCount(D, vector <int>(r, r + (sizeof r / sizeof r[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int D                     = ;
			int r[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AppleTrees().theCount(D, vector <int>(r, r + (sizeof r / sizeof r[0])));
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
