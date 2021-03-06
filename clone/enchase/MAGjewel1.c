#include <ansi.h>
inherit ITEM;
int is_enchase_ob() { return 1; }
void create()
{
        set_name(MAG "宝石碎片" NOR, ({ "MAG jewel1","jewel1" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "一片紫色的宝石碎片。\n" NOR);
                set("unit", "片");
                set("value", 80000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
                    
                set("enchase/type", "all");   // 可镶嵌的道具类型"all"或"sword"或"blade"或"cloth"等
                set("enchase/cur_firm", 90);  // 抗磨损度
                set("enchase/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                        "con" : 1,           // 增加身法

                        ////////////////////     兵器特有属性

                        "perferm_ap"    : 1,  // 绝招命中：+5%
                        "suck_eff_jing" : 3, // 伤敌精力上限
                        "suck_jingli"   : 3, // 吸取精力
                        "suck_neili"    : 3, // 吸取内力3

                   ]));

                set("enchase/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "con" : 1,           // 增加身法

                        ////////////////////     防具特有属性

                        "defense": 10,       // 防御等级：+10
                        "armor"  : 10,       // 防御能力：+10
                        "perform_dp"    : 1,  // 绝招防御：+1%
                        "reduce_damage" : 5, // 化解伤害：5%
                        "reduce_busy"   : 5, // 化解忙乱：5%

                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}


