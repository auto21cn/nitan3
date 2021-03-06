#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(HIG "稀世宝石" NOR, ({ "GRN jewel3","jewel3" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "一颗绿光闪闪的精美宝石，给人以不同寻常的感觉。\n" NOR);
                set("unit", "块");
                set("value", 120000);
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


                        "int" : 3,           // 增加智慧

                        ////////////////////     兵器特有属性

                        "suck_jingli"   : 10, // 吸取精力
                        "suck_eff_jing" : 10, // 伤敌精力上限
                        "damage" : 30,       // 兵器伤害：+30

                   ]));

                set("enchase/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "int" : 3,           // 增加智慧

                        ////////////////////     防具特有属性

                        "armor"  : 30,       // 防御能力：+30
                        "eff_jing"      : 3, // 精气上限：+3%
                        "max_jingli"    : 10, // 精力上限：+10%

                        "jing_recover_speed"   : 15, // 精气恢复速度: +15%
                        "jingli_recover_speed" : 8, // 精力恢复速度：+8%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}

