// SRM 520, Level 3

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

const int MOD = 1000000007;
const int MAX_N = 2505;

int dp[MAX_N][MAX_N];
int comb[MAX_N][MAX_N];


class SRMChallengePhase {
public:
    int countWays(vector<string> _attempts, vector<string> _challenges) {
      string attempts;
      FORIT(it, _attempts)
        attempts += *it;

      string challenges;
      FORIT(it, _challenges)
        challenges += *it;

      int N = attempts.size();
      int YY = 0, YN = 0, NY = 0;
      for (int i = 0; i < N; ++i)
        if (attempts[i] == 'Y' && challenges[i] == 'Y') ++YY;
        else if (attempts[i] == 'Y' && challenges[i] == 'N') ++YN;
        else if (attempts[i] == 'N' && challenges[i] == 'Y') ++NY;

      // no solution
      if (NY > YN) return 0;

      // dynamic programming time
      for (int i = 0; i <= N; ++i) {
        dp[i][0] = 1;
        for (int j = 1; j <= i; ++j)
          dp[i][j] = (dp[i - 1][j] + (int64)(i - j) * dp[i - 1][j - 1]) % MOD;
      }

      // precalc comb
      for (int i = 0; i <= N; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j)
          comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
      }

      // dp[YN + YY][YY] * comb[YN][NY] * (N - 1) ^ (YN - NY) * YY! * YN! * NY!
      int64 sol = 1;
      sol = (sol * dp[YN + YY][YY]) % MOD;
      sol = (sol * comb[YN][NY]) % MOD;
      for (int i = 1; i <= YN - NY; ++i)
        sol = (sol * (N - 1)) % MOD;
      for (int i = 1; i <= YY; ++i)
        sol = (sol * i) % MOD;
      for (int i = 1; i <= YN; ++i)
        sol = (sol * i) % MOD;
      for (int i = 1; i <= NY; ++i)
        sol = (sol * i) % MOD;

      return (int)sol;
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
			string codersAttempted[]  = {"YY"};
			string codersChallenged[] = {"NY"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string codersAttempted[]  = {"YY", "NN"};
			string codersChallenged[] = {"N", "NYY"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string codersAttempted[]  = {"YNNN"};
			string codersChallenged[] = {"NYY", "Y"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string codersAttempted[]  = {"N"};
			string codersChallenged[] = {"N"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string codersAttempted[]  = {"YYY"};
			string codersChallenged[] = {"NNY"};
			int expected__            = 24;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			string codersAttempted[]  = {"YY", "N", "YYYY", "NN", "YYYYY"};
			string codersChallenged[] = {"N", "YYYYY", "N", "Y", "N", "YYYY", "N"};
			int expected__            = 807026001;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string codersAttempted[]  = ;
			string codersChallenged[] = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string codersAttempted[]  = ;
			string codersChallenged[] = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string codersAttempted[]  = ;
			string codersChallenged[] = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SRMChallengePhase().countWays(vector <string>(codersAttempted, codersAttempted + (sizeof codersAttempted / sizeof codersAttempted[0])), vector <string>(codersChallenged, codersChallenged + (sizeof codersChallenged / sizeof codersChallenged[0])));
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
