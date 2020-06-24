#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>


const unsigned long genericWal = 4294967295;
const int course = 375;

bool existsID(unsigned long _id);
const char *getName(unsigned long _id);
const unsigned long getID(const char* _name);
const double getMoney(const char* _name);
double getFMIcoins(unsigned long _id);


struct Wallet
{
	Wallet();
	Wallet(const char* _name, double _money);
	
	void addWallet();//да
	void print() const;//да

	//unsigned long getID() const;


	char owner[256];
	double fiatMoney;
	unsigned long id; // unsigned long <= 4 294 967 295 
	double fmiCoins = fiatMoney / course;


	
	const char* getOwnerWal() const;
	double getMoneyWal() const;
	unsigned long getIDWal() const;
	double getFmiCoinsWal() const;


	friend std::ostream& operator<<(std::ostream& out, const Wallet& wal);//да
	void output();
	
};



enum class Type { BUY, SELL };

struct Transaction : public Wallet
{ 
	Transaction(const char* _name); // к-тор за трансакцията, която се осъществява при създаване на портфейл
	Transaction(unsigned long _sen, unsigned long _rec, double _coins);

	void addTransaction();//unsigned long _sen, unsigned long _rec, double _coins);

	bool hasEnough(unsigned long _id, double _coins);
	void transfer(unsigned long _sen, unsigned long _rec, double _fmiCoins);
	void transfer1(Wallet &_rec, Wallet &_sen, double _coins);
	
	void printTrans();

	time_t curTime; // времето от 01.01.1970г 00:00ч.
	unsigned long senderId;
	unsigned long receiverId;
	double fmiCoins;
};

struct Order 
{
	Order(Type _type, double _coins, unsigned long _walID);

	void makeOrder(Type _type, double _coins, unsigned long _walID);

	Type type;
	unsigned long walletID;
	double fmiCoins;
};


struct WalletList
{
	WalletList();
	~WalletList();


	Wallet** listWal;
	size_t size;
	size_t capacity;


	void resizeUp();
	void resizeDown();

};

struct OrderList
{
	OrderList();
	~OrderList();


	Order** listOrd;
	size_t size;
	size_t capacity;


	void resizeUp();
	void resizeDown();

};

struct TransList
{
	TransList();
	~TransList();


	Transaction** listTrans;
	size_t size;
	size_t capacity;

			
	void resizeUp();
	void resizeDown();


};

