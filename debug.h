#ifndef __DEBUG__H__
#define __DEBUG__H__


#ifdef DEBUGALL
#define myPrintf(m) {printf("%s %d :", __FUNCTION__, __LINE__); printf m;}
#else
#define myPrintf(m) 
#endif

#endif
