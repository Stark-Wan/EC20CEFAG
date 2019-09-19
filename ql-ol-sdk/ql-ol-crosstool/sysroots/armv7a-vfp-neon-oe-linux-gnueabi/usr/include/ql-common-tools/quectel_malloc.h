/**
 * @file quectel_malloc.h
 * @brief Quectel malloc common functions.
 *
 * @note
 */
/*=============================================================================
  Copyright (c) 2018 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
=============================================================================*/

/*============================================================================

                          EDIT HISTORY FOR MODULE
  
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
  
  WHEN             WHO         WHAT, WHERE, WHY
  ------------     -------     ----------------------------------------
  07/17/2018       Mike        Adds string.h header file.
============================================================================*/

#ifndef __QUECTEL_MALLOC_H__
#define __QUECTEL_MALLOC_H__

#include <string.h>

static inline void *quectel_malloc(size_t size)
{
	void *ptr;
	
	if(size <= 0) {
		return NULL;
	}

	ptr = malloc(size);
	if(ptr) {
		memset(ptr, 0, size);
	}
	return ptr;
}

static inline void _quectel_free(void **ptr)
{
	if(NULL != ptr && NULL != (*ptr)) {
		free(*ptr);
		*ptr = NULL;
	}
}
#define quectel_free(ptr) _quectel_free((void **)(ptr))

#endif
