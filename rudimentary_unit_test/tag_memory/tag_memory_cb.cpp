#include  "tag_memory_cb.h"

void tag_memory_cb::delay() {
	tag_value_d_1 = tag_value;
	tag_address_d_1 = tag_address;
}

void tag_memory_cb::check() {
/*
	if(ce && oe && (set_we.read() == 0)) {
			cout<<sc_time_stamp()<<"Reading: Address: " <<tag_address<<" Tag Value:"<<tag_value<<" set_match:"<<set_match<<" hit:"<<hit<<endl;
		}
	else if(ce && set_we.read() !=0) {
			cout<<sc_time_stamp()<<"Writing: Address: " <<tag_address<<" Tag Value:"<<tag_value<<" set_we:"<<set_we<<endl;
	}
	else {
			cout<<sc_time_stamp()<<"NOP: ce: " <<ce<<" oe Value:"<<oe<<" set_we:"<<set_we<<endl;
	}
*/
	cout<<sc_time_stamp()<<"clk: " <<clk<<" :ce:"<<ce<<" oe:"<<oe<<" set_we:"<<set_we<<" tag_value: "<<tag_value;
   cout <<" tag_address:"<<tag_address<<" set_match:"<<set_match<<" hit:"<<hit<<endl;
}
	
