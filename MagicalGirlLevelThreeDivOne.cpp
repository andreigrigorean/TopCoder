// SRM 514, Level 3

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

class MagicalGirlLevelThreeDivOne {
public:
    int K;
    vector<string> first;
    vector<string> v;
    vector<int64> len;

    int64 findBest(string& s) {
      int64 best = 0, cur = 0;
      FORIT(it, s) {
        cur = *it == '1' ? cur + 1 : 0;
        best = max(best, cur);
      }
      return best;
    }

    string getString(int pos, int64 lo, int64 hi) {
      lo = max(0LL, lo);
      hi = min(hi, len[pos] - 1);
      if (hi < lo) return "";

      if (pos < K)
        return first[pos].substr(lo, hi - lo + 1);

      string sol;
      for (int i = pos - 1; i >= 0; i -= K) {
        sol += getString(i, lo, hi);
        lo -= len[i];
        hi -= len[i];
      }
      return sol;
    }

    int64 theMaxPower(vector<string> _first, int n, int64 lo, int64 hi )  {
      first = _first;
      K = first.size();

      if (hi - lo >= 100000) {
        bool allOne = true;
        FORIT(it, first) FORIT(itChar, *it)
          allOne &= *itChar == '1';
        if (allOne) return hi - lo + 1;

        v = first;
        for (int i = K; i <= 4 * K; ++i) {
          string s;
          for (int j = i - 1; j >= 0; j -= K)
            s += v[j];
          v.push_back(s);
        }
        return findBest(v[4 * K]);
      }

      FORIT(it, first)
        len.push_back(it->size());
      int pos = K - 1;
      while (true) {
        ++pos;
        len.push_back(0);
        for (int i = pos - 1; i >= 0; i -= K)
          len[pos] += len[i];
        if (len[pos] > hi) break;
      }

      string sol = getString(min(pos, n), lo, hi);
      return findBest(sol);
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
			string first[]            = {"111", "011"};
			int n                     = 4;
			long long lo              = 2;
			long long hi              = 7;
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = MagicalGirlLevelThreeDivOne().theMaxPower(vector <string>(first, first + (sizeof first / sizeof first[0])), n, lo, hi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string first[]            = {"1", "11", "111"};
			int n                     = 123456789;
			long long lo              = 123456789;
			long long hi              = 123456789012345LL;
			long long expected__      = 123456665555557LL;

			clock_t start__           = clock();
			long long received__      = MagicalGirlLevelThreeDivOne().theMaxPower(vector <string>(first, first + (sizeof first / sizeof first[0])), n, lo, hi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string first[]            = {"0", "00", "000"};
			int n                     = 987654321;
			long long lo              = 987654321;
			long long hi              = 987654321054321LL;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = MagicalGirlLevelThreeDivOne().theMaxPower(vector <string>(first, first + (sizeof first / sizeof first[0])), n, lo, hi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string first[]            = {"1110", "11", "11111", "111", "1"};
			int n                     = 314159265;
			long long lo              = 271828182845904LL;
			long long hi              = 314159265358979LL;
			long long expected__      = 15;

			clock_t start__           = clock();
			long long received__      = MagicalGirlLevelThreeDivOne().theMaxPower(vector <string>(first, first + (sizeof first / sizeof first[0])), n, lo, hi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string first[]            = {"10000", "011011001011000001101000010100000111000110110", 
"000001010001011000001101110", "100100000110100001010000", 
"011011010", "01100000010101101110000011100011001000",
"0001010", "010011000", "000101001", "00", "1"};
			int n                     = 1000000000;
			long long lo              = 1000000000000000LL;
			long long hi              = 1000000000000000LL;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = MagicalGirlLevelThreeDivOne().theMaxPower(vector <string>(first, first + (sizeof first / sizeof first[0])), n, lo, hi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string first[]            = ;
			int n                     = ;
			long long lo              = ;
			long long hi              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MagicalGirlLevelThreeDivOne().theMaxPower(vector <string>(first, first + (sizeof first / sizeof first[0])), n, lo, hi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string first[]            = ;
			int n                     = ;
			long long lo              = ;
			long long hi              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MagicalGirlLevelThreeDivOne().theMaxPower(vector <string>(first, first + (sizeof first / sizeof first[0])), n, lo, hi);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string first[]            = ;
			int n                     = ;
			long long lo              = ;
			long long hi              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MagicalGirlLevelThreeDivOne().theMaxPower(vector <string>(first, first + (sizeof first / sizeof first[0])), n, lo, hi);
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
