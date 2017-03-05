#include "pch.h"

#ifdef LUABIND_NO_EXCEPTIONS
	void boost::throw_exception(const std::exception &){}
#endif // LUABIND_NO_EXCEPTIONS