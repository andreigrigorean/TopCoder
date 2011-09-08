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

const int64 MOD = 1000000007;
const int MAX_N = 27;
const int MAX_M = 77;

int64 comb[MAX_M][MAX_M];
int64 singleRow[MAX_M][MAX_N][MAX_M];
int64 colorRow[MAX_M][MAX_M];
int64 buildings[MAX_N][MAX_M][MAX_M];

class CubeBuilding {
public:
    int N, M;
    int getCount(int R, int G, int B, int _N) {
      N = _N;
      M = R + G + B;

      // compute combinations
      for (int i = 0; i <= M; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j)
          comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
      }

      // singleRow[i][j][k] - number of single row buildings with:
      // i total cubes (not taking into account their color)
      // j length
      // k maximum height
      singleRow[0][0][0] = 1;
      for (int i = 0; i <= M; ++i)
        for (int j = 0; j < N; ++j)
          for (int k = 0; k <= M; ++k)
            if (singleRow[i][j][k] > 0) {
              for (int newCol = 0; i + newCol <= M; ++newCol)
                singleRow[i + newCol][j + 1][max(k, newCol)] = 
                    (singleRow[i + newCol][j + 1][max(k, newCol)] + singleRow[i][j][k]) % MOD;
            }

      // colorRow[i][j] - number of single row buildings with:
      // i "good" cubes
      // j "bad" cubes
      for (int i = 0; i <= M; ++i)
        for (int k = 0; k <= M && k <= i; ++k)
          for (int good = k; good <= i; ++good)
            colorRow[good][i - good] =
                (colorRow[good][i - good] + singleRow[i][N][k] * comb[i - k][good - k]) % MOD;

      // buildings[i][j][k] - number of nice buildings with:
      // i columns
      // j "good" cubes
      // k "bad" cubes
      buildings[0][0][0] = 1;
      for (int i = 0; i < N; ++i)
        for (int j = 0; j <= M; ++j)
          for (int k = 0; j + k <= M; ++k)
            if (buildings[i][j][k]) {
              for (int newJ = 0; newJ + j + k <= M; ++newJ)
                for (int newK = 0; newK + newJ + j + k <= M; ++newK)
                  buildings[i + 1][j + newJ][k + newK] =
                      (buildings[i + 1][j + newJ][k + newK] + buildings[i][j][k] * colorRow[newJ][newK]) % MOD;
            }

      int64 sol = 0;
      sol = (sol + buildings[N][R][G + B] * comb[G + B][G]) % MOD;
      sol = (sol + buildings[N][G][R + B] * comb[R + B][R]) % MOD;
      sol = (sol + buildings[N][B][R + G] * comb[R + G][R]) % MOD;
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
			int R                     = 1;
			int G                     = 0;
			int B                     = 1;
			int N                     = 2;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = CubeBuilding().getCount(R, G, B, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int R                     = 1;
			int G                     = 1;
			int B                     = 2;
			int N                     = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = CubeBuilding().getCount(R, G, B, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int R                     = 2;
			int G                     = 2;
			int B                     = 1;
			int N                     = 3;
			int expected__            = 162;

			clock_t start__           = clock();
			int received__            = CubeBuilding().getCount(R, G, B, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int R                     = 0;
			int G                     = 0;
			int B                     = 10;
			int N                     = 12;
			int expected__            = 372185933;

			clock_t start__           = clock();
			int received__            = CubeBuilding().getCount(R, G, B, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int R                     = ;
			int G                     = ;
			int B                     = ;
			int N                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CubeBuilding().getCount(R, G, B, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int R                     = ;
			int G                     = ;
			int B                     = ;
			int N                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CubeBuilding().getCount(R, G, B, N);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int R                     = ;
			int G                     = ;
			int B                     = ;
			int N                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CubeBuilding().getCount(R, G, B, N);
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
