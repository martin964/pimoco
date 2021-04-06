/*
    PiMoCo: Raspberry Pi Telescope Mount and Focuser Control
    Copyright (C) 2021 Markus Noga

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef PIMOCO_MOUNT_H
#define PIMOCO_MOUNT_H

#include <libindi/inditelescope.h>
#include "pimoco_stepper.h"

// Indi class for pimoco mounts
class PimocoMount : public INDI::Telescope {
public:
	// Creates a Pimoco mount
	PimocoMount();

	// Destroys this pimoco focuser. Stops device motion for safety's sake
	~PimocoMount();

	virtual const char *getDefaultName() override;
    virtual bool initProperties() override;
    virtual bool updateProperties() override;

    virtual void ISGetProperties(const char *dev) override;
    virtual bool ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[], char *names[], int n) override;
    virtual bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override;
    virtual bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override;
    virtual bool ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n) override;
    virtual bool ISSnoopDevice(XMLEle *root) override;

    // Updates number vector property with the given values if res is true and display status IPS_OK, else display status IPS_ALERT. Returns res for convenience. 
    bool ISUpdateNumber(INumberVectorProperty *NP, double values[], char *names[], int n, bool res);

protected:
    virtual bool saveConfigItems(FILE *fp) override;

    virtual bool Connect() override;
    virtual bool Disconnect() override;
    virtual bool Handshake() override;
    virtual void TimerHit() override;

    virtual bool ReadScopeStatus() override;

    virtual bool SetTrackEnabled(bool enabled) override;
    virtual bool SetTrackRate(double raRate, double deRate) override;

	Stepper stepperHA;
    Stepper stepperDec;

    const char *spiDeviceFilenameHA;
    const char *spiDeviceFilenameDec;

    // UI controls
    //

    INumber HAMotorN[5]={};
    INumberVectorProperty HAMotorNP;

    ISwitch HAMSwitchS[1]={};
    ISwitchVectorProperty HAMSwitchSP;

    INumber HARampN[9]={};
    INumberVectorProperty HARampNP;

    INumber DecMotorN[5]={};
    INumberVectorProperty DecMotorNP;

    ISwitch DecMSwitchS[1]={};
    ISwitchVectorProperty DecMSwitchSP;
    
    INumber DecRampN[9]={};
    INumberVectorProperty DecRampNP;

public:
    static const char *HA_TAB;
    static const char *DEC_TAB;
};

#endif // PIMOCO_MOUNT_H
