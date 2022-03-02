#include  "data_memory_cb.h"

void data_memory_cb::delay() {
	address_d_1 = address;
}

void data_memory_cb::check() {
	cout<<sc_time_stamp()<<": " <<address_d_1<<" Data read:"<<dout<<endl;
}
