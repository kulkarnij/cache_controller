#include "tag_memory.h"

void tag_memory::common_assignments() {
	masked_tag_value.write(tag_value.read() & TAG_AND_MASK);
    read_operation = (ce && !we && oe);
	write_operation = (ce &&we);
	lookup_cycle = read_operation | write_operation;

}

//This method explicitly assumes 4 ways, DEFINE_NOT_HONORED
void tag_memory::tag_lookup() {

	bool snoop_flag = (lookup_cycle && update_cycle && (tag_address_wr == tag_address));

	set_match_rd = 0b0000; 
	hit = 0;
	snoop.write(0);
	if (lookup_cycle && snoop_flag) { 
		set_match_rd.write(set_match_wr.read());
		hit.write(1);
		snoop.write(set_match_wr);
	}
	else if(lookup_cycle) {
		if (smem0[tag_address.read()] == masked_tag_value){  set_match_rd.write( set_match_rd.read() | 0b0001); hit.write(1);}
		if (smem1[tag_address.read()] == masked_tag_value) { set_match_rd.write( set_match_rd.read() | 0b0010); hit.write(1);}
		if (smem2[tag_address.read()] == masked_tag_value) { set_match_rd.write( set_match_rd.read() | 0b0100); hit.write(1);}
		if (smem3[tag_address.read()] == masked_tag_value) { set_match_rd.write( set_match_rd.read() | 0b1000); hit.write(1);}
	}
}

void tag_memory::write_setmemory() {
	if(update_cycle) {
//We already asserted zero_one_hot on set_we so write and  return on the first successful match
		if(set_match_wr.read() == 1) { smem0[tag_address_wr.read()] = tag_value_wr;return;}
		if(set_match_wr.read() == 2) { smem1[tag_address_wr.read()] = tag_value_wr;return;}
		if(set_match_wr.read() == 4) { smem2[tag_address_wr.read()] = tag_value_wr;return;}
		if(set_match_wr.read() == 8) { smem3[tag_address_wr.read()] = tag_value_wr;return;}
	}
}

void tag_memory::set_update_inputs() { // clocked.
	if(!reset_n) {
		update_cycle = 0;
		evict = 0;
	}
	update_cycle = write_operation;
	if(write_operation) {
		tag_value_wr = masked_tag_value;
		tag_address_wr = tag_address;
	}
	if(hit && write_operation) {
		set_match_wr = set_match_rd;
		evict = 0;
	}
    else  if( !hit && write_operation) { 
        set_match_wr.write(0b1<<evict_way.read());
		evict = 1;
	}
	else { // Not a write operation.
		set_match_wr.write(0);
		evict = 0;
	}
		
}
