/********************************************************************************
** Form generated from reading UI file 'RVOTest.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RVOTEST_H
#define UI_RVOTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RVOTestClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RVOTestClass)
    {
        if (RVOTestClass->objectName().isEmpty())
            RVOTestClass->setObjectName(QStringLiteral("RVOTestClass"));
        RVOTestClass->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(200);
        sizePolicy.setVerticalStretch(200);
        sizePolicy.setHeightForWidth(RVOTestClass->sizePolicy().hasHeightForWidth());
        RVOTestClass->setSizePolicy(sizePolicy);
        RVOTestClass->setMaximumSize(QSize(600, 400));
        centralWidget = new QWidget(RVOTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        RVOTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RVOTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        RVOTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RVOTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RVOTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RVOTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RVOTestClass->setStatusBar(statusBar);

        retranslateUi(RVOTestClass);

        QMetaObject::connectSlotsByName(RVOTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *RVOTestClass)
    {
        RVOTestClass->setWindowTitle(QApplication::translate("RVOTestClass", "Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RVOTestClass: public Ui_RVOTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RVOTEST_H
