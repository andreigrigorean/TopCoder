// SRM 487, Level 3
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

const int MAX_N = 1000005;
const int64 MOD = 1000000009;

int64 d[MAX_N];

class BunnySequence {
public:
    int getNumber(int m, int n) {
        if (!n) return 1;

        int64 last_m = 1;
        d[1] = 1;

        for (int i = 2; i <= n + 1; ++i) {
            d[i] = last_m;
            if (i == m + 1)
                d[i] = (d[i] - d[i - m] + MOD) % MOD;

            last_m = (last_m + d[i]) % MOD;
            if (i > m) last_m = (last_m - d[i - m] + MOD) % MOD;
        }

        return d[n + 1];
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
			int m                     = 5;
			int n                     = 3;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = BunnySequence().getNumber(m, n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int m                     = 487;
			int n                     = 0;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = BunnySequence().getNumber(m, n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int m                     = 19;
			int n                     = 10;
			int expected__            = 512;

			clock_t start__           = clock();
			int received__            = BunnySequence().getNumber(m, n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int m                     = 3;
			int n                     = 4;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = BunnySequence().getNumber(m, n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int m                     = 10;
			int n                     = 487;
			int expected__            = 829515032;

			clock_t start__           = clock();
			int received__            = BunnySequence().getNumber(m, n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int m                     = ;
			int n                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BunnySequence().getNumber(m, n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int m                     = ;
			int n                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BunnySequence().getNumber(m, n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int m                     = ;
			int n                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BunnySequence().getNumber(m, n);
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
