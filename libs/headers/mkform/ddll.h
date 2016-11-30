#ifndef DDLL
#define DDLL

#include <QtGlobal>

#ifdef D_FORM_LIB
    #define D_FORM Q_DECL_EXPORT
#else
    #define D_FORM Q_DECL_IMPORT
#endif

#endif // DDLL

