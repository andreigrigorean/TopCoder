// SRM 418, Level 1

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

class LargestSubsequence {
public:
    string getLargest(string s) {
      if (s.empty()) return "";
      string::iterator it = max_element(s.begin(), s.end());
      return *it + getLargest(s.substr(it - s.begin() + 1));
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum) {
		switch (casenum) {
		case 0: {
			string s                  = "test";
			string expected__         = "tt";

			clock_t start__           = clock();
			string received__         = LargestSubsequence().getLargest(s);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string s                  = "a";
			string expected__         = "a";

			clock_t start__           = clock();
			string received__         = LargestSubsequence().getLargest(s);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string s                  = "example";
			string expected__         = "xple";

			clock_t start__           = clock();
			string received__         = LargestSubsequence().getLargest(s);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string s                  = "aquickbrownfoxjumpsoverthelazydog";
			string expected__         = "zyog";

			clock_t start__           = clock();
			string received__         = LargestSubsequence().getLargest(s);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string s                  = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LargestSubsequence().getLargest(s);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string s                  = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LargestSubsequence().getLargest(s);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s                  = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LargestSubsequence().getLargest(s);
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
