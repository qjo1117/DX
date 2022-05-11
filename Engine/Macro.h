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

/* ------------------------------
			Property
------------------------------ */

#define PROPERTY(_get, _set) _declspec(property(get = _get, put = _set))
#define G_PROPERTY(_get) _declspec(property(get = _get))
#define S_PROPERTY(_set) _declspec(property(set = _set))

#define SETMEMBER(type, member)		void Set##member(const type& p_val) { m_##member = p_val; }     
#define GETMEMBER(type, member)		const type& Get##member() { return m_##member; }

/* ----- 김치삼 교수님께서 알려주신 PROPERTY ----- */
#define PUBLIC_PROPERTY(type, member)								\
public:                                                             \
type m_##member;                                                    \
public:                                                             \
	SETMEMBER(type, member)											\
	GETMEMBER(type, member)											\
	PROPERTY(Get##member,  Set##member) type& ##member;

#define PRIVATE_PROPERTY(type, member)								\
private:                                                            \
type m_##member;                                                    \
public:                                                             \
	SETMEMBER(type, member)											\
	GETMEMBER(type, member)											\
	PROPERTY(Get##member,  Set##member) type& ##member;

#define PROTECTED_PROPERTY(type, member)							\
protected:                                                          \
type m_##member;                                                    \
public:                                                             \
	SETMEMBER(type, member)											\
	GETMEMBER(type, member)											\
	PROPERTY(Get##member,  Set##member) type& ##member;

/* ------------------------------------------------------------
	어쩌다보니 Attribute찾다가 property에 대해서 흥미가 돋아서
	알고 있는 코드와 조합을 시켜서 만들어 보았습니다.
	https://blog.naver.com/kyuniitale/40029470165	
	_declspec(property(get = _get, put = _set)) 참고 자료 ▲
------------------------------------------------------------ */