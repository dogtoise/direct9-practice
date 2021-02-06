#pragma once
#ifndef __ENGINE_DEFINE_H__

#ifdef EXPORTS_ENGINE
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#define NO_COPY(ClassName)							\
private:											\
	ClassName(const ClassName&) = delete;			\
	ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static ClassName* Get_Instasnce();		\
	static void Destroy_Instance();			\
private:									\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)				\
ClassName* ClassName::m_pInstance = nullptr;		\
ClassName* ClassName::Get_Instasnce()				\
{													\
	if (nullptr == m_pInstance)						\
	{												\
		m_pInstance = new ClassName;				\
	}												\
	return m_pInstance;								\
}													\
void ClassName::Destroy_Instance()					\
{													\
	if (m_pInstance)								\
	{												\
		delete m_pInstance;							\
		m_pInstance = nullptr;						\
	}												\
}

#define __ENGINE_DEFINE_H__
#endif

