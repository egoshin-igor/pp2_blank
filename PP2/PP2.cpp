#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <string>
#include "SyncPrimitiveType.h"
#include <vector>

using namespace std;

int GetAllClientsBalance(CBank& bank);

void PrintHelp();

int main(int argc, char *argv[])
{
	int bankClientsQuantity;
	SyncPrimitiveType syncPrimitiveType;
	if (argc == 2 && (string)argv[1] == "./h")
	{
		PrintHelp();
		return 1;
	}

	if (argc == 2)
	{
		bankClientsQuantity = 2;
		try
		{
			syncPrimitiveType = (SyncPrimitiveType)stoi(argv[1]);
		}
		catch (exception ex)
		{
			PrintHelp();
			return 1;
		}
	}
	else if (argc == 3)
	{
		try
		{
			bankClientsQuantity = stoi(argv[1]);
			syncPrimitiveType = (SyncPrimitiveType)stoi(argv[2]);
		}
		catch (exception ex)
		{
			PrintHelp();
			return 1;
		}

	}

	CBank* bank = new CBank(syncPrimitiveType);
	for (int i = 0; i < bankClientsQuantity; i++)
	{
		bank->CreateClient();
	}

	bool isExit = false;
	while (!isExit)
	{
		string command;
		cin >> command;
		if (command == "exit")
		{
			isExit = true;
			cout << "\nBank balance: " << bank->GetTotalBalance() << '\n';
			cout << "All clients balance: " << GetAllClientsBalance(*bank) << '\n';
			for each (CBankClient client in bank->GetCurrentClients())
			{
				cout << "Client: " << client.GetId() << ". Balance: " << bank->GetClientBalance(client.GetId()) << '\n';
			}
		}
	}

	return 0;
}

int GetAllClientsBalance(CBank& bank)
{
	int result = 0;
	for each (CBankClient client in bank.GetCurrentClients())
	{
		result += bank.GetClientBalance(client.GetId());
	}

	return result;
}

void PrintHelp()
{
	cout << "Type <program> <banksClientQuantity>(optional, default is 2) <syncPrimitive>";
	cout << "Sync primitive types:" << endl << "0 - Mutex, 1 - CriticalSection, 2 - None";
}