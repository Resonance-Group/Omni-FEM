/*
 * ParaviewInitilizer.h
 *
 *  Created on: Nov 21, 2018
 *      Author: phillip
 */

#ifndef INCLUDE_POST_PROCESSOR_PARAVIEWINITILIZER_H_
#define INCLUDE_POST_PROCESSOR_PARAVIEWINITILIZER_H_

#include "QMainWindow"
#include "QString"
#include "QStringList"
#include "QApplication"
#include "QLocale"
#include "QStyleFactory"

#include "Post_Processor/PostProcessorView.h"

#include <pqPVApplicationCore.h>
#include <clocale>

#include "vtkInitializationHelper.h"
#include "vtkPVPluginTracker.h"


class paraviewInitilizer
{
private:
	pqPVApplicationCore *p_paraviewViewApp = nullptr;

	postProcessorView *p_mainWindow = nullptr;

public:
	paraviewInitilizer();

	void initilizeParaviewWindow();

	void loadData(std::string fileName)
	{
		return;
	}

	void loadData();

	~paraviewInitilizer();

};





#endif /* INCLUDE_POST_PROCESSOR_PARAVIEWINITILIZER_H_ */
