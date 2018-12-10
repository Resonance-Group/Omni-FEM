/*
 * PostProcessorWindow.h
 *
 *  Created on: Nov 24, 2018
 *      Author: phillip
 */

#ifndef INCLUDE_POST_PROCESSOR_POSTPROCESSORWINDOW_H_
#define INCLUDE_POST_PROCESSOR_POSTPROCESSORWINDOW_H_


/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <pqViewManager.h>

QT_BEGIN_NAMESPACE

/*
 * This class handles the display of the window
 */
class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    pqViewManager *MultiViewManager;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MultiViewManager = new pqViewManager(centralWidget);
        MultiViewManager->setObjectName(QStringLiteral("MultiViewManager"));
        MultiViewManager->setGeometry(QRect(0, -5, 1171, 821));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H



#endif /* INCLUDE_POST_PROCESSOR_POSTPROCESSORWINDOW_H_ */
