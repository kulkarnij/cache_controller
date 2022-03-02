#include "cache_controller_tb.h"

void cache_controller_tb::evict_once_then_update() {
	if(cycle_count == 0) {
		cout<<"cache_controller_tb::evict_once_then_update: Write followed by read operations to the same address result in eviction the first time in cycle 3 then updates w/o eviction. Observe snoop since the same address is also being looked up and updated."<<endl;
		reset_n = 0;
	}
	else if(cycle_count%2 == 0) { //write 
		reset_n = 1;
		oe=0;
		ce=1;
		we=1;
		proc_address = 0X55555555;
		din.write(5);
	}
	else { //read
		reset_n = 1;
		proc_address = 0X55555555;
		ce=1;
		we=0;
		oe=1;
	}
	cycle_count++;
}
