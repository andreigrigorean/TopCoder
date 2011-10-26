// SRM 519, Level 3

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int MOD = 1000000009;
const int PRIMES = 6;

int primes[PRIMES] = {2, 3, 5, 7, 11, 13};
int factors[][2] = {{1, 0}, {0, 1}, {2, 0}, {1, 1}, {3, 0}, {0, 2}, {2, 1}, {4, 0}};


class VerySmoothDecompositions {
public:
    vector<int> N;
    int powers[PRIMES];

    void divide(vector<int> N, int den, vector<int>& out, int& rem) {
      rem = 0;
      out = vector<int>(N.size(), 0);

      for (int i = N.size() - 1; i >= 0; --i) {
        int tmp = 10 * rem + N[i];
        out[i] = tmp / den;
        rem = tmp % den;
      }

      while (out.back() == 0)
        out.pop_back();
    }

    vector<int> parse(vector<string>& digits) {
      vector<int> sol;
      FORIT(it, digits)
      FORIT(it2, *it)
        sol.push_back(*it2 - '0');
      reverse(sol.begin(), sol.end());
      return sol;
    }

    int solve(vector<string> digits) {
      // parse the number
      N = parse(digits);

      // factorize the number
      memset(powers, 0, sizeof(powers));
      for (int i = 0; i < PRIMES; ++i) {
        while (true) {
          vector<int> newN;
          int rem = 0;
          divide(N, primes[i], newN, rem);

          if (rem > 0) break;
          ++powers[i];
          N = newN;
        }
      }

      // no solution
      if (N.size() > 1 || N[0] != 1)
        return 0;

      // dp[i][j] = number of decompositionis using numbers of the form 2^i * 3^j
      vector< vector<int> > dp = vector< vector<int> >(powers[0] + 1, vector<int>(powers[1] + 1, 0));
      dp[0][0] = 1;
      for (int k = 0; k < 8; ++k)
        for (int i = 0; i <= powers[0]; ++i)
          for (int j = 0; j <= powers[1]; ++j)
            if (i >= factors[k][0] && j >= factors[k][1])
              dp[i][j] = (dp[i][j] + dp[i - factors[k][0]][j - factors[k][1]]) % MOD;

      // compute partial sums over dp
      for (int i = 0; i <= powers[0]; ++i)
        for (int j = 1; j <= powers[1]; ++j)
          dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;

      // find the result
      int64 sol = 0;
      for (int i = 0; i <= min(powers[0], powers[2]); ++i)              // number of 2 * 5
        for (int j = 0; j <= min(powers[0] - i, powers[3]); ++j) {      // number of 2 * 7
          int kmax = powers[1];                                         // max number of 3 * 5
          int kmin = powers[1] - min(powers[1], powers[2] - i);         // min number of 3 * 5
          sol = (sol + dp[powers[0] - i - j][kmax]) % MOD;
          if (kmin > 0)
            sol = (sol + MOD - dp[powers[0] - i - j][kmin - 1]) % MOD;
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
			string digits[]           = {"47"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = VerySmoothDecompositions().solve(vector <string>(digits, digits + (sizeof digits / sizeof digits[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string digits[]           = {"2"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = VerySmoothDecompositions().solve(vector <string>(digits, digits + (sizeof digits / sizeof digits[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string digits[]           = {"10"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = VerySmoothDecompositions().solve(vector <string>(digits, digits + (sizeof digits / sizeof digits[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string digits[]           = {"36"};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = VerySmoothDecompositions().solve(vector <string>(digits, digits + (sizeof digits / sizeof digits[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string digits[]           = {"1","21"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = VerySmoothDecompositions().solve(vector <string>(digits, digits + (sizeof digits / sizeof digits[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			string digits[]           = {"1024"};
			int expected__            = 23;

			clock_t start__           = clock();
			int received__            = VerySmoothDecompositions().solve(vector <string>(digits, digits + (sizeof digits / sizeof digits[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			string digits[]           = {"1099197146547500000"};
			int expected__            = 37;

			clock_t start__           = clock();
			int received__            = VerySmoothDecompositions().solve(vector <string>(digits, digits + (sizeof digits / sizeof digits[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
/*      case 7: {
			string digits[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = VerySmoothDecompositions().solve(vector <string>(digits, digits + (sizeof digits / sizeof digits[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string digits[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = VerySmoothDecompositions().solve(vector <string>(digits, digits + (sizeof digits / sizeof digits[0])));
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
