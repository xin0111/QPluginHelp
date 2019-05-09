#include "pluginhelp.h"

#include "pluginhelpmetadata.h"


QPluginHelpMetadata::QPluginHelpMetadata(const QString& _libraryPath,
	const QString& _name,
	QPluginHelp * _plugin)
	: m_name(_name)
	, libraryPath(_libraryPath)
	, m_plugin(_plugin)
{

}

QString QPluginHelpMetadata::name() const
{
	return m_name;
}

QString QPluginHelpMetadata::library() const
{
	return libraryPath;
}

QPluginHelp *QPluginHelpMetadata::plugin()
{
	return m_plugin;
}
