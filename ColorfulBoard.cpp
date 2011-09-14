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

const int INF = 0x3f3f3f3f;

class ColorfulBoard {
public:
    bool isAcyclic(vector< vector<bool> > graph) {
      int N = graph.size();
      for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
          for (int j = 0; j < N; ++j)
            if (graph[i][k] && graph[k][j])
              graph[i][j] = true;
      for (int i = 0; i < N; ++i)
        if (graph[i][i])
          return false;
      return true;
    }

    int solve(vector<string> board, int col) {
      int N = board.size();
      int M = board[0].size();
      int sol = N;

      vector<char> line(N);
      for (int i = 0; i < N; ++i)
        line[i] = board[i][col];

      vector< vector<bool> > graph(N + M, vector<bool>(N + M));
      for (int j = 0; j < M; ++j) {
        char ch = '.';
        for (int i = 0; i < N; ++i)
          if (board[i][j] != line[i]) {
            if (ch == '.')
              ch = board[i][j];
            else if (ch != board[i][j])
              return INF;
          }
        if (ch == '.') continue;

        ++sol;
        for (int i = 0; i < N; ++i)
          if (board[i][j] != line[i])
            graph[N + j][i] = true;
          else if (board[i][j] != ch)
            graph[i][N + j] = true;
      }

      return isAcyclic(graph) ? sol : INF;
    }
  
    int solve(vector<string> board) {
      int best = INF;
      int M = board[0].size();

      // choose a column which will not be colored
      for (int col = 0; col < M; ++col)
        best = min(best, solve(board, col));

      return best;
    }

    vector<string> transposed(vector<string> board) {
      int N = board.size();
      int M = board[0].size();
      vector<string> newBoard(M, string(N, ' '));
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
          newBoard[j][i] = board[i][j];
      return newBoard;
    }

    int theMin(vector<string> board) {
      int best = min(solve(board), solve(transposed(board)));
      return best == INF ? -1 : best;
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
			string board[]            = {"SSS",
 "SRR",
 "SMM"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = ColorfulBoard().theMin(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"BBBBBBBB",
 "BBBBBBBB",
 "BBBBBBBB",
 "BBBBBBBB",
 "BBBBBBBB"};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = ColorfulBoard().theMin(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"Ab",
 "bA"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = ColorfulBoard().theMin(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"iiiii",
 "iwiwi"}
;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = ColorfulBoard().theMin(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"ffffffffff",
 "xfxxoofoxo",
 "ffffffffff",
 "xfxxoofoxo",
 "ffffffffff",
 "ooxxoofoxo",
 "xfxxoofoxo",
 "xfxxoxfxxo",
 "ffxxofffxo",
 "xfxxoxfxxo"};
			int expected__            = 17;

			clock_t start__           = clock();
			int received__            = ColorfulBoard().theMin(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulBoard().theMin(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulBoard().theMin(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorfulBoard().theMin(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
