#include "data_memory.h"

void data_memory::read_data() {
	if(lookup_cycle) {
		data_way0=dmem0[address.read()];
		data_way1=dmem1[address.read()];
		data_way2=dmem2[address.read()];
		data_way3=dmem3[address.read()];
	}
}

void data_memory::drive_data() { //registered dout.
	if(!reset_n) {
		data_valid.write(0);
	}
	else if(read_operation) {
		data_valid.write(hit);
		if(snoop.read() != 0) {
			dout = din_wr;
		}
		else if(hit){
			data_valid.write(1);
			if(way_match_rd.read() == 1) { dout=data_way0;return;}
			if(way_match_rd.read() == 2) { dout=data_way1;return;}
			if(way_match_rd.read() == 4) { dout=data_way2;return;}
			if(way_match_rd.read() == 8) { dout=data_way3;return;}
//if you land here, there is error, turn data valid off.
			cout<<"Error:way_match_rd is not one hot!!"<<endl;
			data_valid.write(0);
		}
		else { // cache miss
			data_valid.write(0);
		}
	}
	else { // not a read_opaeration
		data_valid.write(0);
	}
}

void data_memory::set_update_inputs() { // clocked.
	if(!reset_n) {
	}
	else {
		if(write_operation) {
			din_wr = din.read();
			address_wr = address.read();
		}
	}	
}

void data_memory::write_mem() { // registered output
	if(update_cycle) { 
		if(way_match_wr.read() == 1) { dmem0[address_wr.read()] = din_wr;return;}
		if(way_match_wr.read() == 2) { dmem1[address_wr.read()] = din_wr;return;}
		if(way_match_wr.read() == 4) { dmem2[address_wr.read()] = din_wr;return;}
		if(way_match_wr.read() == 8) { dmem3[address_wr.read()] = din_wr;return;}
	}
}

//This method explicitly assumes 4 ways, DEFINE_NOT_HONORED
void data_memory::set_eviction_way() {
	if(EVICTION_POLICY == 1) {
		evict_way.write( find_min_way(data_way0.read(),data_way1.read(),data_way2.read(),data_way2.read(),7));
	}
	else if(EVICTION_POLICY == 2) {
		sc_uint<3> index = (sc_uint<3>)(data_way0.read()).range(2,0); //Don't know why the compiler needs explicit cast here..
		evict_way.write( find_min_way(data_way0.read(),data_way1.read(),data_way2.read(),data_way2.read(),index));
	}
	else {
		evict_way.write(0);
	}
}

//Nothing clever, just get it to work first.
sc_uint<2> data_memory::find_min_way(const sc_biguint<256> d0,const sc_biguint<256> d1,const sc_biguint<256> d2,const sc_biguint<256> d3, const sc_uint<3> index) {

	sc_uint<2> result = 0;
	int max_index,min_index;
	max_index= 31+index*32;
	min_index=0+index*32;
	sc_uint<2> first_minpos,second_minpos;
	sc_int<32> first_min,second_min;

	if(d0.range(max_index,min_index) < d1.range(max_index,min_index)) {
		first_min = d0.range(max_index,min_index);
		first_minpos=0;
	}
	else {
		first_min = d1.range(max_index,min_index);
		first_minpos=1;
	}

	if(d2.range(max_index,min_index) < d3.range(max_index,min_index)) {
		second_min = d2.range(max_index,min_index);
		second_minpos=2;
	}
	else {
		second_min = d3.range(max_index,min_index);
		second_minpos=3;
	}

	result = (first_min < second_min)? first_minpos:second_minpos;

	
	return result;
}

