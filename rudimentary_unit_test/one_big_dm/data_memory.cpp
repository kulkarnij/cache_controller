#include "data_memory.h"

void data_memory::read_mem() {
	if(ce.read() && !we.read() && oe.read()) { // write take priority in conflict.
		cout <<"dmem Read: "<< dmem[address.read()] << " from: "<<address.read()<<endl;
		dout.write(dmem[address.read()]);
	}
}

void data_memory::write_mem() {
	if(ce.read() && we.read()) { 
		cout <<"dmem Wrote: "<< din.read() << " to: "<<address.read()<<endl;
		dmem[address.read()]=din.read();
	}
}
