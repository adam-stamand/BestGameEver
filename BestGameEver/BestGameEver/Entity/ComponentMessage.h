#pragma once


enum FuncID {
	GET_POS,
	SET_POS,
	SET_VEL,
	ADD_VEL
};


struct ComponentMessage {
	int func_ID;
	void *params;
};

struct Position {
	float x;
	float y;
};

struct Velocity {
	float x;
	float y;
};