#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_deviceManager(new DeviceManager)
{
}

MainWindow::~MainWindow()
{
}
