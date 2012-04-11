// SRM 540, Level 3

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

const int MAX_N = 102;
const int64 MOD = (int64)(1e9 + 7);

int64 D[MAX_N][MAX_N];

class ProductQuery {
public:
    struct Query {
        int start;
        int val;

        Query() {}

        Query(int start, int val) {
            this->start = start;
            this->val = val;
        }

        bool operator<(const Query &other) const {
            return start > other.start;
        }

        friend ostream& operator<<(ostream& out, const Query& query) {
            return out << query.start << " " << query.val;
        }
    };

    vector<Query> queries[MAX_N];

    int theInput(int N, vector<int> Qfrom, vector<int> Qto, vector<int> output) {
        return solve(N, Qfrom, Qto, output, 2) * solve(N, Qfrom, Qto, output, 5) % MOD;
    }

    int64 solve(int N, vector<int> Qfrom, vector<int> Qto, vector<int> output, int base) {
        // Split the queries so there are no two queries with the same endpoint.
        for (int i = 1; i <= N; ++i)
            queries[i].clear();
        for (size_t i = 0; i < Qfrom.size(); ++i)
            queries[Qto[i] + 1].push_back(Query(Qfrom[i] + 1, output[i] % base));
        
        for (int i = N; i > 0; --i) {
            sort(queries[i].begin(), queries[i].end());
            for (size_t j = 0; j + 1 < queries[i].size(); ++j)
                if (queries[i][j].start == queries[i][j + 1].start) {
                    // No solution: same query, different results
                    if (queries[i][j].val != queries[i][j + 1].val)
                        return 0;
                } else {
                    // No solution: i1 < i2 <= j, i1...j != 0, i2...j == 0
                    if (queries[i][j].val == 0 && queries[i][j + 1].val != 0)
                        return 0;

                    if (queries[i][j].val != 0) { 
                        int new_val = queries[i][j + 1].val * mod_inv(queries[i][j].val, base) % base;
                        queries[queries[i][j].start - 1].push_back(Query(queries[i][j + 1].start, new_val));
                    }
                }
            queries[i].resize(min(1, (int)queries[i].size()));
        }

        // Dynammic programming time, yay!
        // D[i][j] = number of ways to choose the first i numbers if the last 0 is the jth element.
        memset(D, 0, sizeof(D));
        D[0][0] = 1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j <= i; ++j) {
                if (D[i][j] == 0) continue;

                // No endpoint at i + 1
                if (queries[i + 1].size() == 0) {
                    add_mod(D[i + 1][i + 1], D[i][j]);
                    add_mod(D[i + 1][j], D[i][j] * (base - 1) % MOD);
                } else {
                    int start = queries[i + 1][0].start;
                    int val = queries[i + 1][0].val;

                    if (val == 0) {
                        if (j < start)
                            add_mod(D[i + 1][i + 1], D[i][j]);
                        else {
                            add_mod(D[i + 1][i + 1], D[i][j]);
                            add_mod(D[i + 1][j], D[i][j] * (base - 1) % MOD);
                        }
                    } else {
                        if (j < start)
                            add_mod(D[i + 1][j], D[i][j]);
                    }
                }
            }

        int64 ans = 0;
        for (int i = 0; i <= N; ++i)
            add_mod(ans, D[N][i]);
        return ans;
    }

    void add_mod(int64& a, int64 b) {
        a = (a + b) % MOD;
    }

    int mod_inv(int x, int mod) {
        int res = 1;
        for (int i = 1; i <= mod - 2; ++i)
            res = res * x % mod;
        return res;
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
			int N                     = 3;
			int Qfrom[]               = {0};
			int Qto[]                 = {0};
			int output[]              = {5};
			int expected__            = 100;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 5;
			int Qfrom[]               = {0, 2, 0};
			int Qto[]                 = {1, 4, 4};
			int output[]              = {3, 4, 6};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 3;
			int Qfrom[]               = {0, 1};
			int Qto[]                 = {1, 2};
			int output[]              = {5, 8};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 8;
			int Qfrom[]               = {2, 0, 3, 6};
			int Qto[]                 = {3, 7, 4, 6};
			int output[]              = {2, 0, 6, 7};
			int expected__            = 118080;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 20;
			int Qfrom[]               = {9, 6, 2, 3, 1, 3, 12, 3, 4, 6, 10, 18, 10, 11, 15, 5};
			int Qto[]                 = {12, 12, 4, 13, 7, 14, 17, 10, 5, 13, 11, 19, 17, 14, 17, 8};
			int output[]              = {7, 5, 7, 5, 0, 5, 8, 5, 3, 5, 3, 9, 4, 1, 6, 5};
			int expected__            = 276398080;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 58;
			int Qfrom[]               = {5, 5};
			int Qto[]                 = {8, 8};
			int output[]              = {1, 2};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

       case 6: {
            int N                     = 63; 
            int Qfrom[]               = {10, 5, 38, 8, 6, 16, 26, 15, 6, 52, 36, 9, 5, 47, 23, 34, 54, 16, 12, 45, 16, 17, 19, 10, 18, 18, 15, 25, 16, 1, 46, 19, 7, 6, 23, 36, 46, 3, 60, 50, 1, 2, 44, 19};
            int Qto[]                 = {15, 19, 49, 30, 57, 46, 30, 44, 18, 57, 38, 19, 20, 59, 59, 45, 60, 44, 15, 55, 42, 58, 60, 61, 34, 52, 41, 30, 29, 39, 50, 56, 19, 6, 45, 55, 56, 6, 60, 55, 53, 35, 60, 22};
            int output[]              = {3, 0, 7, 0, 0, 9, 7, 1, 0, 5, 9, 0, 0, 5, 5, 1, 5, 7, 9, 5, 3, 5, 5, 5, 1, 3, 3, 1, 3, 0, 9, 5, 0, 9, 7, 5, 5, 1, 3, 5, 0, 0, 5, 7};
			int expected__            = 97245661;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
/*      case 7: {
			int N                     = ;
			int Qfrom[]               = ;
			int Qto[]                 = ;
			int output[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int Qfrom[]               = ;
			int Qto[]                 = ;
			int output[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
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
