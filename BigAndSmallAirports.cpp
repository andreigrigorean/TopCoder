// SRM 529, Level 3
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

class BigAndSmallAirports {
public:
    int64 all_pairs(int64 Xmin, int64 Nlo, int64 Nhi) {
        Nlo = max(Nlo, Xmin);
        if (Nlo > Nhi) return 0;
        return (Nlo - Xmin + 1) * (Nhi - Nlo + 1) + (Nhi - Nlo) * (Nhi - Nlo + 1) / 2;
    }

    int64 solve(int Nlo, int Nhi, int Blo, int Bhi, int Slo, int Shi) {
        int64 ans = 0;

        for (int B = Blo; B <= Bhi; ++B)
            for (int S = Slo; S <= Shi && S < B; ++S) {
                // X == 0
                if (S == 1) {
                    if (Nlo <= 1 && 1 <= Nhi) ++ans;
                    if (Nlo <= 2 && 2 <= Nhi) ++ans;
                } else ans += Nhi - Nlo + 1;
               
                // 1 <= X <= B
                for (int X = 1; X <= B; ++X) {
                    // X * B <= X * (X - 1) + Y * min(S, X)
                    int Y = ceil((X * B - X * (X - 1)) / (double)min(S, X));
                    int N = X + Y;
                    if (Nhi >= N)
                        ans += Nhi - max(Nlo, N) + 1;
                }

                // X > B
                ans += all_pairs(B + 1, Nlo, Nhi);
            }

       return ans;
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
			int Nlo                   = 20;
			int Nhi                   = 20;
			int Blo                   = 3;
			int Bhi                   = 3;
			int Slo                   = 2;
			int Shi                   = 2;
			long long expected__      = 21;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int Nlo                   = 1;
			int Nhi                   = 1;
			int Blo                   = 10;
			int Bhi                   = 10;
			int Slo                   = 2;
			int Shi                   = 2;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int Nlo                   = 10;
			int Nhi                   = 10;
			int Blo                   = 8;
			int Bhi                   = 8;
			int Slo                   = 3;
			int Shi                   = 3;
			long long expected__      = 6;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int Nlo                   = 10;
			int Nhi                   = 100;
			int Blo                   = 13;
			int Bhi                   = 15;
			int Slo                   = 18;
			int Shi                   = 22;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int Nlo                   = 30;
			int Nhi                   = 32;
			int Blo                   = 8;
			int Bhi                   = 10;
			int Slo                   = 6;
			int Shi                   = 8;
			long long expected__      = 768;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int Nlo                   = 4;
			int Nhi                   = 4;
			int Blo                   = 1;
			int Bhi                   = 10;
			int Slo                   = 1;
			int Shi                   = 10;
			long long expected__      = 45;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int Nlo                   = ;
			int Nhi                   = ;
			int Blo                   = ;
			int Bhi                   = ;
			int Slo                   = ;
			int Shi                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int Nlo                   = ;
			int Nhi                   = ;
			int Blo                   = ;
			int Bhi                   = ;
			int Slo                   = ;
			int Shi                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = BigAndSmallAirports().solve(Nlo, Nhi, Blo, Bhi, Slo, Shi);
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
