// SRM 515, Level 3

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <exception>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

#define FORIT(it, v) for (typeof(v.begin()) it = v.begin(); it != v.end(); ++it)
#define x first
#define y second

const int MAX_N = 64;
const int INF = 0x3f3f3f3f;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};


class MeetInTheMaze {
public:
    int n, m;
    vector<string> maze;
    vector< pair<int, int> > F, R, L;
    int dminF[MAX_N][MAX_N], dminR[MAX_N][MAX_N];
    int best[MAX_N][MAX_N];

    class Elem {
      public:
        Elem(int _dist, int _x, int _y) : dist(_dist), x(_x), y(_y) {};
        int dist;
        int x, y;

        bool operator<(const Elem& other) const {
          return dist > other.dist;
        }
    };

    int64 gcd(int64 a, int64 b) {
      return !b ? a : gcd(b, a % b);
    }

    bool validPos(int x, int y) {
      if (x < 0 || x >= n || y < 0 || y >= m) return false;
      if (maze[x][y] == '#') return false;
      return true;
    }

    void BFS(pair<int, int> start, int d[MAX_N][MAX_N]) {
      memset(d, INF, sizeof(int) * MAX_N * MAX_N);
      d[start.x][start.y] = 0;

      queue< pair<int, int> > Q;
      Q.push(start);
      while (!Q.empty()) {
        pair<int, int> pos = Q.front();
        Q.pop();

        for (int i = 0; i < 4; ++i) {
          pair<int, int> newPos = make_pair(pos.x + dx[i], pos.y + dy[i]);
          if (validPos(newPos.x, newPos.y) && d[newPos.x][newPos.y] == INF) {
            d[newPos.x][newPos.y] = d[pos.x][pos.y] + 1;
            Q.push(newPos);
          }
        }
      }
    }

    int64 expectedCost(pair<int, int> startF, pair<int, int> startR) {
      BFS(startF, dminF);
      BFS(startR, dminR);

      memset(best, INF, sizeof(best));

      priority_queue<Elem> heap;
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
          heap.push(Elem(dminF[i][j] + dminR[i][j], i, j));

      while (!heap.empty()) {
        Elem elem = heap.top();
        heap.pop();

        if (elem.dist >= INF) break;
        if (best[elem.x][elem.y] <= elem.dist) continue;
        best[elem.x][elem.y] = elem.dist;

        for (int i = 0; i < 4; ++i) {
          int newx = elem.x + dx[i];
          int newy = elem.y + dy[i];

          if (validPos(newx, newy) && best[newx][newy] > elem.dist + 1) {
            heap.push(Elem(elem.dist + 1, newx, newy));
          }
        }
      }

      int64 cost = 0;
      FORIT(it, L)
        if (best[it->x][it->y] >= INF)
          throw exception();
        else
          cost += best[it->x][it->y];

      return cost;
    }

    string getExpected(vector<string> _maze) {
      maze = _maze;
      n = maze.size();
      m = maze[0].size();

      for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
          if (maze[i][j] == 'F')
            F.push_back(make_pair(i, j));
          else if (maze[i][j] == 'R')
            R.push_back(make_pair(i, j));
          else if (maze[i][j] == 'L')
            L.push_back(make_pair(i, j));

      int64 cost = 0, possib = F.size() * R.size() * L.size();
      try {
        FORIT(itF, F)
          FORIT(itR, R)
            cost += expectedCost(*itF, *itR);
      }
      catch (exception& e) {
        return "";
      }
      int64 d = gcd(cost, possib);
      cost /= d; possib /= d;

      ostringstream oss;
      oss << cost << '/' << possib;
      return oss.str();
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
			string maze[]             = 
      { "######F##", 
        "####.#L.R", 
        "##...####", 
        "####F####", 
        "#########" }
;
			string expected__         = "";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string maze[]             = { "LR", 
  "RF" }
;
			string expected__         = "2/1";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string maze[]             = { "..F.#...", 
  "L.F.#..L", 
  "..F.#...", 
  ".R.#..L.", 
  "...#....", 
  "..R#.L.." }
;
			string expected__         = "";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string maze[]             = { ".L..L..L..", 
  "..........", 
  "..........", 
  "..........", 
  "........R.", 
  "...R......", 
  "..........", 
  "..........", 
  "..........", 
  ".......F.." }
;
			string expected__         = "40/3";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string maze[]             = { "#.#....#...#.#", 
  "#...#..#......", 
  ".L#...#R#..#F.", 
  "#...#......#..", 
  "#......#.....#", 
  ".R.....F....L.", 
  "##..#.......#.", 
  "#........##...", 
  ".F...##L#..#R#" }
;
			string expected__         = "362/27";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			string maze[]             = { "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLFLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFFLLLLLLLLLLRLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLFLLLLLLLLLLLLLLF", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLF", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFLLL", 
  "LLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRRL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLR", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLFFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "FLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLFLLLLLLLLLRLLLLLLLLLLLLLLLLLLLRLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLFLLLLLLLLLLLLLLLLRLLLLLLLLLRLLLLLLLLLLLLRLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "FLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLL" }
;
			string expected__         = "210623/4100";

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string maze[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string maze[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string maze[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MeetInTheMaze().getExpected(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])));
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
