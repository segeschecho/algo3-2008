//=========== (C) Copyright 2006 Zonda-E. All rights reserved. ===========
//
// Purpose: $
//
// by Gonzalez Pablo
//========================================================================


#include "memorymgr.h"
#include "memorypool.h"
#include "heap.h"
#include "heapfactory.h"

#include <assert.h>

#define MEMPOOL_SIGNATURE1		0x702DA00E
#define MEMPOOL_SIGNATURE2		0x9A810A60
#define MEMPOOL_SIGNATURE3		0x2110A010

#ifdef MEMPOOL_FILL
	static const char g_nUninitializedMemory = 0xCD;
	static const char g_nFreedMemory = 0xDD;
#endif


Heap * MemoryPool::s_pParentHeap = NULL;


int ConvertToPow2( int n, int nExponent )
{
	int remainder, nPow2;

	nPow2 = 1 << nExponent;
	remainder = (nPow2-1) & n;
	return n += ((nPow2 - remainder) & (nPow2 - 1));
}


MemoryPool::MemoryPool( size_t nObjectSize, char *heapName, uint numObjectsPerBlock )
{
	// round up the object size to a multiple of 16-bytes
	m_nObjectSize = ConvertToPow2( (int)nObjectSize, 4 );
	assert( m_nObjectSize >= 16 );

	// round up the block size to a multiple of 4KBytes
	m_nBlockSize = ConvertToPow2( numObjectsPerBlock*m_nObjectSize, 12 );
	assert( m_nBlockSize >= 4096 );

	if( s_pParentHeap == NULL )
		s_pParentHeap = HeapFactory::CreateHeap( "Memory Pools" );

	m_pHeap = HeapFactory::CreateHeap( heapName, "Memory Pools" );

	m_nNumObjectsPerBlock = (m_nBlockSize - sizeof(int)) / m_nObjectSize;

	Init();
}


void MemoryPool::Init()
{
	m_nNumAllocatedObjects = 0;
	m_nNumAllocatedBlocks = 0;
	m_nWastedBytes = 0;
	m_pHeadOfFreeList = NULL;
	m_pBlock = NULL;
}


MemoryPool::~MemoryPool()
{
	if( m_nNumAllocatedObjects > 0 )
	{
		// FIX ME!!! we shouldn't be using std::cout, instead we should use some function
		// to retrieve the desired stream where to put messages
		ReportLeaks();
	}

	Clear();
}


void* MemoryPool::Alloc( size_t nSize )
{
	assert( nSize <= m_nObjectSize );

	// check if there is no space in the current block to allocate data
	if( m_pHeadOfFreeList == NULL )
	{
		// create a new block
		char *pBlock = (char*)CreateNewBlock();
		m_pHeadOfFreeList = pBlock;

		// link the new block with the head block
		int *pNextBlock = (int*)GetNextBlockPtr( pBlock );
		*pNextBlock = (int)m_pBlock;

		// update the current block pointer
		m_pBlock = pBlock;
	}

	assert( m_pHeadOfFreeList != (void*)*(int*)m_pHeadOfFreeList );

	void *pMem = m_pHeadOfFreeList;
	m_pHeadOfFreeList = (void*)*(int*)m_pHeadOfFreeList;

	++m_nNumAllocatedObjects;
	m_nWastedBytes += (m_nObjectSize - nSize);

#ifdef MEMPOOL_FILL
	memset( pMem, g_nUninitializedMemory, nSize );
#else
	*((int*)pMem+1) = 0;
#endif

	return pMem;
}

void MemoryPool::Free( void *pMem, size_t nSize )
{
	if( pMem == NULL )
		return;

	// prevent from deallocating the same slice twice
	assert( m_pHeadOfFreeList != pMem );

#ifdef MEMPOOL_FILL
	memset( pMem, g_nFreedMemory, m_nSize );
#endif

	int *pSlice = (int*)pMem;

	*pSlice = (int)m_pHeadOfFreeList;
	m_pHeadOfFreeList = pSlice;

	*(pSlice+1) = MEMPOOL_SIGNATURE1;
	*(pSlice+2) = MEMPOOL_SIGNATURE2;
	*(pSlice+3) = MEMPOOL_SIGNATURE3;

	m_nWastedBytes -= (m_nObjectSize - nSize);
	--m_nNumAllocatedObjects;
}


void MemoryPool::Clear()
{
	if( m_nNumAllocatedObjects > 0 )
	{
		// DO SOMETHING! (should put a message in the messages queue
	}

	while( m_pBlock != NULL )
	{
		char *pNextBlock = (char*)*(int*)GetNextBlockPtr( m_pBlock );
		DestroyBlock( m_pBlock );
		m_pBlock = pNextBlock;
	}

	Init();
}


void * MemoryPool::CreateNewBlock()
{
	char *pBase;

	//pBase = (char*)_aligned_malloc( m_nBlockSize, MM_MEMORY_ALIGNMENT );
	pBase = new (m_pHeap) char[m_nBlockSize];

	if( pBase == NULL )
	{
		// DO SOMETHING!! (no memory available)
	}

	char *pBlock = pBase;

	for( uint i = 0; i < m_nNumObjectsPerBlock; i++ )
	{
		int* pSlice = (int*)pBlock;

		if( i != m_nNumObjectsPerBlock - 1 )
			*pSlice = (int)(pBlock + m_nObjectSize);
		else
			*pSlice = 0;

		// NextObject + Signatures = 16bytes (size of the smallest object)
		*(pSlice+1) = MEMPOOL_SIGNATURE1;
		*(pSlice+2) = MEMPOOL_SIGNATURE2;
		*(pSlice+3) = MEMPOOL_SIGNATURE3;

		pBlock += m_nObjectSize;
	}

	++m_nNumAllocatedBlocks;
//	m_pHeap->Add( m_nBlockSize );

	return pBase;
}


void MemoryPool::DestroyBlock( char *pBlock )
{
	//_aligned_free( pBlock );
	delete pBlock;

	--m_nNumAllocatedBlocks;
//	m_pHeap->Remove( m_nBlockSize );
}


char* MemoryPool::GetNextBlockPtr( char  *pBlock )
{
	return (pBlock + m_nBlockSize - sizeof(int));
}

#include <iostream>

void MemoryPool::ReportLeaks()
{
	std::ostream *os;

	os = &std::cout;

	*os << "Memory Pool: blocks left in memory " << m_nNumAllocatedObjects;
}