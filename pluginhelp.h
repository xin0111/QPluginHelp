#pragma once
#include <QString>
/*
* In addition, a plugin must implement the classFactory and unload
* functions.Note that these functions must be declared as extern "C" in
* order to be resolved properly and prevent C++ name mangling.
*/

class QPluginHelp
{
public:
	QPluginHelp(QString const & name = "",
		QString const & description = "",
		QString const & version = "")
		: mName(name)
		, mDescription(description)		
		, mVersion(version)		
	{}

	virtual ~QPluginHelp()
	{}

	//! Get the name of the plugin
	QString const & name() const
	{
		return mName;
	}

	QString  & name()
	{
		return mName;
	}

	//! Version of the plugin
	QString const & version() const
	{
		return mVersion;
	}

	//! Version of the plugin
	QString & version()
	{
		return mVersion;
	}

	//! A brief description of the plugin
	QString const & description() const
	{
		return mDescription;
	}

	//! A brief description of the plugin
	QString       & description()
	{
		return mDescription;
	}

	/// function to initialize connection to GUI
	virtual void initGui() = 0;

	//! Unload the plugin and cleanup the GUI
	virtual void unload() = 0;

private:
	/// plug-in name
	QString mName;

	/// description
	QString mDescription;

	/// version
	QString mVersion;
};



