// SRM 508, Level 3

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

const double EPS = 1e-10;
const int MAX_M = 5;
const int MAX_COORD = 1000;

class BarbarianInvasion2 {
public:
    int N, M;
    vector< pair<int, int> > polygon;
    vector< pair<int, int> > cities;
    double len[1 << MAX_M];
    double perim;

    class Event {
      public:
        pair<double, double> p;
        int city;

        Event(pair<double, double> _p, int _city) : p(_p), city(_city) {}

        bool operator<(const Event& other) const {
          if (fabs(p.x - other.p.x) < EPS)
            return p.y + EPS < other.p.y;
          return p.x < other.p.x;
        }
    };

    vector<Event> events;

    double sqr(double x) { return x * x; }

    void findEvents(pair<int, int> p1, pair<int, int> p2, int city, double R) {
      double A = p2.y - p1.y;
      double B = p1.x - p2.x;
      double C = p2.x * p1.y - p1.x * p2.y;

      // We need to solve the following system:
      // 1) A*X + B*Y + C = 0
      // 2) (X - cities[city].x)^2 + (Y - cities[city].y)^2 = R^2

      if (B == 0) {
        double X = -C / A;

        double a = 1;
        double b = -2 * cities[city].y;
        double c = sqr(cities[city].y) + sqr(X - cities[city].x) - sqr(R);

        double delta = sqr(b) - 4*a*c;
        if (delta < EPS) return;
        double Y1 = (-b - sqrt(delta)) / (2 * a);
        double Y2 = (-b + sqrt(delta)) / (2 * a);

        events.push_back(Event(make_pair(X, Y1), city));
        events.push_back(Event(make_pair(X, Y2), city));
      } else {
        double a = 1 + sqr(A / B);
        double b = -2 * cities[city].x + 2 * A * C / sqr(B) + 2 * cities[city].y * A / B;
        double c = sqr(cities[city].x) + sqr(cities[city].y) - sqr(R) + sqr(C / B) + 2 * cities[city].y * C / B;

        double delta = sqr(b) - 4*a*c;
        if (delta < EPS) return;
        double X1 = (-b - sqrt(delta)) / (2 * a);
        double X2 = (-b + sqrt(delta)) / (2 * a);
        double Y1 = (-A * X1 - C) / B;
        double Y2 = (-A * X2 - C) / B;

        events.push_back(Event(make_pair(X1, Y1), city));
        events.push_back(Event(make_pair(X2, Y2), city));
      }
    }

    bool equals(pair<double, double> p1, pair<double, double> p2) {
      return fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS;
    }

    double getDist(pair<double, double> p1, pair<double, double> p2) {
      return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
    }

    int bitCount(int x) {
      return !x ? 0 : 1 + bitCount(x & (x - 1));
    }

    bool works(double R) {
      memset(len, 0, sizeof(len));
      for (int i = 0; i < N; ++i) {
        events.clear();
        for (int j = 0; j < M; ++j)
          findEvents(polygon[i], polygon[(i + 1) % N], j, R);
        sort(events.begin(), events.end());

        Event startEvent = Event(polygon[i], -1);
        Event endEvent = Event(polygon[(i + 1) % N], -1);
        if (endEvent < startEvent)
          swap(startEvent, endEvent);

        FORIT(it, events) {
          if (*it < startEvent)
            it->p = startEvent.p;
          if (endEvent < *it)
            it->p = endEvent.p;
        }

        int mask = 0;
        pair<double, double> last = startEvent.p;

        // line-sweep algorithm
        for (int j = 0; j < (int)events.size(); ++j) {
          len[mask] += getDist(last, events[j].p);

          int j2;
          for (j2 = j; j2 + 1 < (int)events.size() && equals(events[j].p, events[j2 + 1].p); ++j2);
          for (int k = j; k <= j2; ++k)
            mask ^= 1 << events[k].city;

          last = events[j].p;
          j = j2;
        }
      }

      // marriage theorem
      for (int mask = 1; mask < (1 << M); ++mask) {
        double lenMask = 0;
        for (int mask2 = 1; mask2 < (1 << M); ++mask2)
          if (mask & mask2)
            lenMask += len[mask2];
        if (lenMask + EPS < perim * bitCount(mask) / M)
          return false;
      }
      return true;
    }

    double minimumTime( vector <int> boundaryX, vector <int> boundaryY, vector <int> cityX, vector <int> cityY )  {
      N = boundaryX.size();
      for (int i = 0; i < N; ++i)
        polygon.push_back(make_pair(boundaryX[i], boundaryY[i]));

      M = cityX.size();
      for (int i = 0; i < M; ++i)
        cities.push_back(make_pair(cityX[i], cityY[i]));

      for (int i = 0; i < N; ++i)
        perim += getDist(polygon[i], polygon[(i + 1) % N]);

      // binary search the result
      double lo = 0, hi = 2 * sqrt(2) * MAX_COORD;
      for (int step = 0; step < 100; ++step) {
        double mid = (lo + hi) / 2;
        if (works(mid)) hi = mid;
        else lo = mid;
      } 
      return lo;
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }
	
	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int boundaryX[]           = {0,2,2,0};
			int boundaryY[]           = {0,0,2,2};
			int cityX[]               = {1};
			int cityY[]               = {1};
			double expected__         = 1.414213562373088;

