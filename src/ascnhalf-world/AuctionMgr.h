/* AscNHalf */

#ifndef __AUCTIONMGR_H
#define __AUCTIONMGR_H

class AuctionHouse;
class AuctionMgr : public Singleton <AuctionMgr>
{
public:
	AuctionMgr()
	{
		loopcount = 0;
		maxId = 1;
	}

	~AuctionMgr()
	{
		vector<AuctionHouse*>::iterator itr = auctionHouses.begin();
		for(; itr != auctionHouses.end(); ++itr)
			delete (*itr);
	}

	void LoadAuctionHouses();
	void Update();

	AuctionHouse * GetAuctionHouse(uint32 Entry);

	uint32 GenerateAuctionId()
	{ 
		lock.Acquire();
		uint32 id=++maxId;
		lock.Release();
		return id;
	}

	vector<AuctionHouse*>::iterator GetAuctionHousesBegin() { return auctionHouses.begin(); }
	vector<AuctionHouse*>::iterator GetAuctionHousesEnd() { return auctionHouses.end(); }

private:
	HM_NAMESPACE::hash_map<uint32, AuctionHouse*> auctionHouseEntryMap;
	vector<AuctionHouse*> auctionHouses;
	volatile uint32 maxId;
	Mutex lock;
	uint32 loopcount;
};

#define sAuctionMgr AuctionMgr::getSingleton()

#endif
