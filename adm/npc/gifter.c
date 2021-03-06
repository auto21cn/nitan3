// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit NPC;

mixed ask_gift();

void create()
{
        set_name(HIM "礼物天使" NOR, ({ "gift angel", "liwu tianshi" }));
        set("long", @LONG
礼物天使，负责泥潭节庆期间礼物发放的天使。
LONG);
        set("gender", "女性" );
        set("age", 18);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);

        set("inquiry", ([        
                "礼物" : (: ask_gift :),  
                "gift" : (: ask_gift :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}

mixed ask_gift()
{
        object ob, me = this_player();
        string *lines, file, gift;
        int time1, time2;
        
        file = read_file(CONFIG_DIR + "gift");
        if (! stringp(file)) 
        {
                command("say 可惜，天神还没有打算做任务礼物呢！");
                return 1;
        }
        
        lines = explode(file, "\n");
        file = lines[sizeof(lines) -1];
        
        if (sscanf(file, "%s %d to %d", gift, time1, time2) != 3)
        {
                command("say 奇怪，礼物怎么不见了，难道是天神在作怪？！");
                return 1;
        }
        
        if ((int)me->query("gifter/" + time1))
        {
                command("say 呵呵～这就是您的不是了！我已经给过您礼物了啊！");
                return 1;
        }
        
        if (time() < time1 || time() > time2)
        {
                command("say 对不起，你来的不是时候，现在送你礼物，天神会惩罚我的！");
                return 1;
        }
        
        if (! ob = new(gift)) 
        {
                 command("say 奇怪，礼物有大问题，你赶快和天神报告吧！");  
                 return 1;
        } else
        {
                me->set("gifter/" + time1, 1);
                ob->move(me, 1); 
                                      
                message_vision(HIW "$N" HIW "凌空一指，突然天空中一道" HIM "七" HIY "彩" HIR "霞" HIC "光" HIW "笼罩$n，转瞬即逝！\n" NOR, 
                               this_object(), me);
                               
                tell_object(me, HIG "你身上好象多了一个礼物（gift），你快看看是什么礼物吧。\n" NOR);
                return 1;
        }
}