			clock_t start__           = clock();
			double received__         = BarbarianInvasion2().minimumTime(vector <int>(boundaryX, boundaryX + (sizeof boundaryX / sizeof boundaryX[0])), vector <int>(boundaryY, boundaryY + (sizeof boundaryY / sizeof boundaryY[0])), vector <int>(cityX, cityX + (sizeof cityX / sizeof cityX[0])), vector <int>(cityY, cityY + (sizeof cityY / sizeof cityY[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int boundaryX[]           = {0,3,3,0};
			int boundaryY[]           = {0,0,3,3};
			int cityX[]               = {1};
			int cityY[]               = {1};
			double expected__         = 2.8284271247461485;

			clock_t start__           = clock();
			double received__         = BarbarianInvasion2().minimumTime(vector <int>(boundaryX, boundaryX + (sizeof boundaryX / sizeof boundaryX[0])), vector <int>(boundaryY, boundaryY + (sizeof boundaryY / sizeof boundaryY[0])), vector <int>(cityX, cityX + (sizeof cityX / sizeof cityX[0])), vector <int>(cityY, cityY + (sizeof cityY / sizeof cityY[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int boundaryX[]           = {0,3,3,0};
			int boundaryY[]           = {0,0,3,3};
			int cityX[]               = {1,2};
			int cityY[]               = {2,1};
			double expected__         = 2.236067977499772;

			clock_t start__           = clock();
			double received__         = BarbarianInvasion2().minimumTime(vector <int>(boundaryX, boundaryX + (sizeof boundaryX / sizeof boundaryX[0])), vector <int>(boundaryY, boundaryY + (sizeof boundaryY / sizeof boundaryY[0])), vector <int>(cityX, cityX + (sizeof cityX / sizeof cityX[0])), vector <int>(cityY, cityY + (sizeof cityY / sizeof cityY[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int boundaryX[]           = {0,40,40,0};
			int boundaryY[]           = {0,0,40,40};
			int cityX[]               = {1,2,31,2,15};
			int cityY[]               = {1,2,3,3,24};
			double expected__         = 38.05748153551994;

			clock_t start__           = clock();
			double received__         = BarbarianInvasion2().minimumTime(vector <int>(boundaryX, boundaryX + (sizeof boundaryX / sizeof boundaryX[0])), vector <int>(boundaryY, boundaryY + (sizeof boundaryY / sizeof boundaryY[0])), vector <int>(cityX, cityX + (sizeof cityX / sizeof cityX[0])), vector <int>(cityY, cityY + (sizeof cityY / sizeof cityY[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int boundaryX[]           = {0,124,-6,-120,-300};
			int boundaryY[]           = {0,125,140,137,-100};
			int cityX[]               = {10,10,10,10};
			int cityY[]               = {50,51,52,21};
			double expected__         = 332.77770358002783;

			clock_t start__           = clock();
			double received__         = BarbarianInvasion2().minimumTime(vector <int>(boundaryX, boundaryX + (sizeof boundaryX / sizeof boundaryX[0])), vector <int>(boundaryY, boundaryY + (sizeof boundaryY / sizeof boundaryY[0])), vector <int>(cityX, cityX + (sizeof cityX / sizeof cityX[0])), vector <int>(cityY, cityY + (sizeof cityY / sizeof cityY[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int boundaryX[]           = ;
			int boundaryY[]           = ;
			int cityX[]               = ;
			int cityY[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = BarbarianInvasion2().minimumTime(vector <int>(boundaryX, boundaryX + (sizeof boundaryX / sizeof boundaryX[0])), vector <int>(boundaryY, boundaryY + (sizeof boundaryY / sizeof boundaryY[0])), vector <int>(cityX, cityX + (sizeof cityX / sizeof cityX[0])), vector <int>(cityY, cityY + (sizeof cityY / sizeof cityY[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int boundaryX[]           = ;
			int boundaryY[]           = ;
			int cityX[]               = ;
			int cityY[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = BarbarianInvasion2().minimumTime(vector <int>(boundaryX, boundaryX + (sizeof boundaryX / sizeof boundaryX[0])), vector <int>(boundaryY, boundaryY + (sizeof boundaryY / sizeof boundaryY[0])), vector <int>(cityX, cityX + (sizeof cityX / sizeof cityX[0])), vector <int>(cityY, cityY + (sizeof cityY / sizeof cityY[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int boundaryX[]           = ;
			int boundaryY[]           = ;
			int cityX[]               = ;
			int cityY[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = BarbarianInvasion2().minimumTime(vector <int>(boundaryX, boundaryX + (sizeof boundaryX / sizeof boundaryX[0])), vector <int>(boundaryY, boundaryY + (sizeof boundaryY / sizeof boundaryY[0])), vector <int>(cityX, cityX + (sizeof cityX / sizeof cityX[0])), vector <int>(cityY, cityY + (sizeof cityY / sizeof cityY[0])));
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
