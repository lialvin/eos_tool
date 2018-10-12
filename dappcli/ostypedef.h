#ifndef _HEAD_OSTYPEDEF_3A24AE1F_5485D62D_32D4B53D_H
#define _HEAD_OSTYPEDEF_3A24AE1F_5485D62D_32D4B53D_H


/* NOTE:
 * The corresponding system header files must be included is prerequisite
 * to make this file function correct.
 */

#if !defined(TRUE)
#define TRUE   1
#endif

#if !defined(FALSE)
#define FALSE  0
#endif

#if !defined(MAX_PATH)
#define MAX_PATH PATH_MAX
#endif

#ifndef mplat_max
#define mplat_max(a, b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef mplat_min
#define mplat_min(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#define LINUX_FILENAME_SEPERATOR       '/'
#define LINUX_FILENAME_SEPERATOR_STR   "/"
#define WIN_FILENAME_SEPERATOR	       '\\'
#define WIN_FILENAME_SEPERATOR_STR     "\\"

#define LINUX_LIB_FILE_SUFFIX_STR		".so"
#define WIN_LIB_FILE_SUFFIX_STR			".dll"


/*
 * Sizes for buffers used by the _makepath() and _splitpath() functions.
 * note that the sizes include space for 0-terminator
 */

/* These typedefs may or may not be defined even under Windows. It
 * depends on the macro BASETYPES.
 */

#if !defined(BASETYPES)
#define BASETYPES
#endif

#if !defined(OS_LINUX)
typedef int BOOL;
#endif



#if !defined(OS_WINDOWS)
typedef long long           LONGLONG;
typedef unsigned long long  ULONGLONG,DDWORD;

#define MAXDWORD    0xffffffff

#else

typedef __int64             LONGLONG;
typedef unsigned __int64    ULONGLONG, DDWORD;
typedef LONGLONG            off64_t;
typedef LONGLONG            loff_t;

#endif


#if !defined(OS_WINDOWS)

/* These typedefs are all predefined under Windows. We'd better
 * make a copy of them for other operating systems.
 */

typedef char   CHAR;
typedef short  SHORT;
typedef int    INT;
typedef long   LONG;
typedef long long  LLONG;

typedef unsigned char  BYTE, UBYTE;
typedef unsigned short WORD, UWORD;
typedef unsigned long  DWORD, UDWORD;
typedef unsigned long long  ULLONG;
typedef signed char    UINT8;
typedef signed char    SBYTE;
typedef signed short   SWORD;
typedef signed long    SDWORD;

typedef unsigned int   UINT;
typedef unsigned int   UINT32;
typedef unsigned int  *PUINT;

typedef float   FLOAT, *PFLOAT;

typedef void    VOID, *PVOID;

typedef int     BOOL;


typedef char        *LPSTR;
typedef const char  *LPCTSTR;
typedef const char  *LPCSTR;


/* Types used for passing & returning polymorphic values */
typedef long           INT_PTR,  *PINT_PTR;
typedef unsigned long  UINT_PTR, *PUINT_PTR;
typedef long           LONG_PTR, *PLONG_PTR;

typedef UINT_PTR  WPARAM;
typedef LONG_PTR  LPARAM;
typedef LONG_PTR  LRESULT;


#define HFILE_ERROR ((HFILE)-1)

#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD)(a) & 0xff)) | ((WORD)((BYTE)((DWORD)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD)(w) >> 8))

#define MAKEWPARAM(l, h)      (WPARAM)MAKELONG(l, h)
#define MAKELPARAM(l, h)      (LPARAM)MAKELONG(l, h)
#define MAKELRESULT(l, h)     (LRESULT)MAKELONG(l, h)

#endif


#if defined(OS_WINDOWS)
#define _MAX_ULONGLONG  0xffffffffffffffff
#define _MIN_ULONGLONG  0x0
#else
#define _MAX_ULONGLONG  0xffffffffffffffffull
#define _MIN_ULONGLONG  0x0ull
#endif
#define _MAX_DWORD      0xffffffff
#define _MIN_DWORD      0x0
#define _MAX_WORD	0xffff
#define _MIN_WORD	0x0
#define _MAX_SHORT	0x7fff
#define _MIN_SHORT	(-0x7fff)
#define _MAX_LONG       0x7fffffff
#define _MIN_LONG       (-0x7fffffff)
#define _MAX_INT        0x7fffffff
#define _MIN_INT        (-0x7fffffff)

#endif /* #ifndef _HEAD_OSTYPEDEF_3A24AE1F_5485D62D_32D4B53D_H */
