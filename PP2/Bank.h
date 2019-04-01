#pragma once
#include <iostream>
#include <vector>
#include <map>

#include <mutex>
#include "BankClient.h"
#include "SyncPrimitiveType.h"

class CBank
{
public:
	CBank(SyncPrimitiveType syncPrimitiveType);
	~CBank();
	CBankClient* CreateClient();
	std::vector<CBankClient> GetCurrentClients();
	int GetTotalBalance();
	int GetClientBalance(int clientId);
	void UpdateClientBalance(CBankClient& client, int value);

private:
	std::vector<CBankClient> m_clients;
	CRITICAL_SECTION m_csClientBalanceUpdate;
	std::mutex m_clientBalanceUpdateMutex;
	int m_totalBalance;
	std::map<int, int> m_clientBalanceById;
	SyncPrimitiveType m_syncPrimitiveType;

	void SetTotalBalance(int value);
	void SomeLongOperations();
	void LockByPrimitiveSyncType();
	void UnlockByPrimitiveSyncType();
};