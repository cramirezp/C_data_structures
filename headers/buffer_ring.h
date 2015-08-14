#ifndef _buffer_ring_h
#define _buffer_ring_h

#include "stdint.h"
#include "string.h"

/*
	first, last are never negative => first/last < _BR_BUFFER_SIZE its not a problem
*/

#define _BR_BUFFER_SIZE 100

#define declare_bring(name, vtype) 									\
	typedef struct													\
	{																\
		vtype buffer[_BR_BUFFER_SIZE];								\
		uint16_t first, last;										\
		uint8_t	size;												\
	}_bf_t;															\
	_bf_t name


#define init_bring(name) 											\
	{																\
		name.first = 0;												\
		name.last  = 0;												\
		name.size  = 0;												\
		memset((void*)&name.buffer, 0, sizeof(*name.buffer)*_BR_BUFFER_SIZE);\
	}
	
#define push_bring(name, vtype, value) 								\
	{																\
		name.buffer[name.last] = value;								\
		name.last = (name.last+1 < _BR_BUFFER_SIZE)? name.last+1: 0;\
		name.size++;												\
	}
#define pull_bring(name) 											\
	(name.first+1>=_BR_BUFFER_SIZE)?								\
	(((name.first = 0) ==0)? ((name.size--)? name.buffer[_BR_BUFFER_SIZE-1]: name.buffer[_BR_BUFFER_SIZE-1]):	\
							((name.size--)? name.buffer[_BR_BUFFER_SIZE-1]: name.buffer[_BR_BUFFER_SIZE-1]) ):	\
	((name.size--)? name.buffer[name.first++]: name.buffer[name.first++])

#define foreach(name, vtype, it) 									\
	int i_;															\
	vtype it;														\
	for(i_=name.first, it=name.buffer[name.first]; i_!=name.last; i_=(i_+1>=_BR_BUFFER_SIZE)? 0: i_+1, it=name.buffer[i_])

#endif // _buffer_ring_h

