#include <cstring>
#include <fstream>
#include "FMIcoins.h"


//void makeOrder(Type _type, double _coins, unsigned long _walletID);

bool existsID(unsigned long _id)//������� �-�, ����� ��������� ���� ������ ID �� ������� ��� ����� wallets.dat
{
	std::ifstream in("wallets.dat", std::ifstream::binary);// | std::ios::beg);

	Wallet temp;//buffer

	while (in)// ����� �������� ������� ���� �������� � ���������� ��������� ����������
	{
		in.read(temp.owner, sizeof(temp.owner));
		in.read((char*)&(temp.fiatMoney), sizeof(temp.fiatMoney));
		in.read((char*)&(temp.id), sizeof(temp.id));
		in.read((char*)&temp.fmiCoins, sizeof(temp.fmiCoins));

		if ((temp.id) == _id)
		{
			in.close();
			return true;
		}
	}
	in.close();
	return false;
}

const char * getName(unsigned long _id)
{
	std::ifstream in("wallets.dat", std::ios::binary);

	Wallet temp;

	while (in)//.read(reinterpret_cast<char*>(&(temp)), sizeof(temp)))
	{		
		in.read((temp.owner), sizeof(temp.owner));
		in.read((char*)&(temp.fiatMoney), sizeof(temp.fiatMoney));
		in.read((char*)&(temp.id), sizeof(temp.id));
		in.read((char*)&temp.fmiCoins, sizeof(temp.fmiCoins));
		
		if ((temp.id) == _id)
		{
			in.close();
			return temp.owner;
		}		
	}
	in.close();
	return 0;
}

const unsigned long getID(const char * _name)
{

	std::ifstream in("wallets.dat", std::ios::binary);

	Wallet temp;

	while (in)//.read(reinterpret_cast<char*>(&(temp)), sizeof(temp)))
	{
		
		in.read((temp.owner), sizeof(temp.owner));
		in.read((char*)&(temp.fiatMoney), sizeof(temp.fiatMoney));
		in.read((char*)&(temp.id), sizeof(temp.id));
		in.read((char*)&temp.fmiCoins, sizeof(temp.fmiCoins));
		

		if (strcmp((temp.owner), _name) == 0)
		{
			in.close();
			return temp.id;			
		}
	}
	in.close();	
	return 0;
}

const double getMoney(const char * _name)
{
	std::ifstream in("wallets.dat", std::ios::binary);

	Wallet temp;

	while (in)//.read(reinterpret_cast<char*>(&(temp)), sizeof(temp)))
	{
		
		in.read((temp.owner), sizeof(temp.owner));
		in.read((char*)&(temp.fiatMoney), sizeof(temp.fiatMoney));
		in.read((char*)&(temp.id), sizeof(temp.id));
		in.read((char*)&temp.fmiCoins, sizeof(temp.fmiCoins));
		

		if ((temp.owner) == _name) // ��� ���������� ������ ID, �� ���������� ������������ ������ �� �����������
		{
			in.close();
			return temp.fiatMoney;
		}
	}

	in.close();
	return 0;
}

double getFMIcoins(unsigned long _id)
{
	std::ifstream in("wallets.dat", std::ios::binary);

	Wallet temp;

	while (in)//.read(reinterpret_cast<char*>(&(temp)), sizeof(temp)))
	{
		
		in.read((temp.owner), sizeof(temp.owner));
		in.read((char*)&(temp.fiatMoney), sizeof(temp.fiatMoney));
		in.read((char*)&(temp.id), sizeof(temp.id));
		in.read((char*)&(temp.fmiCoins), sizeof(temp.fmiCoins));
		
		if ((temp.id) == _id)
		{
			in.close();
			return temp.fmiCoins;
		}		
	}
	in.close();
	return 0;
}

std::ostream & operator<<(std::ostream & out, const Wallet & wal)
{
	out << wal.owner << "\n"
		<< wal.fiatMoney << "\n"
		<< wal.id << "\n"
		<< wal.fmiCoins;

	return out;
}


Wallet::Wallet()
{
	owner[0] = '\0';
	fiatMoney = 0;	
	id = rand() % 1000000000;
	fmiCoins = 0;
}


Wallet::Wallet(const char* _name, double _money)
{
	id = rand() % 1000000000;
	fiatMoney = _money;
	fmiCoins = fiatMoney / course;
	
	strcpy_s(owner, strlen(_name) + 1, _name);	
	

	Transaction::Transaction(_name); //��� ��������� �� �������� �� ����������� � ���� ���������� � ������� genericWal
}


const char* Wallet::getOwnerWal() const
{
	return owner;
}

double Wallet::getMoneyWal() const 
{
	return fiatMoney;
}

unsigned long Wallet::getIDWal() const
{
	return id;
}

double Wallet::getFmiCoinsWal() const
{
	return fmiCoins;
}

