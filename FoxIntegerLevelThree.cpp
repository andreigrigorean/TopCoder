// TCO11 Qual 2, Level 3

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int LCM = 22680;

int v[LCM + 1];

class FoxIntegerLevelThree {
public:
    inline int d(int x) { return x % 9 == 0 ? 9 : x % 9; }

    long long numbers(long long n) {
      return v[LCM] * (n / LCM) + v[n % LCM];
    }

    long long count(long long min, long long max)  {
      for (int i = 1; i <= LCM; ++i)
        if (i * d(i) <= LCM)
          v[i * d(i)] = 1;
      for (int i = 1; i <= LCM; ++i)
        v[i] += v[i - 1];

      return numbers(max) - numbers(min - 1);
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
			long long min             = 10;
			long long max             = 16;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = FoxIntegerLevelThree().count(min, max);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			long long min             = 123;
			long long max             = 123;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = FoxIntegerLevelThree().count(min, max);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			long long min             = 160;
			long long max             = 160;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = FoxIntegerLevelThree().count(min, max);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			long long min             = 47;
			long long max             = 58;
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = FoxIntegerLevelThree().count(min, max);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			long long min             = 123456789;
			long long max             = 9876543210LL;
			long long expected__      = 2618024258LL;

			clock_t start__           = clock();
			long long received__      = FoxIntegerLevelThree().count(min, max);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			long long min             = ;
			long long max             = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxIntegerLevelThree().count(min, max);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long min             = ;
			long long max             = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxIntegerLevelThree().count(min, max);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long min             = ;
			long long max             = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxIntegerLevelThree().count(min, max);
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
