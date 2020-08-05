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

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QMap>

extern "C" {
    #include "libimobiledevice/libimobiledevice.h"
    #include "libimobiledevice/lockdown.h"
}

static QStringList deviceKeys {"ActivationState",
                               "BasebandActivationTicketVersion",
                               "BasebandCertId",
                               "BasebandChipID",
                               "BasebandMasterKeyHash",
                               "BasebandRegionSKU",
                               "BasebandSerialNumber",
                               "BasebandStatus",
                               "BasebandVersion",
                               "BluetoothAddress",
                               "BoardId",
                               "BrickState",
                               "BuildVersion",
                               "CPUArchitecture",
                               "CertID",
                               "ChipID",
                               "ChipSerialNo",
                               "DeviceClass",
                               "DeviceColor",
                               "DeviceName",
                               "DieID",
                               "EthernetAddress",
                               "FirmwareVersion",
                               "FusingStatus",
                               "HardwareModel",
                               "HardwarePlatform",
                               "HasSiDP",
                               "HostAttached",
                               "InternationalMobileEquipmentIdentity",
                               "MLBSerialNumber",
                               "MobileEquipmentIdentifier",
                               "MobileSubscriberCountryCode",
                               "MobileSubscriberNetworkCode",
                               "ModelNumber",
                               "NonVolatileRAM",
                               "PartitionType",
                               "PasswordProtected",
                               "PkHash",
                               "ProductName",
                               "ProductType",
                               "ProductVersion",
                               "ProductionSOC",
                               "ProtocolVersion",
                               "ProximitySensorCalibration",
                               "RegionInfo",
                               "SIMStatus",
                               "SIMTrayStatus",
                               "SerialNumber",
                               "SoftwareBehavior",
                               "SoftwareBundleVersion",
                               "TelephonyCapability",
                               "TimeIntervalSince1970",
                               "TimeZone",
                               "TimeZoneOffsetFromUTC",
                               "TrustedHostAttached",
                               "UniqueChipID",
                               "UniqueDeviceID",
                               "UseRaptorCerts",
                               "Uses24HourClock",
                               "WiFiAddress",
                               "WirelessBoardSerialNumber",
                               "kCTPostponementInfoPRLName",
                               "kCTPostponementInfoServiceProvisioningState"
};

class DeviceManager : public QObject
{
    Q_OBJECT

public:
    explicit DeviceManager(QObject *parent = nullptr);
    ~DeviceManager();

    QString getDeviceInfo(const QString &key);

private:
    bool connectDevice();
    void loadDeviceInfo();

private:
    QMap<QString, QString> m_deviceInfo;
    QString m_deviceUdid;   // Unique Device Identifier
    idevice_t m_device;     // Device Handle
};

#endif
