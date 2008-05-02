//=========== (C) Copyright 2006 Zonda-E. All rights reserved. ===========
//
// Purpose: memory allocation
//
// by Gonzalez Pablo
//========================================================================


#include "heap.h"

#include <assert.h>
#include <malloc.h>

#include <iomanip>

#pragma warning(disable:4996)

#define HEAPMEMORY_SIGNATURE			0xDEADC0DE

typedef unsigned int uint;

int Heap::s_dwNumCurAllocatedBlocks = 0;

struct AllocHeader {
	uint			dwSignature;
	uint			dwSize;
	uint			dwAllocNum;
	
	Heap			*pHeap;
	AllocHeader		*pPrev;
	AllocHeader		*pNext;
};


void Heap::Initialize()
{
	m_bActive		= false;

	m_pHeadAlloc		= NULL;
	m_bytesAllocated	= 0;
	m_bytesPeak			= 0;

	m_pParent		= NULL;
	m_pFirstChild	= NULL;
	m_pNextSibling	= NULL;
	m_pPrevSibling	= NULL;
}

bool Heap::IsActive() const
{
	return m_bActive;
}


void Heap::Activate( const char *szHeapName )
{
	assert( szHeapName != NULL );
	assert( strlen(szHeapName) < NAMELENGHT );

	m_bActive			= true;
	m_bytesAllocated	= 0;
	m_bytesPeak			= 0;

	strcpy( m_sName, szHeapName );
}


void Heap::Deactivate()
{
	strcpy( m_sName, "" );
	m_bActive = false;
	m_bytesAllocated	= 0;
	m_bytesPeak			= 0;
}

void* Heap::Allocate( size_t bytes )
{
	size_t bytesTotal = bytes + sizeof(AllocHeader);

#if defined(_WIN32) && defined(MM_MEMORY_ALIGNMENT)
	char* pMem = (char*)_aligned_malloc( bytesTotal, MM_MEMORY_ALIGNMENT );
#else
	char *pMem = (char*)malloc( bytesTotal );
#endif

	AllocHeader *pHeader = (AllocHeader*)pMem;

	pHeader->dwSignature = HEAPMEMORY_SIGNATURE;
	pHeader->dwSize = (uint)bytes;
	pHeader->pHeap = this;
	pHeader->pPrev = NULL;
	pHeader->pNext = m_pHeadAlloc;
	pHeader->dwAllocNum = ++s_dwNumCurAllocatedBlocks;

	if( m_pHeadAlloc != NULL )
		m_pHeadAlloc->pPrev = pHeader;

	m_pHeadAlloc = pHeader;

	Add( bytes );

	void *pStartMemoryBlock = pMem + sizeof(AllocHeader);
	return pStartMemoryBlock;
}


void Heap::Deallocate( void *pMem )
{
	AllocHeader *pHeader = (AllocHeader*)((char*)pMem - sizeof(AllocHeader));

	// check if the memory was allocated by our memory system
	assert( pHeader->dwSignature == HEAPMEMORY_SIGNATURE );
	pHeader->pHeap->Deallocate( pHeader );
}


void Heap::Deallocate( AllocHeader *pHeader )
{
	if( pHeader->pPrev == NULL )
	{
		assert( pHeader == m_pHeadAlloc );
		m_pHeadAlloc = pHeader->pNext;
	}else
		pHeader->pPrev->pNext = pHeader->pNext;

	if( pHeader->pNext != NULL )
		pHeader->pNext->pPrev = pHeader->pPrev;

	Remove( pHeader->dwSize );
	_aligned_free( pHeader );
}


void Heap::Add( size_t bytes )
{
	m_bytesAllocated += bytes;

	if( m_bytesAllocated > m_bytesPeak )
		m_bytesPeak = m_bytesAllocated;		// stores the peak memory load for this heap

	// increase the number of times this Heap has allocated memory blocks
	++m_dwNumInstances;
}


void Heap::Remove( size_t bytes )
{
	m_bytesAllocated -= bytes;
	--m_dwNumInstances;
}


const char * Heap::GetName() const
{
	return m_sName;
}


void Heap::AttachTo( Heap *pParent )
{
	assert( pParent != NULL );

	if( pParent == m_pParent )
		return;

	// First detach de heap from its current parent
	if( m_pPrevSibling != NULL )
		m_pPrevSibling->m_pNextSibling = m_pNextSibling;

	if( m_pNextSibling != NULL )
		m_pNextSibling->m_pPrevSibling = m_pPrevSibling;

	// Now attach the heap to the desired parent
	m_pParent = pParent;
	m_pNextSibling = pParent->m_pFirstChild;
	m_pPrevSibling = NULL;
	m_pParent->m_pFirstChild = this;
}


int Heap::GetMemoryBookmark()
{
	return Heap::s_dwNumCurAllocatedBlocks;
}

using namespace std;

int Heap::ReportMemoryLeaks( uint bookmark_start, uint bookmark_end, std::ostream &os )
{
	AllocHeader *pHeader = m_pHeadAlloc;
	uint dwLeaks = 0;

	while( pHeader != NULL )
	{
		if( pHeader->dwAllocNum >= bookmark_start && pHeader->dwAllocNum <= bookmark_end )
		{
			uint lvl = 0;

			os << "Heap: ";
			GetHierarchyStr( os, lvl );
			
			os << ". Size: " << pHeader->dwSize << ", Address: 0x" <<
					hex << uppercase << (int)((char*)pHeader + sizeof(AllocHeader)) << endl;
			dec(os);
			++dwLeaks;
		}
		pHeader = pHeader->pNext;
	}

	return dwLeaks;
}


void Heap::GetHierarchyStr( std::ostream &os, uint &lvl )
{
	if( m_pParent != NULL )
	{
		m_pParent->GetHierarchyStr( os, ++lvl );
	}

	os << m_sName;
	
	if( lvl > 0 )
	{
		os << "->";
		--lvl;
	}

}

size_t Heap::getPeak() {
	return m_bytesPeak;
}

void Heap::GetMemoryReport( std::ostream &os )
{
	Heap *pHeap = this;
	static uint ident = 0;

	while( pHeap != NULL )
	{
		size_t totalBytesAlloc = 0, totalBytesPeak = 0;
		uint totalInstances = 0;

		pHeap->GetTreeStats( totalBytesAlloc, totalBytesPeak, totalInstances );
		os.fill(' ');
		os << setw(ident*2) << "" << pHeap->m_sName;

		os << setw(24-(strlen(pHeap->m_sName)+ident*2)) << "" <<
				setw(10) << pHeap->m_bytesAllocated <<
				setw(11) << pHeap->m_bytesPeak <<
				setw(6)	<< pHeap->m_dwNumInstances <<
				setw(10) << totalBytesAlloc <<
				setw(11) << totalBytesPeak <<
				setw(6)	<< totalInstances <<
				endl;

		Heap *pChild = pHeap->m_pFirstChild;

		if( pChild )
		{
			++ident;
			pChild->GetMemoryReport( os );
			--ident;
		}

		pHeap = pHeap->m_pNextSibling;
	}
}

void Heap::GetTreeStats( size_t &totalBytes, size_t &totalPeak, uint &totalInstances )
{
	totalBytes += m_bytesAllocated;
	totalPeak += m_bytesPeak;
	totalInstances += m_dwNumInstances;

	Heap *pChild = m_pFirstChild;
	while( pChild != NULL )
	{
		pChild->GetTreeStats( totalBytes, totalPeak, totalInstances );
		pChild = pChild->m_pNextSibling;
	}
}