// SRM 497, Level 3

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

class ModuleSequence {
public:
    int64 K, N;

    int64 count(int len, int upper) {
        if (len < 0 || upper < 0) return 0;

        int64 sq_root = max(10LL, (int64)sqrt(len));
        vector<int64> v;
        for (int i = 0; i < sq_root; ++i)
            v.push_back(i * K % N);
        sort(v.begin(), v.end());

        int64 sol = 0;
        int64 i, val = 0;
        for (i = 0; i + sq_root - 1 <= len; i += sq_root) {
            vector<int64>::iterator split = lower_bound(v.begin(), v.end(), N - val);

            if (split != v.begin())
                sol += upper_bound(v.begin(), split, upper - val) - v.begin();
            if (split != v.end())
                sol += upper_bound(split, v.end(), upper - val + N) - split;

            val = (val + sq_root * K) % N;
        }
        for (; i <= len; ++i) {
            if (val <= upper) ++sol;
            val = (val + K) % N;
        }

        return sol;
    }

    int64 countElements(int64 _K, int64 _N, int64 A, int64 B, int64 lower, int64 upper) {
        K = _K;
        N = _N;
        return (count(B, upper) - count(B, lower - 1)) - (count(A - 1, upper) - count(A - 1, lower - 1));
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
			long long K               = 2;
			long long N               = 7;
			long long A               = 1;
			long long B               = 5;
			long long lower           = 2;
			long long upper           = 5;
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			long long K               = 9;
			long long N               = 1;
			long long A               = 0;
			long long B               = 7;
			long long lower           = 0;
			long long upper           = 0;
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			long long K               = 20;
			long long N               = 12;
			long long A               = 21;
			long long B               = 30;
			long long lower           = 1;
			long long upper           = 11;
			long long expected__      = 6;

			clock_t start__           = clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			long long K               = 30;
			long long N               = 89;
			long long A               = 112;
			long long B               = 200;
			long long lower           = 80;
			long long upper           = 88;
			long long expected__      = 9;

			clock_t start__           = clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			long long K               = 890;
			long long N               = 1000;
			long long A               = 1000;
			long long B               = 10000;
			long long lower           = 456;
			long long upper           = 980;
			long long expected__      = 4770;

			clock_t start__           = clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			long long K               = 95060;
			long long N               = 999933;
			long long A               = 49676;
			long long B               = 993369;
			long long lower           = 10987;
			long long upper           = 342940;
			long long expected__      = 313283;

			clock_t start__           = clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
      case 6: {
			long long K               = 9;
			long long N               = 1;
			long long A               = 0;
			long long B               = 7;
			long long lower           = 0;
			long long upper           = 0;
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
/*      case 7: {
			long long K               = ;
			long long N               = ;
			long long A               = ;
			long long B               = ;
			long long lower           = ;
			long long upper           = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
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
