//rune18.c

// Ko 科

#include <ansi.h>

inherit ITEM;

int is_rune_ob() { return 1; }
int is_enchase_ob() { return 1; } 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune ko", "rune18", "rune"}));
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：科(KO)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 18);
                set("enchase/type", "all");
                set("enchase/cur_firm", 100); 
                set("enchase/wspe_data", ([
                        "add_fire"     : 30,               
                ]));
                set("enchase/aspe_data", ([
                        "avoid_fire"   : 10,     
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

