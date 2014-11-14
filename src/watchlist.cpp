/*
 * watchlist.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zogg
 */
#include "watchlist.hpp"
//#include <btapi/btgattsrv.h>

const quint8 bitRevTable[16] = {
	0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
};
const quint16 crcTable[256] = {
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
	0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
	0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
	0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
	0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
	0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
	0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
	0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
	0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
	0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
	0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
	0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
	0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
	0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
	0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
	0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
	0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
	0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
	0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
	0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
	0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
	0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
	0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};


static const char* MY_UUID =  "0x8880"; //"00008880-0000-1000-8000-00805f9b34fb";
static const char* WATCH_SERVICE = "0x8882";
using namespace bb::cascades ;


quint16 calcCrc(const QByteArray &data, int size)
 {
 	quint16 remainder = 0xFFFF;

 	for (int i = 0; i < size; i++) {
 		quint8 byte = data[i];
 		byte = (bitRevTable[byte & 0xF] << 4) | bitRevTable[(byte & 0xF0) >> 4];
 		remainder = crcTable[byte ^ (remainder >> 8)] ^ (remainder << 8);
 	}

 	return remainder;
 }
 void gatt_service_connected(const char *bdaddr, const char *service, int instance, int err, uint16_t connInt, uint16_t latency, uint16_t superTimeout, void *userData)
    {
	 qDebug()<< "service connected";
	 int num_charisteristics =
	             bt_gatt_characteristics_count(instance);

	     // get the list of characteristics
	     bt_gatt_characteristic_t  *characteristicList;
	     characteristicList = (bt_gatt_characteristic_t*)malloc(num_charisteristics * sizeof(bt_gatt_characteristic_t));

	     // look for the characteristic we are interested in
	     int characteristicListSize = 0;
	     characteristicListSize = bt_gatt_characteristics(instance,
	                                            characteristicList,
	                                            num_charisteristics);

	     for (int i = 0; i < characteristicListSize; i++) {
	         // look for a UUID match

	        	 	 qDebug()<<"characteristic "<<i<<" : "<<characteristicList[i].uuid;


	     }

	     // Free resources
	     free(characteristicList);
	     characteristicList = NULL;
 }
 void gatt_service_disconnected( const char *bdaddr,
		   const char *service,
		   int instance,
		   int err,
		   void *userData)
 {
	 qDebug()<< "service disconnected";
 }
 void gatt_service_updated( const char *bdaddr,
		   int instance,
		   uint16_t connInt,
		   uint16_t latency,
		   uint16_t superTimeout,
		   void *userData)
 {
	 qDebug()<< "service updated";
 }



