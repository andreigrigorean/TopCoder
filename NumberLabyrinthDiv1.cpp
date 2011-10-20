// SRM 509, Level 3

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
#define x first
#define y second

const int MOD = 1000000009;
const int MAX_COORD = 1000001;
const int MAX_N = 160;
const int MAX_K = 12;

int64 fact[MAX_COORD];
int64 invFact[MAX_COORD];

int64 totalWays[MAX_N][MAX_N][MAX_K];
int64 emptyWays[MAX_N][MAX_N][MAX_K];
int64 nonEmptyWays[MAX_N][MAX_N][MAX_K];


class NumberLabyrinthDiv1 {
public:
    class Cell {
      public:
        int x, y, val;
        Cell(int _x, int _y, int _val) : x(_x), y(_y), val(_val) {}
    };

    vector<Cell> cells;

    bool containsPos(vector<Cell>& cells, int x, int y) {
      FORIT(it, cells)
        if (it->x == x && it->y == y)
          return true;
      return false;
    }

    int64 comb(int n, int k) {
      if (k < 0 || k > n) return 0;
      return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
    }

    int64 getTotalWays(int c1, int c2, int steps) {
      if (totalWays[c1][c2][steps] != -1)
        return totalWays[c1][c2][steps];
      totalWays[c1][c2][steps] = 0;

      if (c1 == c2) return totalWays[c1][c2][steps] = steps == 0;

      int dx = cells[c2].x - cells[c1].x;
      int dy = cells[c2].y - cells[c1].y;

      if (dx < 0 || dy < 0) return 0;
      if (dx == 0 && dy > 0)
        return totalWays[c1][c2][steps] = comb(dy - 1, steps - 1);
      if (dx > 0 && dy == 0)
        return totalWays[c1][c2][steps] = comb(dx - 1, steps - 1);

      for (int rightSteps = 1; rightSteps < steps; ++rightSteps)
        totalWays[c1][c2][steps] = (totalWays[c1][c2][steps] +
            comb(dx - 1, rightSteps - 1) * comb(dy - 1, steps - rightSteps - 1) % MOD * comb(steps, rightSteps)) % MOD;
      return totalWays[c1][c2][steps];
    }

    vector<int> getInnerCells(int c1, int c2) {
      vector<int> ret;
      for (int i = 0; i < (int)cells.size(); ++i)
        if (i != c1 && i != c2 &&
            cells[c1].x <= cells[i].x && cells[i].x <= cells[c2].x &&
            cells[c1].y <= cells[i].y && cells[i].y <= cells[c2].y)
          ret.push_back(i);
      return ret;
    }

    int getCellIndex(int x, int y) {
      for (size_t i = 0; i < cells.size(); ++i)
        if (cells[i].x == x && cells[i].y == y)
          return i;
      return -1;
    }

    int64 getNonEmptyWays(int c1, int c2, int steps) {
      if (nonEmptyWays[c1][c2][steps] != -1)
        return nonEmptyWays[c1][c2][steps];
      nonEmptyWays[c1][c2][steps] = 0;

      vector<int> innerCells = getInnerCells(c1, c2);
      for (size_t i = 0; i < innerCells.size(); ++i)
        if (cells[innerCells[i]].val > 0)
          for (int k = 1; k <= steps; ++k) {
            int64 empty = 0;

            int newCell = getCellIndex(cells[innerCells[i]].x + cells[innerCells[i]].val, cells[innerCells[i]].y);
            if (cells[newCell].val == 0 || newCell == c2)
              if (cells[newCell].x <= cells[c2].x && cells[newCell].y <= cells[c2].y)
                empty = getEmptyWays(newCell, c2, steps - k);

            newCell = getCellIndex(cells[innerCells[i]].x, cells[innerCells[i]].y + cells[innerCells[i]].val);
            if (cells[newCell].val == 0 || newCell == c2)
              if (cells[newCell].x <= cells[c2].x && cells[newCell].y <= cells[c2].y)
                empty = (empty + getEmptyWays(newCell, c2, steps - k)) % MOD;

            nonEmptyWays[c1][c2][steps] = (nonEmptyWays[c1][c2][steps] +
                (getNonEmptyWays(c1, innerCells[i], k) + getEmptyWays(c1, innerCells[i], k)) * empty) % MOD;
          }

       return nonEmptyWays[c1][c2][steps];
    }

    int64 getEmptyWays(int c1, int c2, int steps) {
      if (steps < 0) return 0;
      if (emptyWays[c1][c2][steps] != -1)
        return emptyWays[c1][c2][steps];
      emptyWays[c1][c2][steps] = 0;

      if (c1 == c2)
        return emptyWays[c1][c2][steps] = !steps ? 1 : 0;

      emptyWays[c1][c2][steps] = getTotalWays(c1, c2, steps);
      vector<int> innerCells = getInnerCells(c1, c2);
      for (size_t i = 0; i < innerCells.size(); ++i)
        if (cells[innerCells[i]].val > 0)
          for (int k = 1; k < steps; ++k)
            emptyWays[c1][c2][steps] = (emptyWays[c1][c2][steps] + MOD -
                (getTotalWays(c1, innerCells[i], k)) *
                getEmptyWays(innerCells[i], c2, steps - k) % MOD) % MOD;
      return emptyWays[c1][c2][steps];
    }

