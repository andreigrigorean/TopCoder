// SRM 522, Level 2

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int64 MAX_SQRT = 100005;

class CorrectMultiplication {
public:
    long long getMinimum(int a, int b, int c) {
      if (a > b) swap(a, b);
      
      int64 best = MAX_SQRT * MAX_SQRT;
      for (int64 A = 1; A <= MAX_SQRT; ++A) {
        int64 B = c / A;
        if (B > 0)
          best = min(best, abs(a - A) + abs(b - B) + abs(c - A * B));
        ++B;
        best = min(best, abs(a - A) + abs(b - B) + abs(c - A * B));
      }

      return best;
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
			int a                     = 19;
			int b                     = 28;
			int c                     = 522;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = CorrectMultiplication().getMinimum(a, b, c);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int a                     = 10;
			int b                     = 30;
			int c                     = 500;
			long long expected__      = 11;

			clock_t start__           = clock();
			long long received__      = CorrectMultiplication().getMinimum(a, b, c);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int a                     = 11111;
			int b                     = 11111;
			int c                     = 123454321;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = CorrectMultiplication().getMinimum(a, b, c);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int a                     = 1000;
			int b                     = 100;
			int c                     = 10;
			long long expected__      = 1089;

			clock_t start__           = clock();
			long long received__      = CorrectMultiplication().getMinimum(a, b, c);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int a                     = 399;
			int b                     = 522;
			int c                     = 199999;
			long long expected__      = 24;

			clock_t start__           = clock();
			long long received__      = CorrectMultiplication().getMinimum(a, b, c);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = CorrectMultiplication().getMinimum(a, b, c);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = CorrectMultiplication().getMinimum(a, b, c);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = CorrectMultiplication().getMinimum(a, b, c);
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
