// SRM 518, Level 2

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

class ConvexSequence {
public:
    int64 getMinimum(vector<int> v) {
      int64 sol = 0;

      bool newStep = true;
      while (newStep) {
        newStep = false;
        for (size_t i = 1; i + 1 < v.size(); ++i) {
          int64 target = (v[i - 1] + v[i + 1]) / 2;
          if (target < v[i]) {
            sol += v[i] - target;
            v[i] = target;
            newStep = true;
          }
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
			int a[]                   = {6,5,1,5,3,3};
			long long expected__      = 7;

			clock_t start__           = clock();
			long long received__      = ConvexSequence().getMinimum(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {3,0,1,4};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = ConvexSequence().getMinimum(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {1,1,1,0,2,2,2};
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = ConvexSequence().getMinimum(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {854159326, 317144183, 781399725, 287076509, 894967145, 882577367, 174517516, 134415519, 274494874, 709819883, 59717133, 732212854, 40551288, 232526958, 811785438, 930853743, 946882902, 321325300, 397702677, 376192501, 599310562, 889156198, 135776890, 882710939, 823196361, 681959076, 318666702, 94469186, 536320456, 116468376, 530320850, 436708006, 903344748, 659080120, 774722507, 967315412, 566063635, 43970906, 497687103, 781266213, 876086123, 366960001, 587364849, 191948103, 172568553, 539762057, 83507466, 71569625, 686305822, 663789601};
			long long expected__      = 20178337330LL;

			clock_t start__           = clock();
			long long received__      = ConvexSequence().getMinimum(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {5};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = ConvexSequence().getMinimum(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = ConvexSequence().getMinimum(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = ConvexSequence().getMinimum(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = ConvexSequence().getMinimum(vector <int>(a, a + (sizeof a / sizeof a[0])));
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
