/*
 * PostProcessorView.cpp
 *
 *  Created on: Nov 22, 2018
 *      Author: phillip
 *
 *      Note ui.h file must be generated from the .ui file. Inlcude the ui.h file in the
 *      include list
 */
#include "Post_Processor/PostProcessorView.h"




postProcessorView::postProcessorView()
{
	this->p_Internals = new pqInternals();
	this->p_Internals->setupUi(this);
}

postProcessorView::~postProcessorView()
{

}



