// SRM 521, Level 3

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

const int MOD = 1000000007;
const int CONF = 9;

int64 A[CONF][CONF] = 
    {{0, 0, 0, 0, 1, 0, 0, 0, 0},
     {4, 0, 0, 0, 0, 0, 1, 0, 0},
     {0, 2, 0, 0, 0, 0, 0, 1, 0},
     {0, 1, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 2, 2, 0, 0, 0, 0, 0},
     {0, 0, 1, 0, 0, 0, 0, 0, 1},
     {0, 0, 0, 0, 2, 2, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 1, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 1, 0}};

class Chimney {
public:
    void multiply(int64 A[CONF][CONF], int64 B[CONF][CONF], int64 C[CONF][CONF]) {
      int64 aux[CONF][CONF];
      memset(aux, 0, sizeof(aux));
      for (int i = 0; i < CONF; ++i)
        for (int j = 0; j < CONF; ++j)
          for (int k = 0; k < CONF; ++k)
            aux[i][j] = (aux[i][j] + A[i][k] * B[k][j]) % MOD;
      memcpy(C, aux, sizeof(aux));
    }

    void pow(int64 base[CONF][CONF], int64 exp, int64 res[CONF][CONF]) {
      if (exp == 0) {
        for (int i = 0; i < CONF; ++i)
          for (int j = 0; j < CONF; ++j)
            res[i][j] = (i == j ? 1 : 0);
        return;
      }

      int64 half[CONF][CONF];
      pow(base, exp / 2, half);
      multiply(half, half, res);
      if (exp & 1)
        multiply(res, A, res);
    }

    int countWays(long long n) {
      int64 B[CONF][CONF];
      pow(A, 4 * n, B);
      return B[0][0];
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
			long long n               = 1;
			int expected__            = 24;

			clock_t start__           = clock();
			int received__            = Chimney().countWays(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			long long n               = 2;
			int expected__            = 1088;

			clock_t start__           = clock();
			int received__            = Chimney().countWays(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			long long n               = 5;
			int expected__            = 110198784;

			clock_t start__           = clock();
			int received__            = Chimney().countWays(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			long long n               = 6;
			int expected__            = 138284509;

			clock_t start__           = clock();
			int received__            = Chimney().countWays(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			long long n               = 100000;
			int expected__            = 19900327;

			clock_t start__           = clock();
			int received__            = Chimney().countWays(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			long long n               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Chimney().countWays(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long n               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Chimney().countWays(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long n               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Chimney().countWays(n);
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
