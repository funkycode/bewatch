/*
 * watch.hpp
 *
 *  Created on: Sep 18, 2013
 *      Author: zogg
 */

#ifndef WATCH_HPP_
#define WATCH_HPP_
#include <QObject>

#include <bb/cascades/ArrayDataModel>

#include <btapi/btgatt.h>
#include <btapi/btle.h>
#include <btapi/btdevice.h>


class Watch {
public:
	Watch();
	virtual ~Watch();

	//void serviceConnected(const QString &bdaddr, const QString &service, int instance, int err, uint16_t connInt, uint16_t latency, uint16_t superTimeout );
//	void processBtEvent(const int event, void *data);

private:
	 bt_gatt_callbacks_t m_gatt_cb;



};

#endif /* WATCH_HPP_ */
