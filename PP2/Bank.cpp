#include "Bank.h"
#include <windows.h>

CBank::CBank(SyncPrimitiveType syncPrimitiveType)
{
	InitializeCriticalSection(&m_csClientBalanceUpdate);
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
	m_syncPrimitiveType = syncPrimitiveType;
}

CBank::~CBank()
{
	DeleteCriticalSection(&m_csClientBalanceUpdate);
}

CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clientBalanceById[clientId] = 0;
	m_clients.push_back(*client);
	return client;
}

std::vector<CBankClient> CBank::GetCurrentClients()
{
	return m_clients;
}

void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	LockByPrimitiveSyncType();

	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;

	SomeLongOperations();
	totalBalance += value;
	m_clientBalanceById[client.m_id] += value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value) {
		std::cout << "! ERROR !" << std::endl;
	}

	SetTotalBalance(totalBalance);

	UnlockByPrimitiveSyncType();
}

int CBank::GetTotalBalance()
{
	return m_totalBalance;
}

int CBank::GetClientBalance(int clientId)
{
	return m_clientBalanceById[clientId];
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
	Sleep(1000);
}

void CBank::LockByPrimitiveSyncType()
{
	if (m_syncPrimitiveType == SyncPrimitiveType::Mutex)
	{
		m_clientBalanceUpdateMutex.lock();
	}
	else if (m_syncPrimitiveType == SyncPrimitiveType::CriticalSection)
	{
		EnterCriticalSection(&m_csClientBalanceUpdate);
	}
}

void CBank::UnlockByPrimitiveSyncType()
{
	if (m_syncPrimitiveType == SyncPrimitiveType::Mutex)
	{
		m_clientBalanceUpdateMutex.unlock();
	}
	else if (m_syncPrimitiveType == SyncPrimitiveType::CriticalSection)
	{
		LeaveCriticalSection(&m_csClientBalanceUpdate);
	}
}
