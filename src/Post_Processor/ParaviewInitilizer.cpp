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
	char* argv[] = {0};
	QApplication::setApplicationName("Omni-FEM Post Processor");
	QApplication::setApplicationVersion("0.0.1");
	QApplication::setOrganizationName("Resonance Group");

	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	QApplication qtApp(argc, argv);

	setlocale(LC_NUMERIC, "C");

	QLocale::setDefault(QLocale::c());

	initilizeParaviewWindow();
}


void paraviewInitilizer::initilizeParaviewWindow()
{
	int argc = 0;
	char* argv[] = {0};

	p_paraviewViewApp = new pqPVApplicationCore(argc, argv);
	// Create Main Window here
	p_mainWindow = new postProcessorView();
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

	/*vtkPVPluginTracker::GetInstance()->LoadPluginConfigurationXMLFromString(
	    pluginXML.toLatin1().data());
*/
	p_mainWindow->show();


}


void paraviewInitilizer::loadData()
{

}


paraviewInitilizer::~paraviewInitilizer()
{
	delete this->p_mainWindow;
	delete this->p_paraviewViewApp;
}



