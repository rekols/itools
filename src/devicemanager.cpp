/*
 * Copyright (C) 2020 PandaOS Team.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "devicemanager.h"
#include <QDebug>

DeviceManager::DeviceManager(QObject *parent)
    : QObject(parent),
      m_device(NULL)
{
    if (connectDevice())
        loadDeviceInfo();
}

DeviceManager::~DeviceManager()
{
    idevice_free(m_device);
}

QString DeviceManager::getDeviceInfo(const QString &key)
{
    return m_deviceInfo.value(key, QString());
}

bool DeviceManager::connectDevice()
{
    // Clear old info
    m_deviceInfo.clear();

    // Try to connect to first USB device
    if (idevice_new_with_options(&m_device, NULL, IDEVICE_LOOKUP_USBMUX) != IDEVICE_E_SUCCESS) {
        qDebug() << "No device found!";
        return false;
    }

    // Retrieve the udid of the connected device
    char *udid = NULL;
    if (idevice_get_udid(m_device, &udid) != IDEVICE_E_SUCCESS) {
        qDebug() << "Unable to get the device UDID.";
        idevice_free(m_device);
        return false;
    }

    m_deviceUdid = QString::fromUtf8(udid);
    qDebug() << "Connected with UDID: " << m_deviceUdid;

    // idevice_free(m_device);
    free(udid);

    return true;
}

void DeviceManager::loadDeviceInfo()
{
    // Lockdown Service Handle
    lockdownd_client_t lockdown = NULL;

    // Handshake with lockdownd
    lockdownd_client_new_with_handshake(m_device, &lockdown, "itools");

    // Use the plist format
    plist_t node = NULL;

    // Our result
    char *value = NULL;

    for (const QString &key : deviceKeys) {
        if (lockdownd_get_value(lockdown, NULL, key.toStdString().c_str(), &node) != LOCKDOWN_E_SUCCESS) {
            continue;
        }

        plist_get_string_val(node, &value);
        m_deviceInfo.insert(key, value);
    }

    auto dev = m_deviceInfo.begin();
    while (dev != m_deviceInfo.end()) {
        qDebug() << dev.key() << dev.value();
        dev++;
    }

    lockdownd_client_free(lockdown);
}
