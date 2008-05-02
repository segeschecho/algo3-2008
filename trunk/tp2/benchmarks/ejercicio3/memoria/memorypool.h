//=========== (C) Copyright 2006 Zonda-E. All rights reserved. ===========
//
// Purpose: $
//
// by Gonzalez Pablo
//========================================================================


#ifndef __MEMORY_POOL_H__
#define __MEMORY_POOL_H__

#include <cstddef>

class Heap;

typedef unsigned int uint;

class MemoryPool {
public:
	MemoryPool( size_t nObjectSize, char *heapName, uint numObjectsPerBlock = 256 );
	~MemoryPool();

	void* Alloc( size_t nSize );
	void Free( void *pMem, size_t nSize );

	void Clear();

private:
	MemoryPool( const MemoryPool &m );					// prevents the class to be copied
	MemoryPool &operator=( const MemoryPool & );		// prevents the class to be copied
	void Init();
	char* GetNextBlockPtr( char *pBlock );
	void* CreateNewBlock();
	void DestroyBlock( char *pBlock );

	void ReportLeaks();

	uint m_nBlockSize;
	uint m_nObjectSize;
	uint m_nNumObjectsPerBlock;
	uint m_nNumAllocatedBlocks;
	uint m_nNumAllocatedObjects;
	uint m_nWastedBytes;
	char *m_pBlock;
	
	void *m_pHeadOfFreeList;
	
	Heap *m_pHeap;
	static Heap *s_pParentHeap;
};

#endif