#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(HIG "宝石" NOR, ({ "GRN jewel2","jewel2" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "一颗绿光闪闪的精美宝石，华丽异常。\n" NOR);
                set("unit", "块");
                set("value", 100000);
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


                        "int" : 2,           // 增加智慧

                        ////////////////////     兵器特有属性

                        "suck_jingli"   : 6, // 吸取精力
                        "suck_eff_jing" : 6, // 伤敌精力上限
                        "damage" : 20,       // 兵器伤害：+20

                   ]));

                set("enchase/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "int" : 2,           // 增加智慧

                        ////////////////////     防具特有属性

                        "armor"  : 20,       // 防御能力：+20
                        "eff_jing"      : 2, // 精气上限：+2%
                        "max_jingli"    : 6, // 精力上限：+6%

                        "jing_recover_speed"   : 10, // 精气恢复速度: +10%
                        "jingli_recover_speed" : 4, // 精力恢复速度：+4%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}

