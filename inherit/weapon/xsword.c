// xsword.c

#include <weapon.h>
#include <music.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

inherit MI_XIAO;

varargs void init_xsword(int damage, int flag)
{
	if( clonep(this_object()) ) return;

	set("weapon_prop/damage", damage * 90 / 100);
	set("flag", (int)flag | EDGED);
	set("skill_type", "sword");
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "slash", "slice", "thrust" }) );
	}
}

void init()
{
        add_action("play_xiao", "play");
}

string extra_long()
{
        string str;
        
        str =  "物品类型    ：    兵器\n";
        str += "属    性    ：    萧\n";
        str += sprintf("攻    击    ：    %d\n", query("weapon_prop/damage"));
        str += sprintf("重    量    ：    %d\n", this_object()->query_weight());
        str += sprintf("杀    戮    ：    %d\n", query("combat/PKS"));
        str += sprintf("使用方式    ：    输入指令 wield %s 装备。\n", query("id"));
        str += sprintf("                  输入指令 unwield %s 卸下。\n", query("id"));
        if (this_object()->query_autoload())
                str += "下线丢失    ：    否\n";
        else
                str += "下线丢失    ：    是\n";
        return str;
}
