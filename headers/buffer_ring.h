#ifndef _buffer_ring_h
#define _buffer_ring_h

#include "stdint.h"
#include "string.h"

#define _BR_BUFFER_SIZE 100

#define declare_bring(vtype, name) \
	typedef struct						\
	{									\
		vtype buffer[_BR_BUFFER_SIZE];	\
		uint16_t first, last;			\
		uint8_t	size;					\
	}_bf_t;								\
	_bf_t name


#define init_bring(name) \
	{																		\
		name.first = 0;														\
		name.last  = 0;														\
		name.size  = 0;														\
		memset((void*)&name.buffer, 0, sizeof(name.buffer)*_BR_BUFFER_SIZE);\
	}

#define push_bring(vtype, name, value) \
		{																\
			name.buffer[name.last++] = value;							\
			name.last = (name.last < _BR_BUFFER_SIZE)? name.last: 0;	\
			name.size++;												\
		}
#define pull_bring(vtype, name) \
		(																\
			name.buffer[name.first++],									\
			name.first = (name.first < _BR_BUFFER_SIZE)? name.first: 0,	\
			name.size = (name.size != 0)? name.size-1: 0				\
		)
/*
#define foreach(vtype, name, it) \
		int i_;						\
		vtype it;					\
		for(i_=name.first, it=name.buffer[name.first]; i_-1!=name.last; i_=(i_+1>=_BR_BUFFER_SIZE)? 0: i_+1, it=name.buffer[i_])
*/
#define foreach(vtype, name) \
	int i_;					\
	for(i_=name.first; i_-1!=name.last; i_=(i_+1>=_BR_BUFFER_SIZE)? 0: i_+1)

#endif // _buffer_ring_h