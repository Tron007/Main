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
	try{
	return Wt::WRun(argc, argv, &createApplication);
	} catch (const std::exception& e) {std::cout <<"MAIN error -> "<< e.what()<<std::endl;}
}

