// SN:^g<TNS@AiHPm0KS<
//  Written by ZHANG TIANSHI(Lonely 2007/10/15)	Wed May 27 13:26:25 2009
#include <ansi.h>
inherit ITEM;

int is_enchase_ob(){ return 1; }

void create()
{
	set_name(BLU "神之宝石" NOR, ({ "BLU jewel7" }));
	set_weight(50);
	set("unit", "块");
	set("long", BLU "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR );
	set("value", 200000);
	set("can_be_enchased", 1);
	set("magic/type", "magic");
	set("magic/power", 17);
	set("enchase/SN", 1);
	set("enchase/level", 7);
	set("enchase/cur_firm", 94);
	set("enchase/wspe_data", ([
		"max_neili" : 4000,
		"attack" : 40,
		"add_magic" : 23,
		"learn_effect" : 7,
		"max_potential" : 400000,
		"attack" : 40,
		"add_cold" : 23,
	]));
	set("enchase/aspe_data", ([
		"reduce_fire" : 23,
		"avoid_fire" : 7,
		"derive_times" : 7,
		"con" : 8,
		"derive_times" : 7,
		"practice_times" : 7,
		"armor" : 800,
	]));
	set("wear_msg", HIC "$N" HIC "轻轻地把$n"HIC "戴在头上。\n" NOR);
	set("remove_msg", HIC "$N" HIC "轻轻地把$n"HIC "从头上摘了下来。\n" NOR);

	setup();
}

int query_autoload(){ return 1; }
