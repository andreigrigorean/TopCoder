// SRM 512, Level 3

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int64 MOD = 1000000007;
const int MAX_N = 202;

class PickAndDelete {
public:
    int N;
    vector<int64> v;
    int64 comb[MAX_N][MAX_N];
    int64 dp[MAX_N][MAX_N];
    
    void precalcComb(int N) {
      for (int i = 0; i <= N; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j)
          comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
      }
    }

    int64 pow(int64 base, int64 exp) {
      if (exp == 0) return 1;
      int64 aux = pow(base, exp / 2);
      return aux * aux % MOD * ((exp & 1) ? base : 1) % MOD;
    }

    int count(vector<string> S)  {
      string tmp;
      FORIT(it, S) tmp += *it;

      istringstream in(tmp);  
      int64 val;
      while (in >> val)
        v.push_back(val);
      v.push_back(0);
      sort(v.begin(), v.end());

      int N = v.size() - 1;
      precalcComb(N);

      dp[0][0] = 1;
      for (int i = 1; i <= N; ++i)
        for (int j = i; j <= N; ++j)
          for (int k = 0; k <= j; ++k)
            dp[i][j] = (dp[i][j] + dp[i - 1][j - k] * pow(v[i] - v[i - 1], k) % MOD * comb[N - j + k][k]) % MOD;
      return (int)dp[N][N];
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
			string S[]                = {"1 2"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string S[]                = {"2 2 2 2 2 2 2 2 2"};
			int expected__            = 512;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string S[]                = {"5", " 1 ", "2"};
			int expected__            = 34;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string S[]                = {"3 ", "14159 265", "3589 7", " 932"};
			int expected__            = 353127147;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string S[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string S[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string S[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
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
