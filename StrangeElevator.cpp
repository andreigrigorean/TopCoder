// SRM 495, Level 3
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int MOD = 1000000007;

class StrangeElevator {
public:
    map< pair<int, int>, int64> memF, memG;

    int64 f(int N, int M) {
      if (N % M) return 0;
      if (memF.find(make_pair(N, M)) != memF.end())
        return memF[make_pair(N, M)];

      int64 sol = 0;
      for (int i = 1; i * i <= N; ++i)
        if (N % i == 0) {
          if (i != N)
            sol = (sol + g(i, M)) % MOD;
          if (i * i != N && i != 1)
            sol = (sol + g(N / i, M)) % MOD;
        }
      return memF[make_pair(N, M)] = sol;
    }

    int64 g(int N, int M) {
      if (N % M) return 0;
      if (N == M) return 1;
      if (memG.find(make_pair(N, M)) != memG.end())
        return memG[make_pair(N, M)];

      int64 sol = 0;
      for (int i = 1; i * i <= N; ++i)
        if (N % i == 0) {
          if (M % (N / i) == 0)
            sol = (sol + f(i, M / (N / i))) % MOD;
          if (i * i != N && i != 1 && M % i == 0)
            sol = (sol + f(N / i, M / i)) % MOD;
        }
      return memG[make_pair(N, M)] = sol;
    }

    int theCount(int N, int M) {
      return (f(N, M) + g(N, M)) % MOD;
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
			int H                     = 58;
			int N                     = 2;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int H                     = 1;
			int N                     = 1;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int H                     = 9;
			int N                     = 3;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int H                     = 120;
			int N                     = 12;
			int expected__            = 30;

			clock_t start__           = clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int H                     = 58585858;
			int N                     = 495;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int H                     = 1000000000;
			int N                     = 100000;
			int expected__            = 46084626;

			clock_t start__           = clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int H                     = ;
			int N                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int H                     = ;
			int N                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = StrangeElevator().theCount(H, N);
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
