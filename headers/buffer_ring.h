#ifndef _buffer_ring_h
#define _buffer_ring_h

#include "stdint.h"
#include "string.h"

#define _BR_BUFFER_SIZE 100

#define declare_bring(vtype, name) \
	(struct _bf_t 						\
	{									\
		vtype buffer[_BR_BUFFER_SIZE];	\
		uint16_t first, last;			\
	}name)

#define init_bring(vtype, name) \
	{																	\
		name.first = 0;													\
		name.last   = 0;												\
		memset((void*)&name.buffer, 0, sizeof(vtpye)*_BR_BUFFER_SIZE)	\
	}

#define push_bring(vtype, name, value) \
		{																\
			name.buffer[name.last++] = value;							\
			name.last = (name.last < _BR_BUFFER_SIZE)? name.last: 0;	\
		}
#define pull_bring(vtype, name) \
		(																\
			name.buffer[name.first++],									\
			name.first = (name.first < _BR_BUFFER_SIZE)? name.first: 0	\
		)


#endif // _buffer_ring_h