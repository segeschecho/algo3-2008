//=========== (C) Copyright 2006 Zonda-E. All rights reserved. ===========
//
// Purpose: memory management
//
// by Gonzalez Pablo
//========================================================================


#include "memorymgr.h"
#include "heap.h"

#include <assert.h>

void* operator new( size_t size )
{
	return operator new( size, HeapFactory::GetDefaultHeap() );
}


void* operator new( size_t size, Heap *pHeap )
{
	assert( pHeap != NULL );
	return pHeap->Allocate( size);
}


void operator delete( void *pMem )
{
	if( pMem != NULL )
		Heap::Deallocate( pMem );
}


void* operator new[]( size_t size )
{
	return operator new[]( size, HeapFactory::GetDefaultHeap() );
}


void* operator new[]( size_t size, Heap *pHeap )
{
	assert( pHeap != NULL );
	return pHeap->Allocate( size);
}


void operator delete[]( void *pMem )
{
	if( pMem != NULL )
		Heap::Deallocate( pMem );
}
