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


class postProcessorView::p_pqInternal : public Ui::MainWindow
{
};


postProcessorView::postProcessorView()
{
	this->p_Internals = new p_pqInternal();
	this->p_Internals->setupUi(this);

	/* Now we setup additional window options */
	pqParaViewBehaviors::setEnableStandardPropertyWidgets(false);
	pqParaViewBehaviors::setEnableStandardRecentlyUsedResourceLoader(false);
	pqParaViewBehaviors::setEnableDataTimeStepBehavior(false);
	pqParaViewBehaviors::setEnableSpreadSheetVisibilityBehavior(false);
	pqParaViewBehaviors::setEnablePipelineContextMenuBehavior(false);
	pqParaViewBehaviors::setEnableObjectPickingBehavior(false);
	pqParaViewBehaviors::setEnableUndoRedoBehavior(false);
	pqParaViewBehaviors::setEnableCrashRecoveryBehavior(false);
	pqParaViewBehaviors::setEnablePluginDockWidgetsBehavior(false);
	pqParaViewBehaviors::setEnableVerifyRequiredPluginBehavior(false);
	pqParaViewBehaviors::setEnablePluginActionGroupBehavior(false);
	pqParaViewBehaviors::setEnableCommandLineOptionsBehavior(false);
	pqParaViewBehaviors::setEnablePersistentMainWindowStateBehavior(false);
	pqParaViewBehaviors::setEnableCollaborationBehavior(false);
	pqParaViewBehaviors::setEnableViewStreamingBehavior(false);
	pqParaViewBehaviors::setEnablePluginSettingsBehavior(false);
 	pqParaViewBehaviors::setEnableQuickLaunchShortcuts(false);
 	pqParaViewBehaviors::setEnableLockPanelsBehavior(false);

  // This is actually useless, as they are activated by default
 	pqParaViewBehaviors::setEnableStandardViewFrameActions(true);
 	pqParaViewBehaviors::setEnableDefaultViewBehavior(true);
 	pqParaViewBehaviors::setEnableAlwaysConnectedBehavior(true);
 	pqParaViewBehaviors::setEnableAutoLoadPluginXMLBehavior(true);
 	pqParaViewBehaviors::setEnableApplyBehavior(true);
 	new pqParaViewBehaviors(this, this);

 	new pqDefaultViewBehavior(this);
 	new pqAlwaysConnectedBehavior(this);
 	new pqAutoLoadPluginXMLBehavior(this);
 	pqApplyBehavior* applyBehavior = new pqApplyBehavior(this);

/* 	foreach (pqPropertiesPanel* ppanel, this->findChildren<pqPropertiesPanel*>())
 	{
 		applyBehavior->registerPanel(ppanel);
 	}*/
}


void postProcessorView::loadData()
{
	QString stringConversion;
	QStringList solutionFileList;
	QList<QStringList> finalList;
	wxStandardPaths paths = wxStandardPaths::Get();
	std::string filePath = paths.GetDocumentsDir().ToStdString() + "/" + "solution.vtk";

	stringConversion = QString::fromStdString(filePath);
	solutionFileList << stringConversion;

	finalList.append(solutionFileList);

	pqPipelineSource *source = pqLoadDataReaction::loadData(finalList);

	pqOutputPort* port = source->getOutputPort(0);

	if(port)
	{
		pqPipelineBrowserWidget::setVisibility(true, port);
	}

	if (pqView* view = pqActiveObjects::instance().activeView())
	{
		if (view->getNumberOfVisibleDataRepresentations() == 1 && visible &&
			vtkPVGeneralSettings::GetInstance()->GetResetDisplayEmptyViews())
	    {
			view->resetDisplay();
	    }
		pqActiveObjects::instance().activeView()->render();
	}

}




