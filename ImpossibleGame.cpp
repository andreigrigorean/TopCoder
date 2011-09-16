// SRM 499, Level 3

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

const int MAX_K = 32;
const int MAX_N = 5500;

class ImpossibleGame {
  public:
    int K;
    int N;
    int64 comb[MAX_K][MAX_K];
    vector<int> whatState[MAX_N];
    map< vector<int>, int> whatId;
    vector<int> graph[MAX_N];
    int64 weight[MAX_N];

    void precomputeComb() {
      for (int i = 0; i <= K; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j)
          comb[i][j] = comb[i - 1][j - 1] + comb[i- 1][j];
      }
    }

    void buildVertices() {
      for (int A = 0; A <= K; ++A)
        for (int B = 0; A + B <= K; ++B)
          for (int C = 0; A + B + C <= K; ++C) {
            vector<int> aux;
            aux.push_back(A);
            aux.push_back(B);
            aux.push_back(C);

            ++N;
            whatState[N] = aux;
            whatId[aux] = N;
            weight[N] = comb[K][A] * comb[K - A][B] * comb[K - A - B][C];
          }
    }

    vector< vector<int> > normalize(vector<string> v) {
      vector< vector<int> > ret;
      FORIT(it, v) {
        vector<int> aux(4);
        FORIT(itChar, *it)
          switch (*itChar) {
            case 'A': ++aux[0]; break;
            case 'B': ++aux[1]; break;
            case 'C': ++aux[2]; break;
            case 'D': ++aux[3]; break;
          }
        ret.push_back(aux);
      }
      return ret;
    }

    void buildEdges(vector< vector<int> > before, vector< vector<int> > after) {
      for (int node = 1; node <= N; ++node) {
        int A = whatState[node][0];
        int B = whatState[node][1];
        int C = whatState[node][2];
        int D = K - (A + B + C);
        
        for (size_t i = 0; i < before.size(); ++i)
          if (A >= before[i][0] && B >= before[i][1] && C >= before[i][2] && D >= before[i][3]) {
            vector<int> newState(3);
            newState[0] = A - before[i][0] + after[i][0];
            newState[1] = B - before[i][1] + after[i][1];
            newState[2] = C - before[i][2] + after[i][2];

            graph[node].push_back(whatId[newState]);
          }
      }
    }

    // tarjan
    int indeces;
    int index[MAX_N];
    int lowLink[MAX_N];
    bool inStack[MAX_N];
    stack<int> st;
    int compN;
    int comp[MAX_N];

    void tarjanDFS(int node) {
      index[node] = ++indeces;
      lowLink[node] = indeces;
      st.push(node);
      inStack[node] = true;

      FORIT(it, graph[node])
        if (index[*it] == 0) {
          tarjanDFS(*it);
          lowLink[node] = min(lowLink[node], lowLink[*it]);
        } else if (inStack[*it])
          lowLink[node] = min(lowLink[node], index[*it]);

      if (lowLink[node] == index[node]) {
        ++compN;
        while (true) {
          int aux = st.top();
          st.pop();
          inStack[aux] = false;
          comp[aux] = compN;
          if (aux == node) break;
        }
      }
    }

    void tarjan() {
      for (int i = 1; i <= N; ++i)
        if (index[i] == 0)
          tarjanDFS(i);
    }
    // end of tarjan

    int64 compWeight[MAX_N];
    vector<int> compGraph[MAX_N];
    int64 compPath[MAX_N];

    void makeCompGraph() {
      for (int i = 1; i <= N; ++i) {
        compWeight[comp[i]] += weight[i];
        FORIT(it, graph[i])
          if (comp[i] != comp[*it])
            compGraph[comp[i]].push_back(comp[*it]);
      }
    }

    int64 heaviestPath(int node) {
      if (compPath[node] != 0)
        return compPath[node];
        
      FORIT(it, compGraph[node])
        compPath[node] = max(compPath[node], heaviestPath(*it));
      return compPath[node] += compWeight[node];
    }

    int64 getMinimum(int _K, vector<string> before, vector<string> after) {
      K = _K;
      precomputeComb();
      buildVertices();
      buildEdges(normalize(before), normalize(after));
      tarjan();
      makeCompGraph();
      
      int64 best = 0;
      for (int i = 1; i <= compN; ++i)
        best = max(best, heaviestPath(i));
      return best;
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
			int k                     = 1;
			string before[]           = { "A" }
;
			string after[]            = { "B" }
;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = ImpossibleGame().getMinimum(k, vector <string>(before, before + (sizeof before / sizeof before[0])), vector <string>(after, after + (sizeof after / sizeof after[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int k                     = 2;
			string before[]           = { "A", "A", "D" }
;
			string after[]            = { "B", "C", "D" }
;
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = ImpossibleGame().getMinimum(k, vector <string>(before, before + (sizeof before / sizeof before[0])), vector <string>(after, after + (sizeof after / sizeof after[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int k                     = 2;
			string before[]           = { "B", "C", "D" }
;
			string after[]            = { "C", "D", "B" }
;
			long long expected__      = 9;

			clock_t start__           = clock();
			long long received__      = ImpossibleGame().getMinimum(k, vector <string>(before, before + (sizeof before / sizeof before[0])), vector <string>(after, after + (sizeof after / sizeof after[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int k                     = 6;
			string before[]           = { "AABBC", "AAAADA", "AAACA", "CABAA", "AAAAAA", "BAAAA" }
;
			string after[]            = { "AACCB", "DAAABC", "AAAAD", "ABCBA", "AABAAA", "AACAA" }
;
			long long expected__      = 499;

			clock_t start__           = clock();
			long long received__      = ImpossibleGame().getMinimum(k, vector <string>(before, before + (sizeof before / sizeof before[0])), vector <string>(after, after + (sizeof after / sizeof after[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int k                     = ;
			string before[]           = ;
			string after[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = ImpossibleGame().getMinimum(k, vector <string>(before, before + (sizeof before / sizeof before[0])), vector <string>(after, after + (sizeof after / sizeof after[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int k                     = ;
			string before[]           = ;
			string after[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = ImpossibleGame().getMinimum(k, vector <string>(before, before + (sizeof before / sizeof before[0])), vector <string>(after, after + (sizeof after / sizeof after[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int k                     = ;
			string before[]           = ;
			string after[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = ImpossibleGame().getMinimum(k, vector <string>(before, before + (sizeof before / sizeof before[0])), vector <string>(after, after + (sizeof after / sizeof after[0])));
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
