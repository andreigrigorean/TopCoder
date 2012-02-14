// SRM 524, Level 3
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

const int MOD = 1000000009;
const int MAX_N = 64;

int64 d[MAX_N][MAX_N];
int64 comb[MAX_N][MAX_N];

class AxonometricProjection {
public:
    inline void add_mod(int64& a, int64 b) {
        a = (a + b) % MOD;
    }

    inline int64 power(int64 base, int exp) {
        if (exp == 0) return 1;
        int64 half = power(base, exp / 2);
        return half * half % MOD * (exp & 1 ? base : 1) % MOD;
    }

    inline int64 get_comb(int n, int k) {
        if (k > n) return 0;
        if (comb[n][k] > 0) return comb[n][k];
        if (k == 0) return comb[n][k] = 1;
        return comb[n][k] = (get_comb(n - 1, k) + get_comb(n - 1, k - 1)) % MOD;
    }

    int64 solve(int val, int n, int m, int N, int M) {
        if (val == 0) return 1;

        //d[i][j] = number of ways of completing the first i lines if we have solved j columns
        memset(d, 0, sizeof(d));
        d[0][0] = 1;

        for (int i = 1; i <= n; ++i)
            for (int j = 0; j <= m; ++j) {
                // k = 0
                for (int x = 1; x <= j + M - m; ++x)
                    add_mod(d[i][j], d[i - 1][j] * power(val, m - j + x - 1) % MOD * power(val + 1, j + M - m - x));

                // k > 0
                for (int k = 1; k <= j; ++k)
                    add_mod(d[i][j], d[i - 1][j - k] * get_comb(m - (j - k), k) % MOD * power(val, m - j) % MOD * power(val + 1, j - k + M - m));
            }

        int64 line = 0;
        for (int i = 1; i <= N - n; ++i)
            add_mod(line, power(val, i - 1) * power(val + 1, N - n - i));
        int64 line2 = power(val + 1, N - n);
    
        int64 ans = 0;
        for (int j = 0; j <= m; ++j)
            add_mod(ans, d[n][m - j] * power(line, j) % MOD * power(line2, m - j));

        return ans;
    }

    int howManyWays(vector<int> A, vector<int> B) {
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        // no solution
        if (A.back() != B.back()) return 0;

        int64 ans = 1;
        int n = A.size(), m = B.size();
        int i = 0, j = 0;

        while (i < n && j < m) {
            int min_val = min(A[i], B[j]);
            int i2 = i - 1, j2 = j - 1;
            while (i2 + 1 < n && A[i2 + 1] == min_val) ++i2;
            while (j2 + 1 < m && B[j2 + 1] == min_val) ++j2;

            ans = ans * solve(min_val, i2 - i + 1, j2 - j + 1, n - i, m - j) % MOD;

            i = i2 + 1;
            j = j2 + 1;
        }

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
			int heightsOfLeftView[]   = {1,1};
			int heightsOfFrontView[]  = {1,1};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int heightsOfLeftView[]   = {50,50,50,50,524};
			int heightsOfFrontView[]  = {524,524};
			int expected__            = 104060401;

			clock_t start__           = clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int heightsOfLeftView[]   = {1,2,3,4,5,6,7,8,9,10};
			int heightsOfFrontView[]  = {1,2,3,4,5,6,7,8,9,10,11};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int heightsOfLeftView[]   = {5,2,4,1};
			int heightsOfFrontView[]  = {5,2,4,0,1};
			int expected__            = 429287;

			clock_t start__           = clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int heightsOfLeftView[]   = {5,2,4,52,24,524};
			int heightsOfFrontView[]  = {0,4,20,24,500,504,520,524};
			int expected__            = 97065655;

			clock_t start__           = clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int heightsOfLeftView[]   = {6, 10, 10, 8, 2, 6, 4, 4, 3, 4, 8, 0, 6, 6, 4, 6, 3, 7, 7, 5, 10, 7, 1, 0, 3, 3, 9, 1, 8};
			int heightsOfFrontView[]  = {7, 9, 0, 9, 9, 0, 6, 0, 1, 7, 4, 6, 6, 7, 8, 4, 7, 6, 3, 0, 3, 10, 2, 10, 2, 1, 0, 7, 1, 8, 8, 10, 8, 8, 5, 5, 1, 1, 9, 5, 3};
			int expected__            = 924671600;

			clock_t start__           = clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
      case 6: {
			int heightsOfLeftView[]   = {1, 1, 2};
			int heightsOfFrontView[]  = {1, 1, 2};
			int expected__            = 161;

			clock_t start__           = clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
/*      case 7: {
			int heightsOfLeftView[]   = ;
			int heightsOfFrontView[]  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  if (argc == 1) {
    for (int test = 1; test < 10; ++test) {
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