void Wallet::output()
{
	std::ifstream in("wallets.dat", std::ios::binary);

	Wallet wallet;

	if (in)
	{
		while (in)//.read(reinterpret_cast<char*>(&wallet), sizeof(wallet)))
		{
			std::cout << wallet;
		}
		in.close();
	}

	in.close();
}

// kalin.iliev6@gmail.com

void Wallet::addWallet()
{
	std::ofstream wallets("wallets.dat", std::ios::binary | std::ios::app);

	if (wallets)
	{
		wallets.write(owner, sizeof(owner));
		wallets.write((const char*)&fiatMoney, sizeof(fiatMoney));
		wallets.write((const char*)&id, sizeof(id));
		wallets.write((const char*)&fmiCoins, sizeof(fmiCoins));	

		//wallets.close();
	}
	wallets.close();
}

void Wallet::print() const
{
	std::cout <<"Owner: "<<  owner << '\n'
		<<"Money: "<<  fiatMoney << '\n'
		<<"ID: "<< id << '\n'
		<<"FMI Coins: " << fmiCoins <<'\n'<<'\n';
}


Transaction::Transaction(const char* _name)
{
	senderId = genericWal;
	receiverId = getID(_name);
	fmiCoins = getMoney(_name) / course;
	curTime = time(nullptr);
	

	std::ofstream trans("transactions.dat", std::ios::binary | std::ios::app);

	while (trans)
	{
		trans.write((const char*)&senderId, sizeof(senderId));
		trans.write((const char*)&receiverId, sizeof(receiverId));
		trans.write((const char*)&fmiCoins, sizeof(fmiCoins));

		trans.close();
	}	
}

Transaction::Transaction(unsigned long _sen, unsigned long _rec, double _coins)
{
	senderId = _sen;
	receiverId = _rec;
	fmiCoins = _coins;	
	curTime = time(nullptr);	
}

void Transaction::addTransaction()//unsigned long _sen, unsigned long _rec, double _coins)
{
	std::ofstream trans("transactions.dat", std::ios::binary | std::ios::app);

	if (trans)
	{
		trans.write((const char*)&receiverId, sizeof(receiverId));
		trans.write((const char*)&senderId, sizeof(senderId));
		trans.write((const char*)&fmiCoins, sizeof(fmiCoins));
		//	trans.write((const char*)&t, sizeof(t));

		trans.close();
	}
}

bool Transaction::hasEnough(unsigned long _id, double _coins)
{
	std::ifstream in("wallets.dat", std::ios::binary);
	
	Wallet temp;
	
	while (in)
	{
		in.read((temp.owner), sizeof(temp.owner));
		in.read((char*)&(temp.fiatMoney), sizeof(temp.fiatMoney));
		in.read((char*)&(temp.id), sizeof(temp.id));

		if ((temp.id) == _id) // ��� ���������� ������ ID, �� ���������� ������������ ������ �� �����������
		{
			in.close();
			return temp.fmiCoins >= _coins;
		}
	}
	in.close(); 
}

void Transaction::transfer(unsigned long _sen, unsigned long _rec, double _fmiCoins)
{
	std::ofstream transf("transactions.dat", std::ios::binary | std::ios::app);

	//unsigned long curTime = time;

	if (existsID(_sen) && existsID(_rec))
	{
		if (hasEnough(_sen, _fmiCoins))
		{
				while (transf)
				{
					transf.write(getName(_sen), sizeof(getName(_sen)));
					transf.write(getName(_rec), sizeof(getName(_rec)));
					transf.write((const char*)&_fmiCoins, sizeof(_fmiCoins));					
				}

				transf.close();
		}		
	}

	else
		std::cout << "Invalid IDs" << '\n';

	transf.close();

}

void Transaction::transfer1(Wallet & _rec, Wallet & _sen, double _coins)
{
	std::ofstream transf("transactions.dat", std::ios::binary | std::ios::app);		

	//unsigned long curTime = time;

	if (existsID(_sen.id) && existsID(_rec.id))
	{
		if (hasEnough(_sen.id, _coins))
		{
			_sen.fmiCoins = _sen.getFmiCoinsWal() - _coins;
			_rec.fmiCoins = _rec.getFmiCoinsWal() + _coins;

			while (transf)
			{
				transf.write((_sen.owner), sizeof(_sen.owner));
				transf.write((_rec.owner), sizeof(_rec.owner));
				transf.write((const char*)&_coins, sizeof(_coins));
			}

			transf.close();
		}

		else
			std::cout << "The sender doesn't have enough FMI coins!\n";

		transf.close();
	}

	else
		std::cout << "Invalid IDs\n";

	transf.close();

}

void Transaction::printTrans()
{
	std::cout << "Sender ID: " << senderId << "\n"
		<< "Receiver ID: " << receiverId << "\n"
		<< "FMI Coins: " << fmiCoins<<"\n";
}


Order::Order(Type _type, double _coins, unsigned long _walID)
{
	type = _type;
	fmiCoins = _coins;
	walletID = _walID;
}

