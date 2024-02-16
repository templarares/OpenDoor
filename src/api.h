#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define OpenDoor_DLLIMPORT __declspec(dllimport)
#  define OpenDoor_DLLEXPORT __declspec(dllexport)
#  define OpenDoor_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define OpenDoor_DLLIMPORT __attribute__((visibility("default")))
#    define OpenDoor_DLLEXPORT __attribute__((visibility("default")))
#    define OpenDoor_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define OpenDoor_DLLIMPORT
#    define OpenDoor_DLLEXPORT
#    define OpenDoor_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef OpenDoor_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define OpenDoor_DLLAPI
#  define OpenDoor_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef OpenDoor_EXPORTS
#    define OpenDoor_DLLAPI OpenDoor_DLLEXPORT
#  else
#    define OpenDoor_DLLAPI OpenDoor_DLLIMPORT
#  endif // OpenDoor_EXPORTS
#  define OpenDoor_LOCAL OpenDoor_DLLLOCAL
#endif // OpenDoor_STATIC