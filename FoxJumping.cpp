// SRM 498, Level 3
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int MAX_COORD = 805;
const int MAX_STEPS = 1605;
const int MOD = 10007;

int Sx[MAX_STEPS][MAX_COORD];
int Sy[MAX_STEPS][MAX_COORD];
int B[MAX_STEPS][MAX_COORD / 10 + 1];
int comb[MAX_STEPS][MAX_STEPS];

class FoxJumping {
public:
    int getCount(int Tx, int Ty, int Mx, int My, int R, vector<int> bad) {
      for (int j = 0; j <= Tx; ++j)
        Sx[0][j] = 1;
      for (int i = 1; i <= R; ++i) {
        Sx[i][0] = 1;
        for (int j = 1; j <= Tx; ++j) 
          Sx[i][j] = (Sx[i][j - 1] + Sx[i - 1][j] - 
              (j - Mx - 1 >= 0 ? Sx[i - 1][j - Mx - 1] : 0) + MOD) % MOD;
      }

      for (int j = 0; j <= Ty; ++j)
        Sy[0][j] = 1;
      for (int i = 1; i <= R; ++i) {
        Sy[i][0] = 1;
        for (int j = 1; j <= Ty; ++j)
          Sy[i][j] = (Sy[i][j - 1] + Sy[i - 1][j] -
              (j - My - 1 >= 0 ? Sy[i - 1][j - My - 1] : 0) + MOD) % MOD;
      }

      bad.push_back(0);
      B[0][0] = 1;
      for (int i = 1; i <= R; ++i)
        for (int j = 0; j <= min(Tx, Ty) / 10; ++j)
          for (unsigned k = 0; k < bad.size(); ++k)
            if (bad[k] / 10 <= j)
              B[i][j] = (B[i][j] + B[i - 1][j - bad[k] / 10]) % MOD;

      for (int i = 0; i <= R; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j)
          comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
      }

      int sol = 0;
      int sgn = -1;
      for (int i = 0; i <= R; ++i) {
        sgn *= -1;
        for (int j = 0; j <= min(Tx, Ty) / 10; ++j) {
          int newTx = Tx - j * 10;
          int newTy = Ty - j * 10;
          sol = (sol + sgn * comb[R][i] * B[i][j] % MOD *
            (Sx[R - i][newTx] - (newTx == 0 ? 0 : Sx[R - i][newTx - 1])) % MOD *
            (Sy[R - i][newTy] - (newTy == 0 ? 0 : Sy[R - i][newTy - 1])) % MOD + MOD) % MOD;
        }
      }
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
			int Tx                    = 2;
			int Ty                    = 2;
			int Mx                    = 1;
			int My                    = 1;
			int R                     = 2;
			int bad[]                 = {};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = FoxJumping().getCount(Tx, Ty, Mx, My, R, vector <int>(bad, bad + (sizeof bad / sizeof bad[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int Tx                    = 2;
			int Ty                    = 2;
			int Mx                    = 1;
			int My                    = 1;
			int R                     = 3;
			int bad[]                 = {};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = FoxJumping().getCount(Tx, Ty, Mx, My, R, vector <int>(bad, bad + (sizeof bad / sizeof bad[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int Tx                    = 10;
			int Ty                    = 10;
			int Mx                    = 10;
			int My                    = 10;
			int R                     = 1;
			int bad[]                 = {};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = FoxJumping().getCount(Tx, Ty, Mx, My, R, vector <int>(bad, bad + (sizeof bad / sizeof bad[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int Tx                    = 10;
			int Ty                    = 10;
			int Mx                    = 10;
			int My                    = 10;
			int R                     = 1;
			int bad[]                 = {10};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = FoxJumping().getCount(Tx, Ty, Mx, My, R, vector <int>(bad, bad + (sizeof bad / sizeof bad[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int Tx                    = 11;
			int Ty                    = 11;
			int Mx                    = 11;
			int My                    = 11;
			int R                     = 2;
			int bad[]                 = {10};
			int expected__            = 140;

			clock_t start__           = clock();
			int received__            = FoxJumping().getCount(Tx, Ty, Mx, My, R, vector <int>(bad, bad + (sizeof bad / sizeof bad[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			int Tx                    = 123;
			int Ty                    = 456;
			int Mx                    = 70;
			int My                    = 80;
			int R                     = 90;
			int bad[]                 = {30, 40, 20, 10, 50};
			int expected__            = 6723;

			clock_t start__           = clock();
			int received__            = FoxJumping().getCount(Tx, Ty, Mx, My, R, vector <int>(bad, bad + (sizeof bad / sizeof bad[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int Tx                    = ;
			int Ty                    = ;
			int Mx                    = ;
			int My                    = ;
			int R                     = ;
			int bad[]                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxJumping().getCount(Tx, Ty, Mx, My, R, vector <int>(bad, bad + (sizeof bad / sizeof bad[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int Tx                    = ;
			int Ty                    = ;
			int Mx                    = ;
			int My                    = ;
			int R                     = ;
			int bad[]                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxJumping().getCount(Tx, Ty, Mx, My, R, vector <int>(bad, bad + (sizeof bad / sizeof bad[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int Tx                    = ;
			int Ty                    = ;
			int Mx                    = ;
			int My                    = ;
			int R                     = ;
			int bad[]                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxJumping().getCount(Tx, Ty, Mx, My, R, vector <int>(bad, bad + (sizeof bad / sizeof bad[0])));
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
