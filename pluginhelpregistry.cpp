#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QLibrary>
#include <QMessageBox>
#include <QMainWindow>

#include "pluginhelpregistry.h"
#include "pluginhelp.h"
#include "appplugininterface.h"
#include "pluginhelpdefs.h"


/* typedefs for plugins */
typedef QPluginHelp *create_ui(QAppPluginInterface * qI);
typedef QString name_t();
typedef QString description_t();
typedef QString category_t();
typedef int type_t();

QPluginHelpRegistry::QPluginHelpRegistry() 
: mHympInterface(nullptr)
{

}

void QPluginHelpRegistry::setHympInterface(QAppPluginInterface* iface)
{
	mHympInterface = iface;
}


void QPluginHelpRegistry::install(const QString& pluginPath)
{
	QDir dir(pluginPath);
	if (dir.exists()){
		QStringList plugins = dir.entryList(QStringList() << "*.dll", QDir::Files);
		foreach(QString strLibpath, plugins){
			loadCppPlugin(pluginPath +"/"+ strLibpath);
		}
	}
}

bool QPluginHelpRegistry::isLoaded(const QString& key) const
{
	QMap<QString, QPluginHelpMetadata>::const_iterator it = mPlugins.find(key);
	if (it != mPlugins.end()) // found a c++ plugin
		return true;

	return false;
}

QPluginHelp * QPluginHelpRegistry::plugin(const QString& key)
{
	QMap<QString, QPluginHelpMetadata>::iterator it = mPlugins.find(key);
	if (it == mPlugins.end())
		return nullptr;

	return it->plugin();
}

void QPluginHelpRegistry::addPlugin(const QString& key, const QPluginHelpMetadata& metadata)
{
	mPlugins.insert(key, metadata);
}

void QPluginHelpRegistry::removePlugin(const QString& key)
{
	qDebug()<< ("removing plugin: " + key);
	QMap<QString, QPluginHelpMetadata>::iterator it = mPlugins.find(key);
	if (it != mPlugins.end())
	{
		mPlugins.erase(it);
	}

}

void QPluginHelpRegistry::unloadAll()
{
	for (QMap<QString, QPluginHelpMetadata>::iterator it = mPlugins.begin();
		it != mPlugins.end();
		++it)
	{
		if (it->plugin())
		{
			it->plugin()->unload();
		}
		else
		{
			qDebug() << ("warning: plugin is NULL:" + it.key());
		}
	}
}

void QPluginHelpRegistry::loadCppPlugin(const QString& theFullPathName)
{
	QString baseName = QFileInfo(theFullPathName).baseName();

	// first check to see if its already loaded
	if (isLoaded(baseName))
	{
		// plugin is loaded
		// QMessageBox::warning(this, "Already Loaded", description + " is already loaded");
		return;
	}

	QLibrary myLib(theFullPathName);

	QString myError; //we will only show detailed diagnostics if something went wrong
	myError += QObject::tr("Library name is %1\n").arg(myLib.fileName());

	bool loaded = myLib.load();
	if (!loaded)
	{
		qDebug() << (QObject::tr("Failed to load %1 (Reason: %2)").arg(myLib.fileName(), myLib.errorString()), QObject::tr("Plugins"));
		return;
	}

	myError += QObject::tr("Attempting to resolve the classFactory function\n");

	name_t *pName = (name_t *)cast_to_fptr(myLib.resolve("name"));

	// UI only -- doesn't use mapcanvas
	create_ui *cf = (create_ui *)cast_to_fptr(myLib.resolve("classFactory"));

	if (cf)
	{
		QPluginHelp *pl = cf(mHympInterface);
		if (pl)
		{
			pl->initGui();
			// add it to the plugin registry
			addPlugin(baseName, QPluginHelpMetadata(myLib.fileName(), pName(), pl));

			QObject *o = dynamic_cast<QObject *>(pl);
			if (o)
			{
				if (o->objectName().isEmpty())
				{
#ifndef Q_OS_WIN
					baseName = baseName.mid(3);
#endif
					o->setObjectName(QString("hymp_plugin_%1").arg(baseName));				
				}

				if (!o->parent())
				{
					qDebug() << (QString("setting plugin parent"));
					o->setParent((QMainWindow*)(mHympInterface->mainWindow()));
				}
				else
				{
					qDebug() << (QString("plugin parent already set"));
				}
			}
		}
		else
		{
			// something went wrong
			QMessageBox::warning(mHympInterface->mainWindow(), QObject::tr("Error Loading Plugin"),
				QObject::tr("There was an error loading a plugin."
				"The following diagnostic information may help the QGIS developers resolve the issue:\n%1.")
				.arg(myError));
		}
	}
	else
	{
		qDebug()<< (QObject::tr("Unable to find the class factory for %1.").arg(theFullPathName), QObject::tr("Plugins"));
	}

}

void QPluginHelpRegistry::unloadCppPlugin(const QString& theFullPathName)
{
	QString baseName = QFileInfo(theFullPathName).baseName();
	if (isLoaded(baseName))
	{
		QPluginHelp * pluginInstance = plugin(baseName);
		if (pluginInstance)
		{
			pluginInstance->unload();
		}
		// remove the plugin from the registry
		removePlugin(baseName);
		qDebug()<< ("Cpp plugin successfully unloaded: " + baseName);
	}
}

