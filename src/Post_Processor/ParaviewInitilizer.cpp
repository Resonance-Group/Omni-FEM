/*
 * ParaviewInitilizer.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: phillip
 */
#include "Post_Processor/ParaviewInitilizer.h"

paraviewInitilizer::paraviewInitilizer()
{
	int argc = 0;
	char* argv[];

	QApplication::setApplicationName("Omni-FEM Post Processor");
	QApplication::setApplicationVersion("0.0.1");
	QApplication::setOrganizationName("Resonance Group");

	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	QApplication qApp(argc, argv);

	setlocale(LC_NUMERIC, "C");

	QLocale::setDefault(QLocale::c());

	initilizeParaviewWindow();
}


void paraviewInitilizer::initilizeParaviewWindow()
{
	int argc = 0;
	char* argv[];

	p_paraviewViewApp = new pqPVApplicationCore(argc, argv);
	// Create Main Window here

	/* This section is used in order to load
	 * any application specific plugins
	 */
	QString pluginString = "";

	QStringList pluginList = pluginString.split(';', QString::SkipEmptyParts);
	QString pluginXML = "<PLugins>";

	for(auto pluginName : pluginList)
	{
		pluginXML.append(QString("<Plugin name=\"%1\" auto_load=\"1\" />\n")).arg(pluginName);
	}
	pluginXML.append("</Plugins>\n");

	vtkPVPluginTracker::GetInstance()->LoadPluginConfigurationXMLFromString(
	    pluginXML.toLatin1().data());
}


paraviewInitilizer::~paraviewInitilizer()
{
	delete this->p_mainWindow;
	delete this->p_paraviewViewApp;
}



