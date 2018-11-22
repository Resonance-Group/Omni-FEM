/*
 * ParaviewInitilizer.h
 *
 *  Created on: Nov 21, 2018
 *      Author: phillip
 */

#ifndef INCLUDE_POST_PROCESSOR_PARAVIEWINITILIZER_H_
#define INCLUDE_POST_PROCESSOR_PARAVIEWINITILIZER_H_

#include <clocale>

#include "QMainWindow"
#include "QString"
#include "QStringList"
#include "QApplication"
#include "QLocale"
#include "QStyleFactory"

#include "pqPVApplicationCore.h"

#include "ServerManager/SMApplication/vtkInitializationHelper.h"
#include "vtkPVPluginTracker.h"


class paraviewInitilizer
{
private:
	pqPVApplicationCore *p_paraviewViewApp = nullptr;

	QMainWindow *p_mainWindow = nullptr;

public:
	paraviewInitilizer();

	void initilizeParaviewWindow();

	~paraviewInitilizer();

};





#endif /* INCLUDE_POST_PROCESSOR_PARAVIEWINITILIZER_H_ */
