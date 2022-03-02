#include  "memory_instance_cb.h"

void memory_instance_cb::delay() {
	address_d_1 = address;
}

void memory_instance_cb::check() {
	cout<<sc_time_stamp()<<": " <<address_d_1<<" Data read:"<<dout<<endl;
}
