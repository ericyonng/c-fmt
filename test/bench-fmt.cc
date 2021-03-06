//
//  bench-fmt.cc
//

#include <cstdio>
#include <chrono>

#include "fmt.h"

using namespace fmt;

int main()
{
	const int ITERS = 100000;

	// snprintf: string %20s
	{
		char buf[128];
		std::chrono::time_point<std::chrono::system_clock> s1 = std::chrono::system_clock::now();
		for (size_t i = 0; i < ITERS; i ++) {
			snprintf(buf, sizeof(buf), "%-20s\n", "String String");
		}
		std::chrono::time_point<std::chrono::system_clock> s2 = std::chrono::system_clock::now();
		double test_1_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(s2-s1).count() / (double)ITERS;
		printf("snprintf    (%%20s) : %9.3f ns\n", test_1_ns);
	}

	// snprintf: integer %20llu
	{
		char buf[128];
		std::chrono::time_point<std::chrono::system_clock> s1 = std::chrono::system_clock::now();
		for (size_t i = 0; i < ITERS; i ++) {
			snprintf(buf, sizeof(buf), "%20llu\n", 18446744073709551615ULL);
		}
		std::chrono::time_point<std::chrono::system_clock> s2 = std::chrono::system_clock::now();
		double test_1_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(s2-s1).count() / (double)ITERS;
		printf("snprintf  (%%20llu) : %9.3f ns\n", test_1_ns);
	}

	// snprintf: double %7.5f
	{
		char buf[128];
		std::chrono::time_point<std::chrono::system_clock> s1 = std::chrono::system_clock::now();
		for (size_t i = 0; i < ITERS; i ++) {
			snprintf(buf, sizeof(buf), "%7.5f\n", 3.141592653589793);
		}
		std::chrono::time_point<std::chrono::system_clock> s2 = std::chrono::system_clock::now();
		double test_1_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(s2-s1).count() / (double)ITERS;
		printf("snprintf   (%%7.5f) : %9.3f ns\n", test_1_ns);
	}

	// snprintf: double %17.15f
	{
		char buf[128];
		std::chrono::time_point<std::chrono::system_clock> s1 = std::chrono::system_clock::now();
		for (size_t i = 0; i < ITERS; i ++) {
			snprintf(buf, sizeof(buf), "%17.15f\n", 3.141592653589793);
		}
		std::chrono::time_point<std::chrono::system_clock> s2 = std::chrono::system_clock::now();
		double test_1_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(s2-s1).count() / (double)ITERS;
		printf("snprintf (%%17.15f) : %9.3f ns\n", test_1_ns);
	}

	// c+fmt: string %20s
	{
		std::string buf;
		std::chrono::time_point<std::chrono::system_clock> s1 = std::chrono::system_clock::now();
		for (size_t i = 0; i < ITERS; i ++) {
			buf.clear();
			sprintf(buf, "%-20s\n", "String String");
		}
		std::chrono::time_point<std::chrono::system_clock> s2 = std::chrono::system_clock::now();
		double test_1_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(s2-s1).count() / (double)ITERS;
		printf("c+fmt       (%%20s) : %9.3f ns\n", test_1_ns);
	}

	// c+fmt: integer %20llu
	{
		std::string buf;
		std::chrono::time_point<std::chrono::system_clock> s1 = std::chrono::system_clock::now();
		for (size_t i = 0; i < ITERS; i ++) {
			buf.clear();
			sprintf(buf, "%20llu\n", 18446744073709551615ULL);
		}
		std::chrono::time_point<std::chrono::system_clock> s2 = std::chrono::system_clock::now();
		double test_1_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(s2-s1).count() / (double)ITERS;
		printf("c+fmt     (%%20llu) : %9.3f ns\n", test_1_ns);
	}

	// c+fmt: double %7.5f
	{
		std::string buf;
		std::chrono::time_point<std::chrono::system_clock> s1 = std::chrono::system_clock::now();
		for (size_t i = 0; i < ITERS; i ++) {
			buf.clear();
			sprintf(buf, "%7.5f\n", 3.141592653589793);
		}
		std::chrono::time_point<std::chrono::system_clock> s2 = std::chrono::system_clock::now();
		double test_1_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(s2-s1).count() / (double)ITERS;
		printf("c+fmt      (%%7.5f) : %9.3f ns\n", test_1_ns);
	}

	// c+fmt: double %17.15f
	{
		std::string buf;
		std::chrono::time_point<std::chrono::system_clock> s1 = std::chrono::system_clock::now();
		for (size_t i = 0; i < ITERS; i ++) {
			buf.clear();
			sprintf(buf, "%17.15f\n", 3.141592653589793);
		}
		std::chrono::time_point<std::chrono::system_clock> s2 = std::chrono::system_clock::now();
		double test_1_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(s2-s1).count() / (double)ITERS;
		printf("c+fmt    (%%17.15f) : %9.3f ns\n", test_1_ns);
	}

	return 0;
}
