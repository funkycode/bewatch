#include "bluetoothapi.hpp"




BluetoothAPI::BluetoothAPI(WatchList* w_list)
{

	w_list->generate_list();
}

BluetoothAPI::~BluetoothAPI()
{

}
