// SRM 506, Level 3

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int MAX_N = 155;
const int INF = 0x3f3f3f3f;

int64 dp[MAX_N][MAX_N][MAX_N];


class SlimeXSlimeRancher {
public:
    class SortedVal {
      public:
        int value;
        int initPos;

        SortedVal(int _value, int _initPos) : value(_value), initPos(_initPos) {}
    
        bool operator<(const SortedVal& other) const {
          return value < other.value;
        }
    };

    vector<int> slimes[3];
    vector<SortedVal> sortedVals[3];

    vector<int> parse(vector<string>& v) {
      string tmp;
      FORIT(it, v)
        tmp += *it;

      istringstream in(tmp);
      vector<int> numbers;
      int val;

      while (in >> val)
        numbers.push_back(val);

      return numbers;
    }

    vector<SortedVal> buildSortedVals(vector<int> slime) {
      vector<SortedVal> sortedVals;
      for (int i = 0; i < (int)slime.size(); ++i)
        sortedVals.push_back(SortedVal(slime[i], i));
      sort(sortedVals.begin(), sortedVals.end());
      return sortedVals;
    }

    bool isInside(int i, int j, int k, int index) {
      return 
          sortedVals[0][i].value >= slimes[0][index] &&
          sortedVals[1][j].value >= slimes[1][index] &&
          sortedVals[2][k].value >= slimes[2][index];
    }

    int64 manhattan(int i, int j, int k, int index) {
      return
          (int64)(sortedVals[0][i].value - slimes[0][index]) +
          (int64)(sortedVals[1][j].value - slimes[1][index]) +
          (int64)(sortedVals[2][k].value - slimes[2][index]);
    }

