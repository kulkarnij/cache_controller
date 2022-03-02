#include "tag_memory.h"

void tag_memory::common_assignments() {
	no_write = (set_we.read() == 0) ;
	masked_tag_value.write(tag_value.read() & TAG_AND_MASK);
}

void tag_memory::tag_lookup() {
	set_match = 0b0000;
    hit = 0;
	if(ce && oe && no_write) {
		if (smem0[tag_address.read()] == masked_tag_value){  set_match.write( set_match.read() | 0b0001); hit.write(1);}
		if (smem1[tag_address.read()] == masked_tag_value) { set_match.write( set_match.read() | 0b0010); hit.write(1);}
		if (smem2[tag_address.read()] == masked_tag_value) { set_match.write( set_match.read() | 0b0100); hit.write(1);}
		if (smem3[tag_address.read()] == masked_tag_value) { set_match.write( set_match.read() | 0b1000); hit.write(1);}
	}
}

void tag_memory::write_setmemory() {
	if(ce && !no_write) {
//We already asserted zero_one_hot on set_we so write and  return on the first successful match
		if(set_we.read() == 1) { smem0[tag_address.read()] = masked_tag_value;return;}
		if(set_we.read() == 2) { smem1[tag_address.read()] = masked_tag_value;return;}
		if(set_we.read() == 4) { smem2[tag_address.read()] = masked_tag_value;return;}
		if(set_we.read() == 8) { smem3[tag_address.read()] = masked_tag_value;return;}
	}
}
