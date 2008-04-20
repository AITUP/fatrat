#ifndef _FRQUEUE_H
#define _FRQUEUE_H
#include <QDomNode>
#include <QReadWriteLock>
#include <QList>
#include <QUuid>
#include "Transfer.h"

class Queue : public QObject
{
Q_OBJECT
public:
	Queue();
	~Queue();
	
	static void loadQueues();
	static void saveQueues();
	static void unloadQueues();
	
	void setSpeedLimits(int down,int up) { m_nDownLimit=down; m_nUpLimit=up; }
	void speedLimits(int& down, int& up) const { down=m_nDownLimit; up=m_nUpLimit; }
	
	void setTransferLimits(int down = -1,int up = -1) { m_nDownTransferLimit=down; m_nUpTransferLimit=up; }
	void transferLimits(int& down,int& up) const { down=m_nDownTransferLimit; up=m_nUpTransferLimit; }
	
	void setName(QString name) { m_lock.lockForWrite(); m_strName=name; m_lock.unlock(); }
	QString name() const { m_lock.lockForRead(); QString s=m_strName; m_lock.unlock(); return s; }
	
	QString uuid() const { return m_uuid.toString(); }
	
	bool upAsDown() const { return m_bUpAsDown; }
	void setUpAsDown(bool v) { m_bUpAsDown=v; }
	
	int size();
	
	void lock() { m_lock.lockForRead(); }
	void lockW() { m_lock.lockForWrite(); }
	void unlock() { m_lock.unlock(); }
	Transfer* at(int r);
	
	void add(Transfer* d);
	void add(QList<Transfer*> d);
	
	int moveDown(int n);
	int moveUp(int n);
	void moveToTop(int n);
	void moveToBottom(int n);
	void moveToPos(int from, int to);
	
	void remove(int n, bool nolock = false);
	void removeWithData(int n, bool nolock = false);
	Transfer* take(int n, bool nolock = false);
	
	void autoLimits(int& down, int& up) const { down=m_nDownAuto; up=m_nUpAuto; }
	void setAutoLimits(int down, int up);
private:
	void loadQueue(const QDomNode& node);
	void saveQueue(QDomNode& node,QDomDocument& doc);
	
	QString m_strName;
	int m_nDownLimit,m_nUpLimit,m_nDownTransferLimit,m_nUpTransferLimit;
	int m_nDownAuto, m_nUpAuto;
	bool m_bUpAsDown;
	QUuid m_uuid;
	mutable QReadWriteLock m_lock;
public:
	// statistics
	struct Stats
	{
		int active_d, waiting_d, active_u, waiting_u;
		int down, up;
	} m_stats;
protected:
	QList<Transfer*> m_transfers;
	
	friend class QueueMgr;
};

#endif
