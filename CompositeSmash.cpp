// SRM 517, Level 1

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

const int MAX_N = 100005;

bool isPrime[MAX_N];
bool can[MAX_N];

class CompositeSmash {
public:
    string thePossible(int N, int target) {
      memset(isPrime, true, sizeof(isPrime));
      for (int i = 2; i * i <= N; ++i)
        for (int j = i * i; j <= N; j += i)
          isPrime[j] = false;

      can[target] = true;
      for (int i = target + 1; i <= N; ++i)
        can[i] = !isPrime[i];
      for (int i = 2; i <= N; ++i)
        for (int j = 2; j <= i && j * i <= N; ++j)
          if (!can[i] && !can[j] && i * j != target)
            can[i * j] = false;

      return can[N] ? "Yes" : "No";
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
			int N                     = 517;
			int target                = 47;
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 8;
			int target                = 4;
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 12;
			int target                = 6;
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 5;
			int target                = 8;
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 100000;
			int target                = 100000;
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 5858;
			int target                = 2;
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 6: {
			int N                     = 81461;
			int target                = 2809;
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 7: {
			int N                     = 65536;
			int target                = 256;
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			int N                     = ;
			int target                = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int N                     = ;
			int target                = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			int N                     = ;
			int target                = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CompositeSmash().thePossible(N, target);
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
