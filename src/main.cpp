//============================================================================
// Name        : wt_accounts.cpp
// Author      : First
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "wtaccounts.h"

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
	return new WtAccounts(env);
}

int main(int argc, char *argv[])
{
	return Wt::WRun(argc, argv, &createApplication);
}

