#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(HIG "宝石碎片" NOR, ({ "GRN jewel1","jewel1" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "一片绿色的宝石碎片。\n" NOR);
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


                        "int" : 1,           // 增加智慧

                        ////////////////////     兵器特有属性

                        "suck_jingli"   : 3, // 吸取精力
                        "suck_eff_jing" : 3, // 伤敌精力上限
                        "damage" : 10,       // 兵器伤害：+10

                   ]));

                set("enchase/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "int" : 1,           // 增加智慧

                        ////////////////////     防具特有属性

                        "armor"  : 10,       // 防御能力：+10
                        "eff_jing"      : 1, // 精气上限：+1%
                        "max_jingli"    : 3, // 精力上限：+3%

                        "jing_recover_speed"   : 5, // 精气恢复速度: +5%
                        "jingli_recover_speed" : 2, // 精力恢复速度：+2%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}

