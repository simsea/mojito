/**
 * (c) 2013 Andrew Payne. All rights reserved.
 */
#ifndef _MOJITO_LIFECYCLE_H_
#define _MOJITO_LIFECYCLE_H_

namespace mojito
{
	/**
	 * Entity Lifecycle
	 */
	typedef enum
	{
		Lifecycle_Created,
		Lifecycle_Enabled,
		Lifecycle_Disabled,
		Lifecycle_Destroyed
	} Lifecycle;
}

#endif
