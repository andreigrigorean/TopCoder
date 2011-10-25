// SRM 510, Level 3

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


class TheLuckyBasesDivOne {
public:
    int64 n;
    vector<int64> luckyNumbers;

    bool isLuckyNumber(int64 n) {
      vector<int64>::iterator it = upper_bound(luckyNumbers.begin(), luckyNumbers.end(), n);
      if (it == luckyNumbers.begin())
        return false;
      return *(--it) == n;
    }

    void generateLuckyNumbers(int64 val) {
      if (val <= n) {
        if (val > 0)
          luckyNumbers.push_back(val);
        generateLuckyNumbers(val * 10 + 4);
        generateLuckyNumbers(val * 10 + 7);
      }
    }

    int64 count4PlusDigits() {
      int64 sol = 0;
      for (int64 base = 2; base <= n; ++base) {
        int digits = 0;
        int64 aux = n;
        bool isLucky = true;

        do {
          isLucky &= isLuckyNumber(aux % base);
          aux /= base;
          ++digits;
        } while (aux > 0);

        if (digits <= 3) break;
        if (isLucky) ++sol;
      }
      return sol;
    }

    bool isValidTriplet(int64 a, int64 b, int64 c) {
      int64 lo = max(a, max(b, c)) + 1;
      int64 hi = (int)sqrt(n);
      while (lo < hi) {
        int64 mid = (hi + lo + 1) / 2;
        if ((a * mid <= n / mid) &&
            (a * mid + b <= n / mid) &&
            (a * mid * mid + b * mid + c <= n))
          lo = mid;
        else hi = mid - 1;
      }
      return a * lo * lo + b * lo + c == n;
    }
  
    int64 count3Digits() {
      int64 sol = 0;
      for (size_t i = 0; i < luckyNumbers.size(); ++i) {
        int64 a = luckyNumbers[i];
        int64 base1 = a + 1;
        if (a > n / base1) break;
        if (a * base1 > n / base1) break;

        for (size_t j = 0; j < luckyNumbers.size(); ++j) {
          int64 b = luckyNumbers[j];
          int64 base2 = max(base1, b + 1);
          if (a > n / base2) break;
          if (a * base2 > n / base2) break;
          if (b > n / base2) break;
          if (a * base2 + b > n / base2) break;

          for (size_t k = 0; k < luckyNumbers.size(); ++k) {
            int64 c = luckyNumbers[k];
            int base3 = max(base2, c + 1);
            if (a > n / base3) break;
            if (a * base3 > n / base3) break;
            if (b > n / base3) break;
            if (a * base3 + b > n / base3) break;
            if (a * base3 + b > (n - c) / base3) break;

            if (isValidTriplet(a, b, c)) ++sol;
          }
        }
      }
      return sol;
    }

    bool isValidPair(int64 a, int64 b) {
      if ((n - b) % a == 0) {
        int64 base = (n - b) / a;
        return base > a && base > b;
      }
      return false;
    }

    int64 count2Digits() {
      int64 sol = 0;
      for (size_t i = 0; i < luckyNumbers.size(); ++i) {
        int64 a = luckyNumbers[i];
        int64 base1 = a + 1;
        if (a > n / base1) break;

        for (size_t j = 0; j < luckyNumbers.size(); ++j) {
          int64 b = luckyNumbers[j];
          int64 base2 = max(base1, b + 1);
          if (a > n / base2) break;
          if (a * base2 > n - b) break;

          if (isValidPair(a, b)) ++sol;
        }
      }
      return sol;
    }

    int64 find(int64 _n) {
      n = _n;
      generateLuckyNumbers(0);
      sort(luckyNumbers.begin(), luckyNumbers.end());
      
      if (isLuckyNumber(n)) return -1;
      return count4PlusDigits() + count3Digits() + count2Digits();
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
			long long n               = 255;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			long long n               = 474;
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			long long n               = 13;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			long long n               = 4748;
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			long long n               = 419546186871LL;
			long long expected__      = 1588;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
/*      case 5: {
			long long n               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long n               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TheLuckyBasesDivOne().find(n);
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
