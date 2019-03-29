#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include <string>

using namespace std;

int GetAllClientsBalance(CBank bank);

int main(int argc, char *argv[])
{
	int bankClientsQuantity;
	if (argc != 2)
	{
		bankClientsQuantity = 8;
	}
	else
	{
		try
		{
			bankClientsQuantity = stoi(argv[1]);
		}
		catch (exception ex)
		{
			cout << "<bankClientQuantity> must be a number";
			return 1;
		}
	}

	CBank* bank = new CBank();
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

int GetAllClientsBalance(CBank bank)
{
	int result = 0;
	for each (CBankClient client in bank.GetCurrentClients())
	{
		result += bank.GetClientBalance(client.GetId());
	}

	return result;
}