    int64 pow(int64 base, int exp) {
      if (!exp) return 1;
      int64 half = pow(base, exp / 2);
      return half * half % MOD * (exp & 1 ? base : 1) % MOD;
    }

    void preprocFact() {
      fact[0] = 1;
      for (int i = 1; i < MAX_COORD; ++i)
        fact[i] = fact[i - 1] * i % MOD;

      invFact[MAX_COORD - 1] = pow(fact[MAX_COORD - 1], MOD - 2);
      for (int i = MAX_COORD - 2; i >= 0; --i)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }

    int getNumberOfPaths(vector<int> X, vector<int> Y, vector<int> val, int xFinish, int yFinish, int K) {
      preprocFact();

      // find important cells
      cells.push_back(Cell(0, 0, 0));
      cells.push_back(Cell(xFinish, yFinish, 0));
      for (size_t i = 0; i < X.size(); ++i)
        cells.push_back(Cell(X[i], Y[i], val[i]));
      for (size_t i = 0; i < X.size(); ++i) {
        if (!containsPos(cells, X[i] + val[i], Y[i]))
          cells.push_back(Cell(X[i] + val[i], Y[i], 0));
        if (!containsPos(cells, X[i], Y[i] + val[i]))
          cells.push_back(Cell(X[i], Y[i] + val[i], 0));
      }

      memset(totalWays, -1, sizeof(totalWays));
      memset(emptyWays, -1, sizeof(emptyWays));
      memset(nonEmptyWays, -1, sizeof(nonEmptyWays));

      int64 sol = 0;
      for (int i = 2; i <= K; ++i)
        sol = (sol + getEmptyWays(0, 1, i) + getNonEmptyWays(0, 1, i)) % MOD;
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
			int X[]                   = {};
			int Y[]                   = {};
			int val[]                 = {};
			int xFinish               = 3;
			int yFinish               = 3;
			int K                     = 2;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = NumberLabyrinthDiv1().getNumberOfPaths(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), xFinish, yFinish, K);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int X[]                   = {};
			int Y[]                   = {};
			int val[]                 = {};
			int xFinish               = 3;
			int yFinish               = 3;
			int K                     = 3;
			int expected__            = 14;

			clock_t start__           = clock();
			int received__            = NumberLabyrinthDiv1().getNumberOfPaths(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), xFinish, yFinish, K);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int X[]                   = {2};
			int Y[]                   = {2};
			int val[]                 = {1};
			int xFinish               = 3;
			int yFinish               = 3;
			int K                     = 3;
			int expected__            = 18;

			clock_t start__           = clock();
			int received__            = NumberLabyrinthDiv1().getNumberOfPaths(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), xFinish, yFinish, K);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int X[]                   = {1, 3, 6};
			int Y[]                   = {1, 3, 6};
			int val[]                 = {2, 2, 2};
			int xFinish               = 5;
			int yFinish               = 5;
			int K                     = 4;
			int expected__            = 210;

			clock_t start__           = clock();
			int received__            = NumberLabyrinthDiv1().getNumberOfPaths(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), xFinish, yFinish, K);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int X[]                   = {1, 19, 20, 21, 21, 21, 20, 19, 19};
			int Y[]                   = {1, 11, 11, 11, 10, 9, 9, 9, 10};
			int val[]                 = {1, 2, 2, 2, 2, 2, 2, 2, 2};
			int xFinish               = 20;
			int yFinish               = 10;
			int K                     = 4;
			int expected__            = 1778;

			clock_t start__           = clock();
			int received__            = NumberLabyrinthDiv1().getNumberOfPaths(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), xFinish, yFinish, K);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			int X[]                   = {13, 224, 77, 509, 1451, 43, 379, 142, 477};
			int Y[]                   = {1974, 375, 38, 783, 3, 1974, 1790, 1008, 2710};
			int val[]                 = {30, 1845, 360, 11, 837, 84, 210, 4, 6704};
			int xFinish               = 509;
			int yFinish               = 2011;
			int K                     = 10;
			int expected__            = 196052726;

			clock_t start__           = clock();
			int received__            = NumberLabyrinthDiv1().getNumberOfPaths(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), xFinish, yFinish, K);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int X[]                   = ;
			int Y[]                   = ;
			int val[]                 = ;
			int xFinish               = ;
			int yFinish               = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NumberLabyrinthDiv1().getNumberOfPaths(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), xFinish, yFinish, K);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int X[]                   = ;
			int Y[]                   = ;
			int val[]                 = ;
			int xFinish               = ;
			int yFinish               = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NumberLabyrinthDiv1().getNumberOfPaths(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), xFinish, yFinish, K);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int X[]                   = ;
			int Y[]                   = ;
			int val[]                 = ;
			int xFinish               = ;
			int yFinish               = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NumberLabyrinthDiv1().getNumberOfPaths(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(val, val + (sizeof val / sizeof val[0])), xFinish, yFinish, K);
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
