#pragma once

#ifdef __cplusplus
#define PLUGINEXPORT extern "C" EXPORT
#define PLUGINEXTERN extern "C"
#else
#define PLUGINEXPORT EXPORT
#define PLUGINEXTERN extern
#endif

// hack to workaround warnings when casting void pointers
// retrieved from QLibrary::resolve to function pointers.
// It's assumed that this works on all systems supporting
// QLibrary
#if QT_VERSION >= 0x050000
#define cast_to_fptr(f) f
#else
inline void(*cast_to_fptr(void *p))()
{
	union
	{
		void *p;
		void(*f)();
	} u;

	u.p = p;
	return u.f;
}
#endif
