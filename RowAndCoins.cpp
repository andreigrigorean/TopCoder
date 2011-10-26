// SRM 522, Level 1

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

const int MAX_N = 16;

class RowAndCoins {
public:
    int n;
    string cells;
    int win[1 << MAX_N][2];

    bool canWin(int conf, int player) {
      if (win[conf][player] != -1)
        return win[conf][player];

      int state[MAX_N];
      for (int i = 0; i < n; ++i)
        if (conf & (1 << i)) state[i] = 1;
        else state[i] = 0;

      // check for game ending
      int empty = 0, pos = -1;
      for (int i = 0; i < n; ++i)
        if (!state[i]) {
          ++empty;
          pos = i;
        }
      if (empty == 1) { 
        if (player == 0) 
          return (win[conf][player] = cells[pos] == 'R');
        else
          return (win[conf][player] = cells[pos] == 'B');
      }

      // try every possible move
      for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j) {
          if (j - i + 1 == empty) continue;

          bool ok = true;
          for (int k = i; k <= j; ++k)
            if (state[k]) ok = false;
          if (!ok) continue;

          int newConf = conf;
          for (int k = i; k <= j; ++k)
            newConf |= 1 << k;
          if (!canWin(newConf, 1 ^ player))
            return (win[conf][player] = 1);
        }

        return (win[conf][player] = 0);
    }
  
    string getWinner(string _cells) {
      cells = _cells;
      n = cells.size();
      memset(win, -1, sizeof(win));
      if (canWin(0, 0)) return "Alice";
      return "Bob";
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
			string cells              = "ABBB";
			string expected__         = "Alice";

			clock_t start__           = clock();
			string received__         = RowAndCoins().getWinner(cells);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string cells              = "BBBB";
			string expected__         = "Bob";

			clock_t start__           = clock();
			string received__         = RowAndCoins().getWinner(cells);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string cells              = "BA";
			string expected__         = "Alice";

			clock_t start__           = clock();
			string received__         = RowAndCoins().getWinner(cells);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string cells              = "BABBABBB";
			string expected__         = "Bob";

			clock_t start__           = clock();
			string received__         = RowAndCoins().getWinner(cells);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string cells              = "ABABBBABAABBAA";
			string expected__         = "Alice";

			clock_t start__           = clock();
			string received__         = RowAndCoins().getWinner(cells);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			string cells              = "BBBAAABBAAABBB";
			string expected__         = "Bob";

			clock_t start__           = clock();
			string received__         = RowAndCoins().getWinner(cells);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string cells              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = RowAndCoins().getWinner(cells);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string cells              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = RowAndCoins().getWinner(cells);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string cells              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = RowAndCoins().getWinner(cells);
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
