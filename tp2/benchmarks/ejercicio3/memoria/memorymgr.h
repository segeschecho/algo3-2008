//=========== (C) Copyright 2006 Zonda-E. All rights reserved. ===========
//
// Purpose: $
//
// by Gonzalez Pablo
//========================================================================


#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__

#include "heapfactory.h"
#include "memorypool.h"

class Heap;

void* operator new( size_t size );
void* operator new( size_t size, Heap* pHeap );
void  operator delete( void* pMem, size_t size );

void* operator new[]( size_t size );
void* operator new[]( size_t size, Heap* pHeap );
void  operator delete[]( void* pMem, size_t size );


#define DECLARE_HEAP \
		public: \
			static void* operator new( size_t bytes ); \
			static void* operator new[]( size_t bytes ); \
			static void operator delete( void *pMem, size_t bytes ); \
			static void operator delete[]( void *pMem, size_t bytes ); \
		private: \
			static Heap * s_pHeap;


#define DEFINE_HEAP( className, heapName, parentHeapName ) \
		Heap *className::s_pHeap = NULL; \
		void* className::operator new( size_t bytes ) { \
			if( s_pHeap == NULL ) { \
				if( parentHeapName == NULL ) \
					s_pHeap = HeapFactory::CreateHeap( heapName ); \
				else \
					s_pHeap = HeapFactory::CreateHeap( heapName, parentHeapName ); \
			} \
			return ::operator new( bytes, s_pHeap ); \
		} \
		void* className::operator new[]( size_t bytes ) { \
			if( s_pHeap == NULL ) { \
				if( parentHeapName == NULL ) \
					s_pHeap = HeapFactory::CreateHeap( heapName ); \
				else \
					s_pHeap = HeapFactory::CreateHeap( heapName, parentHeapName ); \
			} \
			return ::operator new[]( bytes, s_pHeap ); \
		} \
		void className::operator delete( void *pMem, size_t size ) { \
			::operator delete( pMem ); \
		} \
		void className::operator delete[]( void *pMem, size_t size ) { \
			::operator delete[]( pMem ); \
		}


#define DECLARE_MEMPOOL( classname, heapname ) \
	private: \
		static MemoryPool *s_pPool; \
	public: \
		inline static void *operator new( size_t size ) { \
			if( s_pPool == NULL ) \
			{ \
				static MemoryPool p( sizeof(classname), heapname ); \
				s_pPool = &p; \
			} \
			return s_pPool->Alloc( size ); \
		} \
		inline static void operator delete( void *pMem, size_t size ) { \
			s_pPool->Free( pMem, size ); \
		} \
		static void ClearPool() { s_pPool->Clear(); }

#define DEFINE_MEMPOOL( classname ) \
	MemoryPool * classname::s_pPool;

#endif