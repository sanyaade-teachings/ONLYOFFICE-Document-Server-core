#ifndef _ZLIB_H
#define _ZLIB_H

#ifndef ZLIB_USE_DYNAMIC_LIBRARY
#define ZLIB_DECL_EXPORT
#else
#include "../../../../DesktopEditor/common/base_export.h"
#define ZLIB_DECL_EXPORT Q_DECL_EXPORT
#endif

#include <malloc.h>
#include <string>

#include "../../../DesktopEditor/common/ZipLib.h"

#ifdef __cplusplus
extern "C" {
#endif

ZLIB_DECL_EXPORT void* Zlib_Malloc(unsigned int size);
ZLIB_DECL_EXPORT void  Zlib_Free(void* p);

ZLIB_DECL_EXPORT CZLib* Zlib_Create();
ZLIB_DECL_EXPORT CZLib* Zlib_Load(unsigned char* buffer, unsigned long size);
ZLIB_DECL_EXPORT void  Zlib_Destroy(CZLib* p);

ZLIB_DECL_EXPORT unsigned char* Zlib_GetPathsInArchive(CZLib* p);
ZLIB_DECL_EXPORT unsigned char* Zlib_GetFileFromArchive(CZLib* p, const char* path);
ZLIB_DECL_EXPORT unsigned char* Zlib_CompressFiles(CZLib* p,   unsigned char* tree);

#ifdef __cplusplus
}
#endif

#endif // _ZLIB_H
