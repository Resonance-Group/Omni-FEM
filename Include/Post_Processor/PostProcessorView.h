/*
 * PostProcessorView.h
 *
 *  Created on: Nov 22, 2018
 *      Author: phillip
 */

#ifndef INCLUDE_POST_PROCESSOR_POSTPROCESSORVIEW_H_
#define INCLUDE_POST_PROCESSOR_POSTPROCESSORVIEW_H_

#include "QMainWindow"
#include "QObject"
#include "QString"
#include "QAction"
#include "QList"
#include "QToolBar"

#include "pqSGExportStateWizard.h"

#include "pqAlwaysConnectedBehavior.h"
#include "pqApplyBehavior.h"
#include "pqDefaultViewBehavior.h"

#include "pqApplicationCore.h"
#include "pqAutoLoadPluginXMLBehavior.h"
#include "pqInterfaceTracker.h"
#include "pqParaViewBehaviors.h"
#include "pqParaViewMenuBuilders.h"
#include "pqStandardViewFrameActionsImplementation.h"

#include "pqAxesToolbar.h"
#include "pqLoadDataReaction.h"
#include "pqMainControlsToolbar.h"
#include "pqRepresentationToolbar.h"
#include "pqSetName.h"

class postProcessorView : public QMainWindow
{
	Q_OBJECT
	typedef QMainWindow Superclass;

private:
	Q_DISABLE_COPY(postProcessorView)
	pqInternals *p_Internals;

public:
	postProcessorView();
	~postProcessorView();

protected slots:
	void showHelpProxy(const QString &groupName, const QString &proxyName);
};



#endif /* INCLUDE_POST_PROCESSOR_POSTPROCESSORVIEW_H_ */
