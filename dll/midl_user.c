
#include <stdlib.h>

void* __cdecl MIDL_user_allocate(size_t sz)
{
	return malloc(sz);
}

void __cdecl MIDL_user_free(void* ptr)
{
	free(ptr);
}
