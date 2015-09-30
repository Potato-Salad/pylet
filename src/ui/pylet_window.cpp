/*
* Copyright (c) 2015 Jake Schadaway.
* Licensed under the MIT License. See LICENSE.md for details.
*/

#include "pylet_window.h"
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qmenubar.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qsplitter.h>

PyletWindow::PyletWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QDesktopWidget *desktop = QApplication::desktop();
    screenRect = desktop->screen()->rect();

    initWindow();
    initWidgets();
    showMaximized();
}

void PyletWindow::initWindow()
{
    setMinimumSize(600, 400);
    int screenWidth = screenRect.width();
    int screenHeight = screenRect.height();
    resize(screenWidth - 250, screenHeight - 250);

    setWindowTitle("Pylet (Editor)"); 
}

void PyletWindow::initWidgets()
{
    QSplitter* coreWidget = new QSplitter(Qt::Horizontal);
    setCentralWidget(coreWidget);

    QWidget* navigator = new QWidget(coreWidget);
    QVBoxLayout* navLayout = new QVBoxLayout(navigator);
    navLayout->setMargin(0);
    navLayout->setSpacing(0);
    navigator->setLayout(navLayout);
    navigator->setMaximumWidth(280);
    coreWidget->insertWidget(0, navigator);

    QLabel* crawler = new QLabel(navigator);
    crawler->setStyleSheet("background-color: red; color: white; font-size: 40px;");
    crawler->setAlignment(Qt::AlignCenter);
    crawler->setText("File Crawler");
    navLayout->addWidget(crawler, 3);

    QLabel* infoBox = new QLabel(navigator);
    infoBox->setStyleSheet("background-color: green; color: white; font-size: 40px;");
    infoBox->setAlignment(Qt::AlignCenter);
    infoBox->setText("Info Box");
    navLayout->addWidget(infoBox, 1);

    codeEditor = new CodeEditor(coreWidget);
    codeEditor->setMinimumWidth(280);
    coreWidget->insertWidget(1, codeEditor);

    QLabel* shell = new QLabel(coreWidget);
    shell->setStyleSheet("background-color: orange; color: white; font-size: 40px;");
    shell->setAlignment(Qt::AlignCenter);
    shell->setText("Shell / Tracer");
    shell->setMinimumWidth(280);
    coreWidget->insertWidget(2, shell);

    coreWidget->setStretchFactor(0, 1);
    coreWidget->setStretchFactor(1, 5);
    coreWidget->setStretchFactor(2, 3);

    coreWidget->setMidLineWidth(8);

    populateMenu();
    addToolBar("Action Bar");
    statusBar();
}

void PyletWindow::populateMenu()
{
    QAction* undo = new QAction(this);
    undo->setText("Undo");
    undo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    connect(undo, SIGNAL(triggered()), codeEditor, SLOT(undo()));

    QAction* redo = new QAction(this);
    redo->setText("Redo");
    redo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    connect(redo, SIGNAL(triggered()), codeEditor, SLOT(redo()));

    QMenu *fileMenu = menuBar()->addMenu("File");
    QMenu *editMenu = menuBar()->addMenu("Edit");
    QMenu *searchMenu = menuBar()->addMenu("Search");
    QMenu *runMenu = menuBar()->addMenu("Run");
    QMenu *viewMenu = menuBar()->addMenu("View");
    QMenu *settingsMenu = menuBar()->addMenu("Settings");
    QMenu *helpMenu = menuBar()->addMenu("Help");

    editMenu->addAction(undo);
    editMenu->addAction(redo);
}
