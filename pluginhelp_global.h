#ifndef QCODECONTROL_GLOBAL_H
#define QCODECONTROL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PLUGINHELP_EXPORTS
# define PLUGINHELP_EXPORT Q_DECL_EXPORT
#else
# define PLUGINHELP_EXPORT Q_DECL_IMPORT
#endif

#endif // QCODECONTROL_GLOBAL_H