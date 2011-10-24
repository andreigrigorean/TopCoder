// SRM 496, Level 1

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

class ColoredStrokes {
public:
    int getLeast(vector<string> A) {
      int sol = 0;

      for (int i = 0; i < (int)A.size(); ++i)
        for (int j = 0; j < (int)A[i].size(); ++j) {
          if ((A[i][j] == 'R' || A[i][j] == 'G') && 
              (j == 0 || (A[i][j - 1] != 'R' && A[i][j - 1] != 'G')))
            ++sol;
          if ((A[i][j] == 'B' || A[i][j] == 'G') &&
              (i == 0 || (A[i - 1][j] != 'B' && A[i - 1][j] != 'G')))
            ++sol;
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
			string picture[]          = {"...",
 "..."};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ColoredStrokes().getLeast(vector <string>(picture, picture + (sizeof picture / sizeof picture[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string picture[]          = {"..B.",
 "..B."};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = ColoredStrokes().getLeast(vector <string>(picture, picture + (sizeof picture / sizeof picture[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string picture[]          = {".BB."};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ColoredStrokes().getLeast(vector <string>(picture, picture + (sizeof picture / sizeof picture[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string picture[]          = {"...B..",
 ".BRGRR",
 ".B.B.."};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = ColoredStrokes().getLeast(vector <string>(picture, picture + (sizeof picture / sizeof picture[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string picture[]          = {"...B..",
 ".BRBRR",
 ".B.B.."};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = ColoredStrokes().getLeast(vector <string>(picture, picture + (sizeof picture / sizeof picture[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			string picture[]          = {"GR",
 "BG"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = ColoredStrokes().getLeast(vector <string>(picture, picture + (sizeof picture / sizeof picture[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string picture[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColoredStrokes().getLeast(vector <string>(picture, picture + (sizeof picture / sizeof picture[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string picture[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColoredStrokes().getLeast(vector <string>(picture, picture + (sizeof picture / sizeof picture[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string picture[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColoredStrokes().getLeast(vector <string>(picture, picture + (sizeof picture / sizeof picture[0])));
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
