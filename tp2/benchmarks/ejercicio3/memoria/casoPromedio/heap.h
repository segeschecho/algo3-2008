//=========== (C) Copyright 2006 Zonda-E. All rights reserved. ===========
//
// Purpose: $
//
// by Gonzalez Pablo
//========================================================================


#ifndef __HEAP_H__
#define __HEAP_H__

#include <ostream>

#define MM_MEMORY_ALIGNMENT		32


struct AllocHeader;

typedef unsigned int uint;

class Heap {
public:
	void Initialize();
	void* Allocate( size_t bytes );
	static void Deallocate( void *pMem );

	void Add( size_t bytes );
	void Remove( size_t bytes );

	bool IsActive() const;

	void Activate( const char *szHeapName );
	void Deactivate();

	const char* GetName() const;
	
	void AttachTo( Heap *pParent );

	static int GetMemoryBookmark();

	int ReportMemoryLeaks( uint bookmark_start, uint bookmark_end, std::ostream &os );
	void GetMemoryReport( std::ostream &os );

    size_t getPeak();

private:
	void Deallocate( AllocHeader *pHeader );
	void GetTreeStats( size_t &totalBytes, size_t &totalPeak, uint &totalInstances );
	void GetHierarchyStr( std::ostream &os, uint &lvl );

	enum { NAMELENGHT = 128 };

	char m_sName[NAMELENGHT];

	bool m_bActive;

	size_t	m_bytesAllocated;
	size_t	m_bytesPeak;
	int		m_dwNumInstances;

	Heap *m_pParent;

	Heap *m_pFirstChild;

	Heap *m_pNextSibling;
	Heap *m_pPrevSibling;

	AllocHeader *m_pHeadAlloc;

	static int s_dwNumCurAllocatedBlocks;
};

#endif