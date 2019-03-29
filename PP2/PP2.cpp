#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <string>
#include "SyncPrimitiveType.h"

using namespace std;

int GetAllClientsBalance(CBank& bank);

int main(int argc, char *argv[])
{
	int bankClientsQuantity;
	SyncPrimitiveType syncPrimitiveType;
	if (argc != 3)
	{
		bankClientsQuantity = 2;
	}
	else
	{
		try
		{
			bankClientsQuantity = stoi(argv[1]);
			syncPrimitiveType = (SyncPrimitiveType)stoi(argv[2]);
		}
		catch (exception ex)
		{
			cout << "program.exe <bank clients quantity> <synchronization primitive type>";
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