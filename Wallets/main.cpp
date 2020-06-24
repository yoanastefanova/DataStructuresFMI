#include "FMIcoins.h"
#include <iostream>
#include <time.h>




int main()
{
	Wallet wal("gogo", 123);

	Wallet wal2("sasho", 849);

	Wallet wal3("peshooo", 3017);

	Wallet wal4("baltazar", 10030);
	
	wal.addWallet();
	wal2.addWallet();	
	wal3.addWallet();
	wal4.addWallet();

	wal.print();
	wal2.print();
	wal3.print();
	wal4.print();
	
	wal4.output();

	//std::cout << getFMIcoins(41);
	
	//Order ord(Type::BUY, 200, 41);

	

	// trans(19169, 41, 500);

	//trans.transfer1(wal, wal3, 20);
	

	/*
	char ch;

	while (in.get(ch))
	{
		std::cout << ch;
	}
	*/
	

	
	system("pause");

	return 0;
}