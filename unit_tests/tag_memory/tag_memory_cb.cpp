#include  "tag_memory_cb.h"

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
	cout<<"********************* tag_memory_cb***************************************************"<<endl;
	//cout<<"Time:"<<sc_time_stamp()<<" clk: " <<clk<<" reset_n:"<<reset_n<<" ce:"<<ce<<" oe:"<<oe<<" we:"<<we<<endl;
	cout<<"Cycle:"<<cycle_count<<" clk: " <<clk<<" reset_n:"<<reset_n<<" ce:"<<ce<<" oe:"<<oe<<" we:"<<we<<endl;
	cout<<	" tag_value: "<<tag_value;
	cout <<" tag_address:"<<tag_address<<" evict_way:"<<evict_way<<endl;
    cout<<"read_operation:"<<read_operation<<" write_operation:"<<write_operation<<" lookup_cycle:"<<lookup_cycle;
	cout	<<" update_cycle:"<<update_cycle <<" snoop:"<<snoop<<endl;
	cout<< "set_match_rd:"<<set_match_rd<< " set_match_wr:"<<set_match_wr<<" hit:"<<hit<<" evict:"<<evict<<endl;
	cout<<"_____________________ tag_memory_cb__________________________________________________"<<endl;
    cycle_count++;
}
	
