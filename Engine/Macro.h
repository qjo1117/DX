#pragma once


/* -------- Simple SingleTon -------- */

#define DECLARE_SINGLE(type) 				\
private:									\
	type() {}								\
	~type() {}								\
public:										\
static type* GetI()							\
{											\
	static type instance;					\
	return &instance;						\
}											\


#define GET_SINGLE(type)		type::GetI()

/*---------------
	  Crash
---------------*/

#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

#define ASSERT_CRASH(expr)			\
{									\
	if (!(expr))					\
	{								\
		CRASH("ASSERT_CRASH");		\
		__analysis_assume(expr);	\
	}								\
}