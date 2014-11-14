/* bluetoothapi.hpp
 *
 *  Created on: Aug 17, 2013
 *      Author: zogg
 */


#ifndef BLUETOOTHAPI_HPP_
#define BLUETOOTHAPI_HPP_

#include <btapi/btdevice.h>
#include <btapi/btgatt.h>
#include <btapi/btle.h>
#include <btapi/btspp.h>
#include "watchlist.hpp"
#include <errno.h>
#include <QObject>
#include <QDebug>


class BluetoothAPI : public QObject
{
    Q_OBJECT
public:
    BluetoothAPI(WatchList* w_list);//(QObject *obj);
    virtual ~BluetoothAPI();

};


#endif /* BLUETOOTHAPI_HPP_ */
