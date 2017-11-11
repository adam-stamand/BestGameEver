#pragma once


enum FuncID {
	GET_POS,
	SET_POS,
	SET_VEL,
	ADD_VEL,
	APPLY_FORCE,
	ROTATE
};



struct ComponentMessage {
	int func_ID;
	void *params;
};


struct EntityMessage {
	int comp_ID;
	ComponentMessage *comp_msg;
};


