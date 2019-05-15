#pragma once

#ifndef PLUGINEXTERN
#ifdef Q_OS_WIN
#  define PLUGINEXTERN extern "C" __declspec( dllexport )
#  ifdef _MSC_VER
// do not warn about C bindings returing QString
#    pragma warning(disable:4190)
#  endif
#else
#  if defined(__GNUC__) || defined(__clang__)
#    define PLUGINEXTERN extern "C" __attribute__ ((visibility ("default")))
#  else
#    define PLUGINEXTERN extern "C"
#  endif
#endif
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