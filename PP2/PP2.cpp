#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <string>
#include "SyncPrimitiveType.h"
#include <vector>
#include <optional>

using namespace std;

int GetAllClientsBalance(CBank& bank);

void PrintHelp();
optional<int> getParsed(string arg);

int main(int argc, char *argv[])
{
	const string helpCommand = "./h";

	int bankClientsQuantity;
	SyncPrimitiveType syncPrimitiveType;
	if (argc == 2 && (string)argv[1] == helpCommand)
	{
		PrintHelp();
		return 1;
	}

	optional<int> firstIntArg = getParsed(argv[1]);
	if (!firstIntArg.has_value())
	{
		PrintHelp();
		return 1;
	}

	if (argc == 2)
	{
		bankClientsQuantity = 2;
		syncPrimitiveType = (SyncPrimitiveType)firstIntArg.value();
	}
	else if (argc == 3)
	{
		bankClientsQuantity = firstIntArg.value();
		optional<int> secondIntArg = getParsed(argv[2]);
		if (!secondIntArg.has_value())
		{
			PrintHelp();
			return 1;
		}
		syncPrimitiveType = (SyncPrimitiveType)secondIntArg.value();
	}
	else
	{
		PrintHelp();
		return 1;
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

optional<int> getParsed(string arg)
{
	try
	{
		return stoi(arg);
	}
	catch (exception ex)
	{
		return {};
	}
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