#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "BankClient.h"

class CBank
{
public:
	CBank();
	CBankClient* CreateClient();
	std::vector<CBankClient> GetCurrentClients();
	int GetTotalBalance();
	int GetClientBalance(int clientId);
	void UpdateClientBalance(CBankClient& client, int value);

private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;
	std::map<int, int> m_clientBalanceById;

	void SetTotalBalance(int value);
	void SomeLongOperations();
};