#include "memory_instance_tb.h"

void memory_instance_tb::simple_write_read1() {
	cout<<"DM width:"<<DM_INSTANCE_WIDTH_BITS<<endl;
	if(cycle_count%2 == 0) { //write 
		oe=0;
		ce=1;
		we=1;
		address = 7;
		din.write(5);
	}
	else { //read
		address = 7;
		ce=1;
		we=0;
		oe=1;
	}
	cycle_count++;
}
