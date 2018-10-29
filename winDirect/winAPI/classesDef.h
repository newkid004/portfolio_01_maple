#pragma once

namespace classesDef
{
	enum class CLASSES
	{
		CLASSES_GLOBAL				= 0x100000,
		CLASSES_WARRIER				= 0x000001,
		CLASSES_WIZARD				= 0x000002,
		CLASSES_THIEF				= 0x000004,
		CLASSES_ARCHER				= 0x000008,
	};

	enum CLASSES_TYPE
	{
		//초보자
		CLASSES_TYPE_GLOBAL			= 0x100000,		
		
		//1차
		CLASSES_TYPE_WARRIER		= 0x0001,
		CLASSES_TYPE_WIZARD			= 0x0002,	
		CLASSES_TYPE_THIEF			= 0x0004,
		CLASSES_TYPE_ARCHER			= 0x0008,

		//2차
		CLASSES_TYPE_FIGHTER		= 0x0011,			
		CLASSES_TYPE_PAGE			= 0x0021,
		CLASSES_TYPE_SPEARMAN		= 0x0041,

		CLASSES_TYPE_ICEWIZARD		= 0x0012,
		CLASSES_TYPE_FIREWIZARD		= 0x0022,
		CLASSES_TYPE_CLELIC			= 0x0042,

		CLASSES_TYPE_ASSASSIN		= 0x0014,
		CLASSES_TYPE_SHIF			= 0x0024,

		CLASSES_TYPE_HUNTER			= 0x0018,
		CLASSES_TYPE_SHSU			= 0x0028,

		//3차
		CLASSES_TYPE_CRUSADER		= 0x0111,
		CLASSES_TYPE_KNIGHT			= 0x0221,
		CLASSES_TYPE_BERSERKR		= 0x0441,
										 
		CLASSES_TYPE_ICEMAGE		= 0x0112,
		CLASSES_TYPE_FIREMAGE		= 0x0222,
		CLASSES_TYPE_PRIST			= 0x0442,
										
		CLASSES_TYPE_HERMIT			= 0x0114,
		CLASSES_TYPE_SHIFMASTER		= 0x0224,
										 
		CLASSES_TYPE_RANGER			= 0x0118,
		CLASSES_TYPE_SNIPER			= 0x0228,
										 
		//4차							  
		CLASSES_TYPE_HERO			= 0x1111,
		CLASSES_TYPE_PLLADIN		= 0x2221,
		CLASSES_TYPE_DARKNIGHT		= 0x4441, 

		CLASSES_TYPE_ICEARKMAGE		= 0x1112,
		CLASSES_TYPE_FIREARKMAGE	= 0x2222,
		CLASSES_TYPE_BISHOP			= 0x4442,
									  
		CLASSES_TYPE_NIGHTRODE		= 0x1114,
		CLASSES_TYPE_SHADOR			= 0x2224,
									  
		CLASSES_TYPE_BOWMASTER		= 0x1118,
		CLASSES_TYPE_GODBOW			= 0x2228

	};
}