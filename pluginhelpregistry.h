#pragma 
#include <QMap>
#include "pluginhelpmetadata.h"
#include "Singleton.h"
#include "pluginhelp_global.h"

class QAppPluginInterface;
class QString;
class QPluginHelp;

class PLUGINHELP_EXPORT QPluginHelpRegistry :public Singleton<QPluginHelpRegistry>
{
public:

	//! set pointer to  interface passed to plugins 
	void setHympInterface(QAppPluginInterface* iface);

	// after setHympInterface 
	void install(const QString& pluginPath);

	//! Check whether this module is loaded
	bool isLoaded(const QString& key) const;

	//! Retrieve a pointer to a loaded plugin
	QPluginHelp * plugin(const QString& key);

protected:
	//! Add a plugin to the map of loaded plugins
	void addPlugin(const QString& key, const QPluginHelpMetadata& metadata);

	//! Remove a plugin from the list of loaded plugins
	void removePlugin(const QString& key);

	//! Unload plugins
	void unloadAll();

	//! C++ plugin loader
	void loadCppPlugin(const QString& theFullPathName);

	//! C++ plugin unloader
	void unloadCppPlugin(const QString& theFullPathName);

public:
	QPluginHelpRegistry();
private:
	QMap<QString, QPluginHelpMetadata> mPlugins;
	QAppPluginInterface* mHympInterface;
};

