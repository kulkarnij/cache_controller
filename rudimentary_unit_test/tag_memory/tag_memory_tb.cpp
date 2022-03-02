#include "tag_memory_tb.h"

void tag_memory_tb::simple_write_read1() {
	if(cycle_count%2 == 0) { //write 
		cout<<"Forcing write"<<endl;
		oe=0;
		ce=1;
		set_we=2;
		tag_address = 7;
		tag_value.write(5);
	}
	else { //read
		cout<<"Forcing read"<<endl;
		tag_address = 7;
		ce=1;
		set_we=0;
		oe=1;
	}
	cycle_count++;
}
