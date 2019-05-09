#pragma once
#include <QObject>
#include "pluginhelp_global.h"
class QgsMapCanvas;
// Interface class for exposing functions in HympApp for use by plugins
class PLUGINHELP_EXPORT QAppPluginInterface : public QObject
{
public:
	QAppPluginInterface();
	virtual ~QAppPluginInterface();

	/** Return a pointer to the main window */
	virtual QWidget * mainWindow() = 0;

	/** Return a pointer to the map canvas */
	virtual QgsMapCanvas * mapCanvas() = 0;
};