void notifications_cb(int instance,
					uint16_t handle,
                      const uint8_t *val,
                      uint16_t len,
                      void *userData) {

      qDebug()<<"instance "<< QString::number(instance);
      qDebug()<<"handle "<<QString::number(handle);
      qDebug()<<"val "<< QString(QByteArray(reinterpret_cast<const char*>(val), len).toHex());
}
void btEvent(const int event, const char *bt_addr, const char *event_data) {

	//Q_UNUSED(bt_addr)

	//QString event_name = btEventName(event);
	//qDebug() << "XXXX BT event =" << event;
	//qDebug() << "XXXX  addr=" << bt_addr;

	if (event_data != NULL) {
		QString event_data_str = QString(*event_data);
		//qDebug() << "XXXX BT event_data=" << event_data;
	} else {
		//qDebug() << "XXXX BT event_data=NULL";
	}
}
 WatchList::WatchList()
 {
	 if (bt_device_init(0) != EOK) {
		 qDebug() <<"Unable to initialize bluetooth device";
	        }

	 			if (!bt_ldev_get_power()) {
	 				bt_ldev_set_power(true);
	 			}


	 	        if (bt_gatt_init(0) != EOK) {
	 	        	qDebug() << "GATT initialization failure" << errno;
	 	        }
	 if (bt_le_init(0) != 0) {
				            qDebug() << "LE initialization failure ";
				        }

	 _w_list = new GroupDataModel(QStringList() << "watchName" << "watchAddress" << "watchClass" << "watchType");
 }
 WatchList::~WatchList()
 {

 }
 void WatchList::generate_list()
 {
	 QVariantMap map;

	 bt_disc_start_inquiry(BT_INQUIRY_LIAC); //BT_INQUIRY_GIAC
	 			delay(10);
	 			// Cancel the scan since we should have what we need by now.
	 			bt_disc_cancel_inquiry();

	 			qDebug()<<"local device is"<<bt_ldev_get_type();
	 			// Retrieve information on discovered devices.
	 			bt_remote_device_t *next_remote_device = 0;

	 			bt_remote_device_t **remote_device_array =
	 			        bt_disc_retrieve_devices(BT_DISCOVERY_ALL, 0);
	 			_w_list->clear();
	 			if (remote_device_array) {
	 			    for (int i = 0; (next_remote_device = remote_device_array[i]); ++i) {
						#define UNKNOWN "Unknown"
	 			        char device_name[128] = UNKNOWN;
	 			        char device_addr[128];
	 			        int device_class = -1;
	 			        int device_type = -1;
	 			        const int bufferSize = sizeof(device_name);

	 			        // Get the friendly name of the remote device. The friendly name
	 			        // is a string value that makes it easy to identify the device.
	 			        if (bt_rdev_get_friendly_name(next_remote_device,
	 			                                      device_name, bufferSize) != 0) {

	 			        	qDebug() << "BEEWATCH NAME ERROR";

	 			        }else{

	 							QString bt_name = QString::fromUtf8(device_name);
	 						//	if (bt_name.contains("metawatch", Qt::CaseInsensitive))
	 						//	{
	 								//qDebug() << "BEEWATCH FOUND METAWATCH" ;
	 								map["watchName"] = bt_name;
	 								qDebug() << "name " << device_name ;

	 								// Retrieve the MAC address of the remote device.
	 								if (bt_rdev_get_address(next_remote_device, device_addr) != 0) {
	 									// handle error
	 									qDebug() << "BEEWATCH MAC ERROR";
	 								}else{
	 									map["watchAddress"] = QString::fromLatin1(device_addr);
	 									qDebug() << "address " <<QString::fromLatin1(device_addr) ;
	 								}
	 								// Retrieve the Class of Device value of the remote device.
	 								device_class = bt_rdev_get_device_class(next_remote_device,
	 																		 BT_COD_DEVICECLASS);
	 								map["watchClass"] = QString::number(device_class);
	 								qDebug() << "BEEWATCH DEVICE CLASS: " << device_class;

	 								device_type = bt_rdev_get_type(next_remote_device);
	 								map["watchType"] = QString::number(device_type);
	 								qDebug() << "BEEWATCH DEVICE TYPE: " << device_type;


	 								char **services_array = 0;
	 									int i;
	 								if ((services_array = bt_rdev_get_services_gatt(next_remote_device))) {
	 										 qDebug()<<"hmmm";


	 										 for (i = 0; 0 != services_array[i]; i++) {

	 											 qDebug()<<"service:"<<services_array[i];

	 										 }
	 									 }


	 								_w_list->insert(map);






	 						//	}else{

	 						//		qDebug() << "BEEWATCH FOUND OTHER THAN METAWATCH DEVICE" ;
	 						//	}
	 			        }

	 			    }
	 			    bt_rdev_free_array(remote_device_array);
	 			}

 }

 DataModel* WatchList::return_w_list()
 {




	 return _w_list;
 }
 DataModel* WatchList::update_w_list()
  {

	 generate_list();
 	 return _w_list;
 }
 /*
 void (*)(const char*, const char*, int, int, std::uint16_t, std::uint16_t, std::uint16_t, void*)
		 {aka void (*)(const char*, const char*, int, int, short unsigned int, short unsigned int, short unsigned int, void*)}'
 to 'bt_gatt_service_updated_cb {aka void (*)(const char*, int, short unsigned int, short unsigned int, short unsigned int, void*)}

*/
 bool WatchList::connect(QString watchAddress)
 {

	qDebug()<<"connecting to "<<watchAddress;
    bool paired = false;

	 bt_remote_device_t *next_remote_device = bt_rdev_get_device(watchAddress.toLatin1().data());
	 if (bt_rdev_is_paired(next_remote_device, &paired) == 0) {
	 	    if (!paired) {
	 	        if(bt_rdev_pair(next_remote_device)==0)
	 	        	qDebug()<<"paired";
	 	        else
	 	        	qDebug()<<"failed to pair";
	 	    }
	 	}
//	 	else {
//	 		qDebug()<<"failed to get pair";
//	 	    return false;
//	 	}
	 const int deviceType = bt_rdev_get_type(next_remote_device);

	 qDebug()<< "deviceType"<<deviceType;
	   if ((deviceType == BT_DEVICE_TYPE_LE_PUBLIC)
	    || (deviceType == BT_DEVICE_TYPE_LE_PRIVATE)) {
		   qDebug()<< "LE device";
	   }else if (deviceType == BT_DEVICE_TYPE_REGULAR)
	   {
		   qDebug()<< "device regular";
	   }else if (deviceType == BT_DEVICE_TYPE_UNKNOWN)
	   {
		   qDebug()<< "device unknown";
	   }
	   else
	   {
		   qDebug()<< "device type not detected";
	   }


	  //






	  errno= 0;


	 bt_gatt_conn_parm_t conParm;
	 	conParm.minConn = 0x30;
	 	conParm.maxConn = 0x50;
	 	conParm.latency = 0;
	 	conParm.superTimeout = 50;





	char **services_array = 0;
	int i;
	qDebug()<<"8880 is "<< MY_UUID;

	bt_remote_device_t **remote_device_array;
	bt_remote_device_t *device;
	int device_count;
	 if( ( remote_device_array = bt_disc_retrieve_by_service_gatt( MY_UUID, &device_count))
	                                                                != NULL ) {
	    for(i=0;(device = remote_device_array[i]);++i)
	    {
	    	qDebug()<<"test"<<i;
	    }
	    bt_rdev_free_array( remote_device_array );
	  }

	// if ((services_array = bt_rdev_get_services_gatt(next_remote_device))) {
		 if( ( services_array = bt_rdev_get_services_gatt(next_remote_device)) != NULL) {
		 qDebug()<<"hmmm";


		 for (i = 0; 0 != services_array[i]; i++) {

			 qDebug()<<"service:"<<services_array[i];

		 }
	 }


	 bt_gatt_callbacks_t gatt_callbacks = { gatt_service_connected, gatt_service_disconnected, gatt_service_updated };

	 bt_gatt_init(&gatt_callbacks);
	 int j;


   if(bt_gatt_connect_service("00:18:33:FA:CA:FD",  MY_UUID,
		   NULL, NULL, NULL) < 0) {


	     qDebug() << "YYYY GATT connect service request failed: " + QString::number(errno) + " (" + QString(strerror(errno)) + ")";
//
 } else {


//
     qDebug() << "YYYY requested connection to HR service OK";

//
	 }




return true;




 }
 bool WatchList::connect_spp(QString watchAddress){

    bt_spp_init();


	QByteArray data;
	quint16 crc;

	data.resize(6);
	data[0] = 0x01;
	data[1] = 0X06;
	data[2] = 0x30;//0x01; //0x30
	data[3] = 0xF9; //10000001
//	crc = calcCrc(data, 4);

	data[4] = 0x00;
	data[5] = 0x00;
	data[6] = 0x00;
	//data[4] = 0xD7; //0xd73c
	//data[5] = 0x3C;

	bt_remote_device_t  *remote_device;

	bt_remote_device_t  **remote_device_array;
	bt_remote_device_t  *next_remote_device;

	bool paired = false;
	remote_device = bt_rdev_get_device(watchAddress.toLatin1().data());

	if (bt_rdev_is_paired(remote_device, &paired) == 0) {
	    if (!paired) {
	        if(bt_rdev_pair(remote_device)==0)
	        	qDebug()<<"paired";
	    }
	}
	else {
		qDebug()<<"failed to pair";
	    return false;
	}


   int fd = bt_spp_open(watchAddress.toLatin1().data(), "0x1101", false);
       if (fd >= 0) {
          write(fd,data,data.size());

       } else {
          qDebug()<<"couldn't connect spp";

       }
       // Close SPP connection
       bt_spp_close(fd);





}







