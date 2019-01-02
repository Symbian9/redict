#include "trayicon.h"

TrayIcon::TrayIcon(QObject *parent)
    : QSystemTrayIcon(parent),
      m_menu(new QMenu),
      m_openAction(new QAction(tr("Open"), m_menu)),
      m_exitAction(new QAction(tr("Exit"), m_menu))
{
    m_menu->addAction(m_openAction);
    m_menu->addAction(m_exitAction);

    setContextMenu(m_menu);
    setIcon(QIcon(":/images/redict.svg"));
    setToolTip("Redict");

    connect(this, &QSystemTrayIcon::activated, this, &TrayIcon::iconActive);
    connect(m_openAction, &QAction::triggered, this, &TrayIcon::openActionTriggered);
    connect(m_exitAction, &QAction::triggered, this, &TrayIcon::exitActionTriggered);
}

TrayIcon::~TrayIcon()
{
    delete m_menu;
}

void TrayIcon::iconActive(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Context) {
        m_menu->show();
    } else if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
        emit openActionTriggered();
    }
}
