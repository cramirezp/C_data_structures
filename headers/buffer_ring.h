/********************************************************************
 *
 * FIFO queue data structure
 *
 * Implemeneted with a array as a buffer ring
 *
 * Need to call:
 *		-declare_bring(some name, type to store) -> declares type
 *		-init_bring(same name) -> buffer ring header and array to 0
 * Can
 *		-push value of vtype to the buffer ring if name at end
 *		-pull value from name and update buffer ring's header
 *		-loop values from first to last
 *
 *
 * It's stupid to implement remove() (would require to copy from
 * first to position or from end to position) or
 * getNextValue/previousValue cause is the same as looping values
 * with foreach_bring() and equals the value.
 *
 *******************************************************************/
#ifndef _buffer_ring_h
#define _buffer_ring_h

#include "stdint.h"
#include "string.h"

/*
	first, last are never negative => first or last < _BR_BUFFER_SIZE its not a problem
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

#define foreach_bring(name, vtype, it) 								\
	int i_;															\
	vtype it;														\
	for(i_=name.first, it=name.buffer[name.first]; i_!=name.last; i_=(i_+1>=_BR_BUFFER_SIZE)? 0: i_+1, it=name.buffer[i_])


#endif // _buffer_ring_h

