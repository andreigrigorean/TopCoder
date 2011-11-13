// SRM 489, Level 2

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

class DiceRotation {
public:
    int theCount(int x, int y) {
        int sol = 0;

        if (x >= 2 && y >= 2) sol += 2;
        if (x == 4) sol += y + 1;
        if (y == 4) sol += x + 1;

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
			int goalx                 = 2;
			int goaly                 = 2;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DiceRotation().theCount(goalx, goaly);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int goalx                 = 5;
			int goaly                 = 8;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DiceRotation().theCount(goalx, goaly);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int goalx                 = 47;
			int goaly                 = 58;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DiceRotation().theCount(goalx, goaly);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int goalx                 = 489;
			int goaly                 = 489;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DiceRotation().theCount(goalx, goaly);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int goalx                 = 1000000000;
			int goaly                 = 1000000000;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DiceRotation().theCount(goalx, goaly);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int goalx                 = ;
			int goaly                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DiceRotation().theCount(goalx, goaly);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int goalx                 = ;
			int goaly                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DiceRotation().theCount(goalx, goaly);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int goalx                 = ;
			int goaly                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DiceRotation().theCount(goalx, goaly);
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
