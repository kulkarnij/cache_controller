#include "memory_instance.h"

void memory_instance::read_mem() {
	if(ce.read() && !we.read() && oe.read()) { // write take priority in conflict.
		cout <<"minstance Read: "<< dmem[address.read()] << " from: "<<address.read()<<endl;
		dout.write(dmem[address.read()]);
	}
}

void memory_instance::write_mem() {
	if(ce.read() && we.read()) { 
		cout <<"minstance Wrote: "<< din.read() << " to: "<<address.read()<<endl;
		dmem[address.read()]=din.read();
	}
}
