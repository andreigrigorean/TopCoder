// SRM 489, Level 1

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

class BallsConverter {
public:
    vector<string> A;

    int newBall(int i, int j) {
        if ('A' <= A[i][j] && A[i][j] <= 'Z')
            return A[i][j] - 'A';
        else
            return 26 + A[i][j] - 'a';
    }

    string theGood(vector<string> _A) {
        A = _A;
        int n = A.size();

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    if (newBall(i, newBall(j, k)) != newBall(newBall(i, j), k))
                        return "Bad";
        return "Good";
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
			string convert[]          = {"AB", "BA"};
			string expected__         = "Good";

			clock_t start__           = clock();
			string received__         = BallsConverter().theGood(vector <string>(convert, convert + (sizeof convert / sizeof convert[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string convert[]          = {"BA", "AA"};
			string expected__         = "Bad";

			clock_t start__           = clock();
			string received__         = BallsConverter().theGood(vector <string>(convert, convert + (sizeof convert / sizeof convert[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string convert[]          = {"ACB", "CBA", "BAC"};
			string expected__         = "Bad";

			clock_t start__           = clock();
			string received__         = BallsConverter().theGood(vector <string>(convert, convert + (sizeof convert / sizeof convert[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string convert[]          = {"AAAA", "ABBB", "ABCC", "ABCD"};
			string expected__         = "Good";

			clock_t start__           = clock();
			string received__         = BallsConverter().theGood(vector <string>(convert, convert + (sizeof convert / sizeof convert[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string convert[]          = {"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcd",
"ACEGIKMOQSUWYacACEGIKMOQSUWYac",
"ADGJMPSVYbADGJMPSVYbADGJMPSVYb",
"AEIMQUYcCGKOSWaAEIMQUYcCGKOSWa",
"AFKPUZAFKPUZAFKPUZAFKPUZAFKPUZ",
"AGMSYAGMSYAGMSYAGMSYAGMSYAGMSY",
"AHOVcFMTaDKRYBIPWdGNUbELSZCJQX",
"AIQYCKSaEMUcGOWAIQYCKSaEMUcGOW",
"AJSbGPYDMVAJSbGPYDMVAJSbGPYDMV",
"AKUAKUAKUAKUAKUAKUAKUAKUAKUAKU",
"ALWDOZGRcJUBMXEPaHSdKVCNYFQbIT",
"AMYGSAMYGSAMYGSAMYGSAMYGSAMYGS",
"ANaJWFSBObKXGTCPcLYHUDQdMZIVER",
"AOcMaKYIWGUESCQAOcMaKYIWGUESCQ",
"APAPAPAPAPAPAPAPAPAPAPAPAPAPAP",
"AQCSEUGWIYKaMcOAQCSEUGWIYKaMcO",
"AREVIZMdQDUHYLcPCTGXKbOBSFWJaN",
"ASGYMASGYMASGYMASGYMASGYMASGYM",
"ATIbQFYNCVKdSHaPEXMBUJcRGZODWL",
"AUKAUKAUKAUKAUKAUKAUKAUKAUKAUK",
"AVMDYPGbSJAVMDYPGbSJAVMDYPGbSJ",
"AWOGcUMEaSKCYQIAWOGcUMEaSKCYQI",
"AXQJCZSLEbUNGdWPIBYRKDaTMFcVOH",
"AYSMGAYSMGAYSMGAYSMGAYSMGAYSMG",
"AZUPKFAZUPKFAZUPKFAZUPKFAZUPKF",
"AaWSOKGCcYUQMIEAaWSOKGCcYUQMIE",
"AbYVSPMJGDAbYVSPMJGDAbYVSPMJGD",
"AcaYWUSQOMKIGECAcaYWUSQOMKIGEC",
"AdcbaZYXWVUTSRQPONMLKJIHGFEDCB"}
;
			string expected__         = "Good";

			clock_t start__           = clock();
			string received__         = BallsConverter().theGood(vector <string>(convert, convert + (sizeof convert / sizeof convert[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			string convert[]          = {"AAAAAFAAAAAAAAAAAAAAAAAXAAAAcAAAAAAAAAAnAAAAAAAvAA",
"ABBBBFBBBBBLBBBBQBBBBBBXYBBBcBBBBBBBBBBnBBBBBBBvwB",
"ABCCCFCCCCCLMCOCQRCCCCCXYCCCcCCCCCCCCCCnCCCCsCCvwC",
"ABCDEFGHDDDLMDODQRSDUVWXYDDbcdDfghDDklDnopDrsDDvwx",
"ABCEEFEEEEELMEOEQRSEUVWXYEEbcEEfEhEEklEnEpEEsEEvwE",
"FFFFFFFFFFFFFFFFFFFFFFFXFFFFcFFFFFFFFFFFFFFFFFFvFF",
"ABCGEFGGGGGLMGOGQRSGUVWXYGGbcGGfGhGGklGnGpGGsGGvwG",
"ABCHEFGHHHHLMHOHQRSHUVWXYHHbcdHfHhHHklHnHpHHsHHvwH",
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwx",
"ABCDEFGHJJJLMJOJQRSJUVWXYJJbcdJfghJJklJnopJrsJJvwx",
"ABCDEFGHKJKLMNOPQRSTUVWXYZKbcdefghijklmnopqrsKKvwx",
"ALLLLFLLLLLLLLLLLLLLLLLXLLLLcLLLLLLLLLLnLLLLLLLvwL",
"ABMMMFMMMMMLMMOMQMMMMMMXYMMMcMMMMMMMMMMnMMMMMMMvwM",
"ABCDEFGHNJNLMNOPQRSTUVWXYZNbcdefghijklmnopqrsNNvwx",
"ABOOOFOOOOOLOOOOQOOOOOOXYOOOcOOOOOOOOOOnOOOOOOOvwO",
"ABCDEFGHPJPLMPOPQRSTUVWXYZPbcdPfghiPklmnopPrsPPvwx",
"AQQQQFQQQQQLQQQQQQQQQQQXQQQQcQQQQQQQQQQnQQQQQQQvwQ",
"ABRRRFRRRRRLMRORQRRRRRRXYRRRcRRRRRRRRRRnRRRRRRRvwR",
"ABCSSFSSSSSLMSOSQRSSSSSXYSSScSSSSSSSSSSnSSSSsSSvwS",
"ABCDEFGHTJTLMTOTQRSTUVWXYTTbcdTfghiTklTnopTrsTTvwx",
"ABCUUFUUUUULMUOUQRSUUUWXYUUUcUUUUhUUklUnUUUUsUUvwU",
"ABCVVFVVVVVLMVOVQRSVUVWXYVVbcVVfVhVVklVnVVVVsVVvwV",
"ABCWWFWWWWWLMWOWQRSWWWWXYWWWcWWWWhWWkWWnWWWWsWWvwW",
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXvXX",
"AYYYYFYYYYYLYYYYQYYYYYYXYYYYcYYYYYYYYYYnYYYYYYYvwY",
"ABCDEFGHZJZLMZOZQRSTUVWXYZZbcdZfghiZklZnopZrsZZvwx",
"ABCDEFGHaJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwx",
"ABCbbFbbbbbLMbObQRSbUbWXYbbbcbbfbhbbklbnbbbbsbbvwb",
"cccccccccccccccccccccccXcccccccccccccccccccccccvcc",
"ABCdEFGddddLMdOdQRSdUVWXYddbcddfdhddkldndpddsddvwd",
"ABCDEFGHeJeLMeOPQRSTUVWXYZebcdefghijklmnoperseevwx",
"ABCffFfffffLMfOfQRSfUfWXYfffcffffhffklfnffffsffvwf",
"ABCgEFGHgggLMgOgQRSgUVWXYggbcdgfghggklgngpggsggvwg",
"ABChhFhhhhhLMhOhQRShhhhXYhhhchhhhhhhkhhnhhhhshhvwh",
"ABCDEFGHiJiLMiOiQRSiUVWXYiibcdifghiiklinopirsiivwx",
"ABCDEFGHjJjLMjOPQRSTUVWXYZjbcdjfghijklmnopjrsjjvwx",
"ABCkkFkkkkkLMkOkQRSkkkkXYkkkckkkkkkkkkknkkkkskkvwk",
"ABCllFlllllLMlOlQRSlllWXYlllcllllhllkllnllllsllvwl",
"ABCDEFGHmJmLMmOmQRSTUVWXYZmbcdmfghimklmnopmrsmmvwx",
"nnnnnFnnnnnnnnnnnnnnnnnXnnnncnnnnnnnnnnnnnnnnnnvnn",
"ABCoEFGHoooLMoOoQRSoUVWXYoobcdofghooklonoporsoovwx",
"ABCppFpppppLMpOpQRSpUVWXYppbcppfphppklpnpppSsppvwp",
"ABCDEFGHqJqLMqOPQRSTUVWXYZqbcdefghijklmnopqrsqqvwx",
"ABCrEFGHrrrLMrOrQRSrUVWXYrrbcdrfghrrklrnrSrrsrrvwx",
"ABsssFsssssLMsOsQRsssssXYssscssssssssssnsssssssvws",
"ABCDEFGHtJKLMNOPQRSTUVWXYZtbcdefghijklmnopqrsttvwx",
"ABCDEFGHuJKLMNOPQRSTUVWXYZubcdefghijklmnopqrstuvwx",
"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv",
"AwwwwFwwwwwwwwwwwwwwwwwXwwwwcwwwwwwwwwwnwwwwwwwvww",
"ABCxEFGHxxxLMxOxQRSxUVWXYxxbcdxfghxxklxnxpxxsxxvwx"}
;
			string expected__         = "Bad";

			clock_t start__           = clock();
			string received__         = BallsConverter().theGood(vector <string>(convert, convert + (sizeof convert / sizeof convert[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string convert[]          = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = BallsConverter().theGood(vector <string>(convert, convert + (sizeof convert / sizeof convert[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string convert[]          = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = BallsConverter().theGood(vector <string>(convert, convert + (sizeof convert / sizeof convert[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string convert[]          = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = BallsConverter().theGood(vector <string>(convert, convert + (sizeof convert / sizeof convert[0])));
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
