#include "cache_controller.h"

void cache_controller::common_assignments() {
	//31:18 shifter right by 2.
	tag_value =  proc_address.read().range(PROC_WIDTH-1,PROC_WIDTH-TAG_RAW_WIDTH) >> 2; // We are looking for these address bits.
	//17:5
	tag_address = proc_address.read().range(PROC_WIDTH-TAG_RAW_WIDTH-1,OFFSET_WIDTH); // Tag can be stored at this addres in any of the 4 set memories.
}

void cache_controller::check() {
	cout<<"********************* cache_controller::check()***************************************************"<<endl;
	//cout<<"Time:"<<sc_time_stamp()<<" clk: " <<clk<<" reset_n:"<<reset_n<<" ce:"<<ce<<" oe:"<<oe<<" we:"<<we<<endl;
	cout<<"Cycle:"<<cycle_count<<" clk: " <<clk<<" reset_n:"<<reset_n<<" ce:"<<ce<<" oe:"<<oe<<" we:"<<we<<endl;
	cout<<"proc_address: "<<proc_address<<" din:"<<din<<" dout:"<<dout<<" data_valid:"<<data_valid<<endl;
	cout<<	" tag_value: "<<tag_value;
	cout <<" tag_address:"<<tag_address<<" evict_way:"<<evict_way<<endl;
    cout<<"read_operation:"<<read_operation<<" write_operation:"<<write_operation<<" lookup_cycle:"<<lookup_cycle;
	cout	<<" update_cycle:"<<update_cycle <<" snoop:"<<snoop<<endl;
	cout<< "way_match_rd:"<<way_match_rd<< " way_match_wr:"<<way_match_wr<<" hit:"<<hit<<" evict:"<<evict<<endl;
	cout<<"_____________________ cache_controller::check()__________________________________________________"<<endl;
    cycle_count++;
}
