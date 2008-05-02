//=========== (C) Copyright 2006 Zonda-E. All rights reserved. ===========
//
// Purpose: $
//
// by Gonzalez Pablo
//========================================================================


#ifndef __HEAP_FACTORY_H__
#define __HEAP_FACTORY_H__

#include <ostream>

class Heap;

class HeapFactory {
public:
	static Heap* CreateHeap( const char *szHeapName );
	static Heap* CreateHeap( const char *szHeapName, const char *szParentHeapName );

	static Heap* GetDefaultHeap();

	static int GetMemoryBookmark();
	static void ReportMemoryLeaks( int bookmark, std::ostream &os );
	static void ReportMemoryLeaks( int bookmark_start, int bookmark_end, std::ostream &os );

	static void GetMemoryReport( std::ostream &os );

private:
	static void Initialize();
	static Heap* GetRootHeap();
	static Heap* CreateNewHeap( const char *szHeapName );
	static Heap* FindHeap( const char *szHeapName );

	enum { MAXHEAPS = 512 };

	static Heap s_Heaps[MAXHEAPS];

	static Heap* s_pRootHeap;
	static Heap* s_pDefaultHeap;
};

#endif