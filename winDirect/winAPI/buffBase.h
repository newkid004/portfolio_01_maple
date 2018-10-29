#pragma once
#include "state.h"
class buffBase
{
protected:
	string			_name;
	string			_explain;

	int				_lv;
	
	NUM_REAL		_aliveTime;


	statePoint		_adjustStatePoint;
	stateBasic		_adjustStateBasic;

public:
	virtual HRESULT		init();
	virtual void		release();
	virtual void		render();
	buffBase() {};
	~buffBase() {};
};

