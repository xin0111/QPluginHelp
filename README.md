
##### qt 插件调用库
- testplugin.h
```` c++
#pragma once
#include <QObject>
#include "pluginhelp.h"

class QAppPluginInterface;

class TestPlugin : public QObject, public QPluginHelp
{
	Q_OBJECT
public:
	explicit TestPlugin(QAppPluginInterface* iface);
	void initGui() override;
	void unload() override;
private:
	QAppPluginInterface* mIface;
};

````
- testplugin.cpp
```` c++
#include "testplugin.h"
#include "pluginhelp.h"
#include "pluginhelpdefs.h"
#include "appplugininterface.h"

static const QString sName = "TestPlugin";
static const QString sDescription = "Test Pluginhelp";
static const QString sPluginVersion = "Version 0.1";


TestPlugin::TestPlugin(QAppPluginInterface* iface)
: QPluginHelp( sName, sDescription, sPluginVersion ),
mIface(iface)
{

}

void TestPlugin::initGui()
{
	//todo something...
}

void TestPlugin::unload()
{

}

/**
* Required extern functions needed  for every plugin
* These functions can be called prior to creating an instance
* of the plugin class
*/
// Class factory to return a new instance of the plugin class

PLUGINEXTERN Q_DECL_EXPORT  QPluginHelp * classFactory(QAppPluginInterface * theInterfacePointer)
{
	return new TestPlugin(theInterfacePointer);
}

// Return the name of the plugin - note that we do not user class members as
// the class may not yet be insantiated when this method is called.
PLUGINEXTERN Q_DECL_EXPORT QString name()
{
	return sName;
}

// Return the description
PLUGINEXTERN Q_DECL_EXPORT QString description()
{
	return sDescription;
}

// Return the version number for the plugin
PLUGINEXTERN Q_DECL_EXPORT QString version()
{
	return sPluginVersion;
}

// Delete ourself
PLUGINEXTERN Q_DECL_EXPORT void unload(QPluginHelp * thePluginPointer)
{
	delete thePluginPointer;
}

````

- main.cpp
````c++
    // 复写 QAppPluginInterface 
    QAppPluginInterface* iface = ....;
    QPluginHelpRegistry::instance()->setHympInterface(iface);
    QString pluginsPath = "插件路径";
    QPluginHelpRegistry::instance()->install(pluginsPath);
````