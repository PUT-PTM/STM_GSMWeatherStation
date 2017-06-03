#ifndef TM_ATTRIBUTES_H
#define TM_ATTRIBUTES_H

#if defined (__GNUC__)
	#ifndef __weak		
		#define __weak   	__attribute__((weak))
	#endif
	#ifndef __packed	
		#define __packed 	__attribute__((__packed__))
	#endif
#endif

#endif
