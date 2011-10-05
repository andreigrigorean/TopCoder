// SRM 496, Level 3

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

class YetAnotherHamiltonianPath {
public:
    int sqr(int x) { return x * x; }

    int lcp(string A, string B) {
      int i;
      for (i = 0; i < (int)A.size() && i < (int)B.size(); ++i)
        if (A[i] != B[i])
          return i;
      return i;
    }

    int leastCost(vector<string> label) {
      string start = label[0];
      string finish = label[1];
      sort(label.begin(), label.end());

      int n = label.size();
      int cost = 0;

      for (int i = 0; i < n; ++i)
        cost += 2 * sqr(label[i].size());
      cost -= sqr(start.size()) + sqr(finish.size());

      for (int i = 0; i < n; ++i)
        cost -= sqr(lcp(label[i], label[(i + 1) % n]));
      cost += sqr(lcp(start, finish));

      return cost;
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
			string label[]            = {"home", "school", "pub"} ;
			int expected__            = 70;

			clock_t start__           = clock();
			int received__            = YetAnotherHamiltonianPath().leastCost(vector <string>(label, label + (sizeof label / sizeof label[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string label[]            = {"school", "home", "pub", "stadium"};
			int expected__            = 167;

			clock_t start__           = clock();
			int received__            = YetAnotherHamiltonianPath().leastCost(vector <string>(label, label + (sizeof label / sizeof label[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string label[]            = {"abcd","aecgh","abef","aecd"};
			int expected__            = 91;

			clock_t start__           = clock();
			int received__            = YetAnotherHamiltonianPath().leastCost(vector <string>(label, label + (sizeof label / sizeof label[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string label[]            = {"canada", "cyprus", "croatia", "colombia", "chile", "china", "cameroon"};
			int expected__            = 509;

			clock_t start__           = clock();
			int received__            = YetAnotherHamiltonianPath().leastCost(vector <string>(label, label + (sizeof label / sizeof label[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string label[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = YetAnotherHamiltonianPath().leastCost(vector <string>(label, label + (sizeof label / sizeof label[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string label[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = YetAnotherHamiltonianPath().leastCost(vector <string>(label, label + (sizeof label / sizeof label[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string label[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = YetAnotherHamiltonianPath().leastCost(vector <string>(label, label + (sizeof label / sizeof label[0])));
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
