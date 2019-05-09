#pragma once
#include <QString>
#include "pluginhelp_global.h"

class QPluginHelp;
class PLUGINHELP_EXPORT QPluginHelpMetadata
{
public:
	QPluginHelpMetadata(const QString& _libraryPath, const QString& _name, QPluginHelp *_plugin);
	QString name() const;
	QString library() const;
	QPluginHelp *plugin();
private:
	QString m_name;
	QString libraryPath;
	QPluginHelp *m_plugin;
};