    int64 train(vector<string> first_slime, vector<string> second_slime, vector<string> third_slime) {
      slimes[0] = parse(first_slime);
      slimes[1] = parse(second_slime);
      slimes[2] = parse(third_slime);

      sortedVals[0] = buildSortedVals(slimes[0]);
      sortedVals[1] = buildSortedVals(slimes[1]);
      sortedVals[2] = buildSortedVals(slimes[2]);

      int N = slimes[0].size();

      memset(dp, INF, sizeof(dp));
      dp[0][0][0] = 0;

      for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
          for (int k = 0; k < N; ++k) {
            // move to (i + 1, j, k)
            if (i + 1 < N) {
              if (isInside(i + 1, j, k, sortedVals[0][i + 1].initPos))
                dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k] + manhattan(i + 1, j, k, sortedVals[0][i + 1].initPos));
              else
                dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k]);
            }

            // move to (i, j + 1, k)
            if (j + 1 < N) {
              if (isInside(i, j + 1, k, sortedVals[1][j + 1].initPos))
                dp[i][j + 1][k] = min(dp[i][j + 1][k], dp[i][j][k] + manhattan(i, j + 1, k, sortedVals[1][j + 1].initPos));
              else
                dp[i][j + 1][k] = min(dp[i][j + 1][k], dp[i][j][k]);
            }

            // move to (i, j, k + 1)
            if (k + 1 < N) {
              if (isInside(i, j, k + 1, sortedVals[2][k + 1].initPos))
                dp[i][j][k + 1] = min(dp[i][j][k + 1], dp[i][j][k] + manhattan(i, j, k + 1, sortedVals[2][k + 1].initPos));
              else
                dp[i][j][k + 1] = min(dp[i][j][k + 1], dp[i][j][k]);
            }
          }

      return dp[N - 1][N - 1][N - 1];
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
			string first_slime[]      = {"1 6 2"};
			string second_slime[]     = {"1 3 5"};
			string third_slime[]      = {"5 4 3"};
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = SlimeXSlimeRancher().train(vector <string>(first_slime, first_slime + (sizeof first_slime / sizeof first_slime[0])), vector <string>(second_slime, second_slime + (sizeof second_slime / sizeof second_slime[0])), vector <string>(third_slime, third_slime + (sizeof third_slime / sizeof third_slime[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string first_slime[]      = {"3 2 1"};
			string second_slime[]     = {"6 5 4"};
			string third_slime[]      = {"9 8 7"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = SlimeXSlimeRancher().train(vector <string>(first_slime, first_slime + (sizeof first_slime / sizeof first_slime[0])), vector <string>(second_slime, second_slime + (sizeof second_slime / sizeof second_slime[0])), vector <string>(third_slime, third_slime + (sizeof third_slime / sizeof third_slime[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string first_slime[]      = {"1 2", "3 4"};
			string second_slime[]     = {"12 3 ", "4"};
			string third_slime[]      = {"1 2 ", "34"};
			long long expected__      = 36;

			clock_t start__           = clock();
			long long received__      = SlimeXSlimeRancher().train(vector <string>(first_slime, first_slime + (sizeof first_slime / sizeof first_slime[0])), vector <string>(second_slime, second_slime + (sizeof second_slime / sizeof second_slime[0])), vector <string>(third_slime, third_slime + (sizeof third_slime / sizeof third_slime[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string first_slime[]      = {"1 1 1 1000000000 1000000000 1000000000"};
			string second_slime[]     = {"1000000000 1000000000 1000000000 1 1 1"};
			string third_slime[]      = {"1 1 1 2 2 2"};
			long long expected__      = 2999999997LL;

			clock_t start__           = clock();
			long long received__      = SlimeXSlimeRancher().train(vector <string>(first_slime, first_slime + (sizeof first_slime / sizeof first_slime[0])), vector <string>(second_slime, second_slime + (sizeof second_slime / sizeof second_slime[0])), vector <string>(third_slime, third_slime + (sizeof third_slime / sizeof third_slime[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			string first_slime[]      = {"1 2 1 1 2 2 2 2 ", "3 1 1 3 1 1 3 3 2 2 3 ", "2 2 3 3 3 3 3 3 4 1", " 1 4 1 1 4 1 ", "1 4 4 2 2 4 2 2 4 2", " 2 4 4 3 3 4 3 3 4", " 3 3 4 4 4 4 4 4 4", " 4 5 1 1 5 1 1 5 1 1 5", " 1 1 5 5 2 2 ", "5 2 2 5 2", " 2 5 2 2 5 5 3 3 5 ", "3 3 5 3 3 5 3 3 5 5", " 4 4 5 4 4 5 4 4 5 4 4 5 5", " 5 5 5 5 5 5 5 5"};
			string second_slime[]     = {"1 1 2 1 1 2 2 2 ", "1 3 1 1 3 2 1 2 3 1 2 ", "3 2 2 3 3 3 3 3 1 4", " 1 1 4 2 1 4 ", "3 1 2 4 1 2 4 2 2 4", " 3 2 3 4 1 3 4 2 3", " 4 3 3 4 4 4 4 4 4", " 4 1 5 1 1 5 2 1 5 3 1", " 5 4 1 2 5 1 ", "2 5 2 2 5", " 3 2 5 4 2 3 5 1 3 ", "5 2 3 5 3 3 5 4 3 4", " 5 1 4 5 2 4 5 3 4 5 4 4 5", " 5 5 5 5 5 5 5 5"};
			string third_slime[]      = {"1 1 1 2 2 1 1 2 ", "1 1 3 2 2 3 3 1 1 3 2 ", "2 3 3 1 1 2 2 3 1 1", " 4 2 2 4 3 3 ", "4 4 1 1 4 2 2 4 3 3", " 4 4 1 1 4 2 2 4 3", " 3 4 4 1 1 2 2 3 3", " 4 1 1 5 2 2 5 3 3 5 4", " 4 5 5 1 1 5 ", "2 2 5 3 3", " 5 4 4 5 5 1 1 5 2 ", "2 5 3 3 5 4 4 5 5 1", " 1 5 2 2 5 3 3 5 4 4 5 5 1", " 1 2 2 3 3 4 4 5"};
			long long expected__      = 340;

			clock_t start__           = clock();
			long long received__      = SlimeXSlimeRancher().train(vector <string>(first_slime, first_slime + (sizeof first_slime / sizeof first_slime[0])), vector <string>(second_slime, second_slime + (sizeof second_slime / sizeof second_slime[0])), vector <string>(third_slime, third_slime + (sizeof third_slime / sizeof third_slime[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
/*      case 5: {
			string first_slime[]      = ;
			string second_slime[]     = ;
			string third_slime[]      = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SlimeXSlimeRancher().train(vector <string>(first_slime, first_slime + (sizeof first_slime / sizeof first_slime[0])), vector <string>(second_slime, second_slime + (sizeof second_slime / sizeof second_slime[0])), vector <string>(third_slime, third_slime + (sizeof third_slime / sizeof third_slime[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string first_slime[]      = ;
			string second_slime[]     = ;
			string third_slime[]      = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SlimeXSlimeRancher().train(vector <string>(first_slime, first_slime + (sizeof first_slime / sizeof first_slime[0])), vector <string>(second_slime, second_slime + (sizeof second_slime / sizeof second_slime[0])), vector <string>(third_slime, third_slime + (sizeof third_slime / sizeof third_slime[0])));
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
