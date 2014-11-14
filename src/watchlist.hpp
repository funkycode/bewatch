/*
 * watchlist.hpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zogg
 */


#ifndef WATCHLIST_HPP_
#define WATCHLIST_HPP_
#include <btapi/btdevice.h>
#include <btapi/btgatt.h>
#include <btapi/btle.h>
#include <btapi/btspp.h>
#include <errno.h>


#include <bb/cascades/GroupDataModel>
#include <QObject>
#include <QDebug>


class WatchList : public QObject
{
    Q_OBJECT
public:
    WatchList();//(QObject *obj);
    virtual ~WatchList();
    void generate_list();
    Q_INVOKABLE bb::cascades::DataModel* return_w_list();
    Q_INVOKABLE bb::cascades::DataModel* update_w_list();
    Q_INVOKABLE bool connect(QString watchAddress);
    Q_INVOKABLE bool connect_spp(QString watchAddress);
//signals:
   // void watchListUpdate ();
//private:
    bb::cascades::GroupDataModel* _w_list;





};


#endif /* WATCHLIST_HPP_ */
