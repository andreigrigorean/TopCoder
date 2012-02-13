// SRM 530, Level 3

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

const int64 MOD = 1000000009;
const int MAX_N = 52;
const int MAX_SCORE = 1900;

int d[2][MAX_N][MAX_N][MAX_SCORE + 1];

class GogoXBallsAndBins {
public:
    inline void add_mod(int& a, int b) {
        a = a + b;
        if (a >= MOD) a -= MOD;
    }

    int solve(vector<int> T, int moves) {
        sort(T.rbegin(), T.rend());

        int n = T.size();
        int p = 0;

        d[0][0][0][0] = 1;
        for (int i = 0; i < n; ++i) {
            // clear
            for (int j = 0; j <= i; ++j)
                for (int k = 0; k <= i; ++k)
                    for (int l = 0; l <= MAX_SCORE; ++l)
                        d[p ^ 1][j][k][l] = 0;

            // solve
            for (int j = 0; j <= i; ++j)
                for (int k = 0; k <= i; ++k)
                    for (int l = 0; l <= MAX_SCORE; ++l) 
                        if (d[p][j][k][l] > 0) {
                        // up and down go together
                        add_mod(d[p ^ 1][j][k][l], d[p][j][k][l]);

                        // up +, down +
                        if (l + 2 * T[i] <= MAX_SCORE)
                        add_mod(d[p ^ 1][j + 1][k + 1][l + 2 * T[i]], d[p][j][k][l]);

                        // up +, down -
                        if (j > 0)
                        add_mod(d[p ^ 1][j][k][l], ((int64)d[p][j][k][l] * j) % MOD);

                        // up -, down +
                        if (k > 0)
                        add_mod(d[p ^ 1][j][k][l], ((int64)d[p][j][k][l] * k) % MOD);

                        // up -, down -
                        if (j > 0 && k > 0)
                        add_mod(d[p ^ 1][j - 1][k - 1][l - 2 * T[i]], ((int64)d[p][j][k][l] * j * k) % MOD);
                    }
            p ^= 1;
        }
        return d[p][0][0][2 * moves];
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
			int T[]                   = {1, 2, 3};
			int moves                 = 1;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int T[]                   = {1, 2, 3};
			int moves                 = 2;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int T[]                   = {1, 2, 3};
			int moves                 = 3;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int T[]                   = {1, 2, 3};
			int moves                 = 0;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int T[]                   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
			int moves                 = 64;
			int expected__            = 625702391;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int T[]                   = ;
			int moves                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int T[]                   = ;
			int moves                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int T[]                   = ;
			int moves                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GogoXBallsAndBins().solve(vector <int>(T, T + (sizeof T / sizeof T[0])), moves);
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
