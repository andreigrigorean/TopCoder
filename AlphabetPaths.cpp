// SRM 523, Level 3
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int MAX_N = 21;
const int SIGMA = 21;

char alphabet[21] = {'A', 'B', 'C', 'D', 'E', 'F', 'Z', 'H', 'I', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V', 'X'};
int ord[26] = {};

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int freq[1 << MAX_N];
int bit_count[1 << MAX_N];

class AlphabetPaths {
public:
    int n, m;
    vector<string> A;
    vector<int> paths;
 
    inline int get_ord(char ch) {
        return ord[ch - 'A'];
    }

    inline bool valid_pos(int i, int j) {
        return (0 <= i && i < n && 0 <= j && j < m);
    }

    void back(int i, int j, int mask) {
        if (bit_count[mask] == (SIGMA + 1) / 2) {
            ++freq[mask];
            paths.push_back(mask);
            return;
        }
        for (int k = 0; k < 4; ++k) {
            int ii = i + dx[k];
            int jj = j + dy[k];
            if (valid_pos(ii, jj) && A[ii][jj] != '.' && ((mask & (1 << get_ord(A[ii][jj]))) == 0))
                back(ii, jj, mask | (1 << get_ord(A[ii][jj])));
        }
    }

    inline int complement(int mask, int start) {
        return ((1 << SIGMA) - 1) ^ mask ^ (1 << start);
    }

    long long count(vector<string> _A) {
       // preproc alphabet
       for (int i = 0; i < SIGMA; ++i)
            ord[alphabet[i] - 'A'] = i;
       for (int i = 0; i < (1 << (SIGMA - 1)); ++i) {
           bit_count[2 * i] = bit_count[i];
           bit_count[2 * i + 1] = bit_count[i] + 1;
       }

        A = _A;
        n = A.size();
        m = A[0].size();

        int64 sol = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (A[i][j] == '.') continue;
                paths.clear();
                back(i, j, 1 << get_ord(A[i][j]));
                FORIT(it, paths) {
                    sol += (int64)freq[*it] * freq[complement(*it, get_ord(A[i][j]))];
                    freq[*it] = 0;
                }
            }
        return sol * 2;
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
			string letterMaze[]       = {"ABCDEFZHIXKLMNOPQRST",
 "...................V"};
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string letterMaze[]       = {".................VT.",
 "....................",
 "ABCDEFZHIXKLMNOPQRS.",
 "..................S.",
 ".................VT."};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string letterMaze[]       = {"TBCDE.PQRSA", 
 "FZHIXKLMNOV"};
			long long expected__      = 50;

			clock_t start__           = clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string letterMaze[]       = {"ABCDEF.",
 "V....Z.",
 "T....H.",
 "S....I.",
 "R....X.",
 "KLMNOPQ"};
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string letterMaze[]       = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string letterMaze[]       = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string letterMaze[]       = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
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
