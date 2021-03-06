#include <ansi.h>
inherit ITEM;
// by dream

int is_enchase_ob() { return 1; } 

void create()
{
        set_name("神之宝石", ({ "BLK jewel7","jewel7" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一块闪烁这奇异光芒的黑色宝石，"
                    "让人感到一阵阵的心悸。\n");
                set("unit", "块");
                set("value", 200000);
		set("no_identify", 1); 

                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
		
		set("enchase/SN", 2);
                set("can_be_enchased", 1);    // 只有最高等级的宝石才有此标志
		set("magic/type", "magic"); 
		set("magic/power", 15 + random(16));                     
                set("magic/cur_firm", 90);  // 抗磨损度
                
                set("magic/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                          "str" : 10,           // 增加膂力

                        ////////////////////     兵器特有属性

                        "poison_attack" : 90, // 毒焰攻击
                        "draw_dragon"   : 1,  // 召唤神龙
                        "xuruo_status"  : 3,  // 战力削弱(虚弱)1秒

                   ]));

                set("magic/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性
 
                          "str" : 10,           // 增加膂力

                        ////////////////////     防具特有属性

                        "reduce_poison" : 90, // 抗毒效果：90%
                        "avoid_poison"  : 90, // 毒性回避：90%
                        "reduce_damage" : 50, // 化解伤害：50%
                        "reduce_busy"   : 50, // 化解忙乱：50%
                        "reduce_poison" : 90, // 抗毒效果：90%
                        "parry"  : 100,       // 招架等级：+100

                   ]));
                   
        }
        setup();
}

int query_autoload()
{
        return 1;
}