void Order::makeOrder(Type _type, double _coins, unsigned long _walID)
{
	/*

	 -------------------------------SELL----------------------------------
	 1.������ �� ��� ���������� ����� walID ��� ����� wallets.dat ------- ��
	 2.����������� _walID ������ �� ��� FMIcoins >= �� ����, ����� ���� �� ������� (�� �� ��
	   ������� ����� FMIcoins ���, ������ �� �� ��������� ����������� ����������, � ����� �
	   �������) - ��������� �� ��������� ���� �� ������������ �� � genericWal.
	   -->������ �� �� �������� ����������� Orders �� ���� ��������, ������ �� ���� �� ��������
		  � ������ �� ���� �� �� �������� �� �������� ���������
	 3.������ �� �� ������� ���� ��� Order �� �������� �� FMIcoins � �� ����������� ����� ���
	   ������ �� ���. ��� ��� ������������ BUY ����������, �� �� �� ����������� �������� SELL
	   Order, ��������� �� �������� ��������� �� ������� ��� ����� orders.dat
	 4.��������� ������ �� ��� ���������� fiatMoney, � ���������� - FMIcoins
	 5.������������ ���������� �� BUY �� ��������� �� ������� � ���������� � �� ����� �� ��� ��
	   ������� ���������� ��� ����� transactions.dat ��� ���������� �������, ��������� � ������.
	 6.�� ����� ��������� ���������� ������ �� �� ������ ��������� �� fiatMoney ��� �������� �
	   FMIcoins ��� ��������, ���� �� �������� ������ �� ����������.
	*/


	if (!existsID(_walID))
	{
		std::cout << "Non-existent ID!";
		return;
	}

	else
	{
		if (_type == Type::SELL)
		{
		

		}


		else if (_type == Type::BUY)
		{


		}

		else
			std::cout << "Invalid type! Enter either SELL or BUY.\n";
	}



	/*
	 ------------------------------BUY-------------------------------------
	 1.������ �� ��� ���������� ����� walID ��� ����� wallets.dat
	 2.����������� ������ �� ��� ���������� fiatMoney, �� �� ������ ������� ���� FMIcoins,
	   �������� �� ����� �� ����������.
	   ---> ������ �� �� ������� � ��������� Orders ���� ���� ���������� �� ����� _walID, ���
			���� �� �� ���� �������� � ������ �� ���� �� �� ��������
	 3.������ �� �� ������� ���� ��� ���������� �� SELL �� FMIcoins � �� �� ������������ ����� ���
	   ������ �� ��� � ����, � ����� �� ��������.
	 4.��������� ������ �� ��� ���������� fiatMoney, � ���������� - FMIcoins
	 5.���������� �� ������ �� SELL �� ������ ������ �� ������� ������ ������ ORder ��� ������ ���� ������ ��������� ������.
	 6.��� �� ����� �� ���� ���������� Orders, �� �� ���� �������� �� �� ����������� �������, �� ������ ��������� �������� Order
	   ��� ����� orders.dat, �� ��� ��������� ����������� ���������� FMIcoins
	 7.�� ����� �� ����������� ���������� � ���� ������ ������ �� �� ������� ����� �� ���������� ��� ����������� ���������, �������� � ������
	 8.����� ��������� ���������� �� �������� �� transactions.dat
	 9.�� ����� ��������� ���������� ������ �� �� ������ ��������� �� fiatMoney ��� �������� �
	   FMIcoins ��� ��������, ���� �� �������� ������ �� ����������.

	*/
}

TransList::TransList() : size(0), capacity(8)
{
	listTrans = new Transaction*[capacity];
}

TransList::~TransList()
{
	for (size_t i = 0; i < size; ++i)
	{
		delete listTrans[i];
	}

	delete[] listTrans;
}

void TransList::resizeDown()
{
	capacity = capacity / 2;
	Transaction** newTrans = new Transaction*[capacity];

	for (size_t i = 0; i < size; ++i)
	{
		newTrans[i] = listTrans[i];
	}

	delete[] listTrans;
	listTrans = newTrans;
}

void TransList::resizeUp()
{
	capacity = capacity * 2;
	Transaction** newTrans = new Transaction*[capacity];

	for (size_t i = 0; i < size; ++i)
	{
		newTrans[i] = listTrans[i];
	}

	delete[] listTrans;
	listTrans = newTrans;
}

WalletList::WalletList() : size(0), capacity(8)
{
	listWal = new Wallet*[capacity];
}

WalletList::~WalletList()
{
	for (size_t i = 0; i < size; ++i)
	{
		delete listWal;
	}

	delete[] listWal;
}

OrderList::OrderList() : size(0), capacity(8)
{
	listOrd = new Order*[capacity];
}

OrderList::~OrderList()
{
	for (size_t i = 0; i < size; ++i)
	{
		delete listOrd;
	}

	delete[] listOrd;
}
