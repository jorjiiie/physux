#ifndef DEBUG_H
#define DEBUG_H
#include <stdexcept>

#define throw_if(condition, message)\
    if ((condition))\
        throw std::runtime_error(message)

#ifndef DEBUG_MODE
	#define ASSERT(cond, msg) 0
#else
#define ASSERT(cond, msg)\
	if (!(cond))\
	{std::cerr << "Assertion failed: (" << #cond << "), "\
      << "function " << __FUNCTION__\
      << ", file " << __FILE__\
      << ", line " << __LINE__ << "."\
      << std::endl << msg << std::endl, abort();}
#endif

#endif

