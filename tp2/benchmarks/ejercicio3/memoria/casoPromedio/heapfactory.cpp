//=========== (C) Copyright 2006 Zonda-E. All rights reserved. ===========
//
// Purpose: $
//
// by Gonzalez Pablo
//========================================================================


#include "heapfactory.h"
#include "heap.h"

#include <assert.h>

#include <iomanip>

using namespace std;

Heap* HeapFactory::s_pRootHeap = NULL;
Heap* HeapFactory::s_pDefaultHeap = NULL;
Heap HeapFactory::s_Heaps[];

// Initialize the factory
void HeapFactory::Initialize()
{
	for( int i=0; i < MAXHEAPS; i++)
		s_Heaps[i].Initialize();

	s_pRootHeap = CreateNewHeap( "Root" );
	s_pDefaultHeap = CreateHeap( "Default", "Root" );
}


// Create a new heap using Root as PARENT
Heap* HeapFactory::CreateHeap( const char *pszHeapName )
{
	return CreateHeap( pszHeapName, "Root" );
}


// Create a new heap
Heap* HeapFactory::CreateHeap( const char *szHeapName, const char *szParentHeapName )
{
	assert( szHeapName != NULL );
	assert( szParentHeapName != NULL );

	if( s_pRootHeap == NULL )
		Initialize();

	Heap *pParent = FindHeap( szParentHeapName );
	if( !pParent )
	{
		// if the parent heap does not exist, create a new one
		// and attach it to the Root Heap
		pParent = CreateNewHeap( szParentHeapName );
		pParent->AttachTo( s_pRootHeap );
	}

	Heap *pHeap = FindHeap( szHeapName );
	if( !pHeap )
	{
		// if the heap does not exist, create a new one
		pHeap = CreateNewHeap( szHeapName );
	}

	pHeap->AttachTo( pParent );
	return pHeap;
}


Heap* HeapFactory::GetRootHeap()
{
	if( s_pRootHeap == NULL )
		Initialize();

	return s_pRootHeap;
}


Heap* HeapFactory::GetDefaultHeap()
{
	if( s_pDefaultHeap == NULL )
		Initialize();

	return s_pDefaultHeap;
}


Heap* HeapFactory::CreateNewHeap( const char *szHeapName )
{
	for( int i=0; i < MAXHEAPS; i++)
	{
		if( !s_Heaps[i].IsActive() )
		{
			Heap *pHeap = &s_Heaps[i];
			pHeap->Activate( szHeapName );
			return pHeap;
		}
	}

	return NULL;
}


Heap* HeapFactory::FindHeap( const char *szHeapName )
{
	if( szHeapName == NULL )
		return NULL;

	for( int i=0; i < MAXHEAPS; i++ )
	{
		Heap *pHeap = &s_Heaps[i];

		if( pHeap->IsActive() && !strcmp( szHeapName, pHeap->GetName() ) )
				return pHeap;
	}

	return NULL;
}

int HeapFactory::GetMemoryBookmark()
{
	return Heap::GetMemoryBookmark();
}


void HeapFactory::ReportMemoryLeaks( int bookmark, std::ostream &os )
{
	HeapFactory::ReportMemoryLeaks( bookmark, Heap::GetMemoryBookmark(), os );
}


void HeapFactory::ReportMemoryLeaks(int bookmark_start, int bookmark_end, std::ostream &os )
{
	int leaks = 0;

	for( int i=0; i < MAXHEAPS; i++ )
	{
		if( s_Heaps[i].IsActive() )
			leaks += s_Heaps[i].ReportMemoryLeaks( bookmark_start, bookmark_end, os );
	}

	if( leaks > 0 )
		os << "Memory leaks found: " << leaks << std::endl;
	else
		os << "No memory leaks were found." << std::endl;
}

void HeapFactory::GetMemoryReport( std::ostream &os )
{
	os.fill(' ');
	os << "MEMORY INFORMATION" << endl <<
			setw(42) << "Local" << setw(26) << "Total" << endl <<
			"Name" << setw(30) << "Memory" << setw(11) << "Peak" << setw(6) << "Inst" << setw(10) << "Memory" << setw(11) << "Peak" << setw(6) << "Inst" << endl;

	HeapFactory::GetRootHeap()->GetMemoryReport( os );
}