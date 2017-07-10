// tests.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	TestResult result;
	TestRegistry::runAllTests(result);
    return 0;
}

