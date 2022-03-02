#include "tag_memory_tb.h"

void tag_memory_tb::evict_once_then_update() {
	if(cycle_count == 0) {
		cout<<"tag_memory_tb::evict_once_then_update: Write followed by read operations to the same address result in eviction the first time in cycle 3 then updates w/o eviction. Observe snoop since the same address is also being looked up and updated."<<endl;
		reset_n = 0;
	}
	else if(cycle_count%2 == 0) { //write 
		reset_n = 1;
		oe=0;
		ce=1;
		we=1;
		tag_address = 7;
		tag_value.write(5);
		evict_way=0;
	}
	else { //read
		reset_n = 1;
		tag_address = 7;
		ce=1;
		we=0;
		oe=1;
		evict_way=0;
	}
	cycle_count++;
}
