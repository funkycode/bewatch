/*
 * metawatchapi.hpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zogg
 */

#ifndef METAWATCHAPI_HPP_
#define METAWATCHAPI_HPP_

enum MsgType {
	NoMsg =0, //Nothing
	GetDeviceType = 0x01, //Phone
	GetDeviceTypeResponse = 0x02, //Watch
	GetVersionInfo = 0x03,  //Both
	GetVersionInfoResponse = 0x04, //Both
	ControlFullScreen = 0x42, //Phone
	SetVibrateMode = 0x23, //Phone
	SetRealTimeClock = 0x26, //Phone
	WatchPropertyOperation = 0x30, //Phone
	WatchPropertyOperationResponse = 0x31, //Watch
	StatusChangeEvent = 0x33, //Watch
	EnableButton = 0x46, //Phone
	DisableButton = 0x47, //Phone
	ButtonEventMessage = 0x34, //Watch
	WriteLCDBuffer = 0x40, //Phone
	UpdateLCDDisplay = 0x43, //Phone
	SetWidgetListMessage = 0xA1, //Phone
	LoadTemplate = 0x44, //Phone
	SetBatteryWarningLevelMessage = 0x53, //Phone
	LowBatteryWarningMessage = 0x54, //Watch
	LowBatteryBluetoothOffMesssage = 0x55, //Watch
	GetBatteryStatusMessage = 0x56, //Phone
	GetBatteryStatusResponse = 0x57, //Watch
	GetLightSensorValuemessage = 0x58, //Phone
	GetLightSensorValueResponse = 0x59, //Watch
	MusicPlayingStateMessage = 0x18, //Phone
	SetupAccelerometerMessage = 0xE1, //Phone
	AccelerometerDataResponse = 0xE0, //Watch
	WriteOLEDBuffer = 0x10, //Phone
	ChangeOLEDMode = 0x12, //Phone
	WriteOLEDScrollBuffer = 0x13, //Phone
	AdvanceWatchHands = 0x20 //Phone
};

enum DeviceTypeResponse{
	Reserved = 0,
	AnalogWatch,
	DigitalWatchGen1,
	DigitalDevBoardGen1,
	AnalogDevBoard,
	DigitalWatchGen2,
	DigitalDevBoardGen2
};

enum WatchPropertyBit{
	WatchFormat =0, //Set 24H (Default is 12H AM/PM,)
	DateFormat, //DDMM (Default is MMDD)
	ShowSeconds, //Default is off
	ShowSeparationLine, //Show at idle mode (Default set)
	AutoBackligt, //Turn on LED on Notifications is dark around
	Reserved1, //No use yet
	Reserved2, //No use yet
	ReadOperation //Default is Write

};

enum WatchMode{
	IdleMode = 0,
	AppMode,
	NotificationMode,
	MusicMode
};

enum WatchModeEventType{
	Reserved = 0,
	ModeSwitchingComplete,
	ModeTimeout
};


enum Button {
	BtnA = 0,
	BtnB,
	BtnC,
	BtnD,
	BtnE,
	BtnF
};

enum ButtonPress {
	PressOnly = 0,
	PressAndRelease = 1,
	HoldAndRelease = 2,
	LongHoldAndRelease = 3
};

#endif /* METAWATCHAPI_HPP_ */
