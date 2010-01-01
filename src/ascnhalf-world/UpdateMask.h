/* AscNHalf */

#ifndef __UPDATEMASK_H
#define __UPDATEMASK_H

class UpdateMask
{
	uint32 *mUpdateMask;
	uint32 mCount; // in values
	uint32 mBlocks; // in uint32 blocks

public:
	UpdateMask( ) : mUpdateMask( 0 ), mCount( 0 ), mBlocks( 0 ) { }
	UpdateMask( const UpdateMask& mask ) : mUpdateMask( 0 ) { *this = mask; }

	~UpdateMask( )
	{
		if(mUpdateMask)
			delete [] mUpdateMask;
	}

	void SetBit( const uint32 index )
	{
		ASSERT(index < mCount);
		( (uint8 *)mUpdateMask )[ index >> 3 ] |= 1 << ( index & 0x7 );
		// ( (uint8 *)mUpdateMask )[ index / 8 ] |= 1 * pow( 2, index % 8 );
	}

	void UnsetBit( const uint32 index )
	{
		ASSERT(index < mCount);
		( (uint8 *)mUpdateMask )[ index >> 3 ] &= (0xff ^ (1 <<  ( index & 0x7 ) ) );
		// ( (uint8 *)mUpdateMask )[ index / 8 ] &= 255 - ( 1 * pow( 2, index % 8 ) ) );
	}

	bool GetBit( const uint32 index ) const
	{
		ASSERT(index < mCount);
		return ( ( (uint8 *)mUpdateMask)[ index >> 3 ] & ( 1 << ( index & 0x7 ) )) != 0;
		//actually int->bool conversion is not needed here
	}

	uint32 GetUpdateBlockCount() const 
	{
		uint32 x;
		for( x=mBlocks-1;x;x--)
			if(mUpdateMask[x])break;
		return (x+1); 
	}
	INLINE uint32 GetBlockCount() const {return mBlocks;}
	
	INLINE uint32 GetLength() const { return (mBlocks *sizeof(uint32)); }
	INLINE uint32 GetCount() const { return mCount; }
	INLINE const uint8* GetMask() const { return (uint8*)mUpdateMask; }

	void SetCount(uint32 valuesCount)
	{
		if(mUpdateMask)
			delete [] mUpdateMask;

		mCount = valuesCount;
		//mBlocks = valuesCount/32 + 1;
		//mBlocks = (valuesCount + 31) / 32;
		mBlocks = mCount >> 5;
		if(mCount & 31)
			++mBlocks;

		mUpdateMask = new uint32[mBlocks];
		memset(mUpdateMask, 0, mBlocks *sizeof(uint32));
	}

	void Clear()
	{
		if (mUpdateMask)
			memset(mUpdateMask, 0, mBlocks << 2);
	}

	UpdateMask& operator = ( const UpdateMask& mask )
	{
		SetCount(mask.mCount);
		memcpy(mUpdateMask, mask.mUpdateMask, mBlocks << 2);

		return *this;
	}

	void operator &= ( const UpdateMask& mask )
	{
		ASSERT(mask.mCount <= mCount);
		for(uint32 i = 0; i < mBlocks; i++)
			mUpdateMask[i] &= mask.mUpdateMask[i];
	}

	void operator |= ( const UpdateMask& mask )
	{
		ASSERT(mask.mCount <= mCount);
		for(uint32 i = 0; i < mBlocks; i++)
			mUpdateMask[i] |= mask.mUpdateMask[i];
	}

	UpdateMask operator & ( const UpdateMask& mask ) const
	{
		ASSERT(mask.mCount <= mCount);

		UpdateMask newmask;
		newmask = *this;
		newmask &= mask;

		return newmask;
	}

	UpdateMask operator | ( const UpdateMask& mask ) const
	{
		ASSERT(mask.mCount <= mCount);

		UpdateMask newmask;
		newmask = *this;
		newmask |= mask;

		return newmask;
	}
};

#endif

