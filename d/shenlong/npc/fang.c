// fangyi.c  方怡
#include <ansi.h>

inherit NPC;
// inherit F_MASTER;

int do_work();
string *fjob = ({"毒蛇", "腹蛇", "金环蛇", "水蛇", "银环蛇", "竹叶青蛇"});

void create()
{
        set_name("方怡", ({ "fang yi","fang" }));
//      set("nickname", "");
        set("title",HIY"神龙教"HIR"赤龙使"NOR"座下弟子");
        set("long",
                "一张瓜子脸，容貌甚美。\n");
        set("gender", "女性");
        set("age", 18);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 23);
        set("int", 25);
        set("con", 25);
        set("dex", 26);
        set("max_qi", 600);
        set("max_jing", 600);
        set("neili", 600);
        set("max_neili", 600);
        set("jingli", 600);
        set("max_jingli", 600);
        set("jiali", 30);
        set("combat_exp", 50000);
//      set("score", 50000);
//      set("shen", -3000);

        set_skill("force", 30);
        set_skill("shenlong-xinfa", 20);
        set_skill("dodge", 40);
        set_skill("yixingbu", 60);
        set_skill("strike", 30);
        set_skill("parry", 40);
        set_skill("sword", 50);
        set_skill("literate", 40);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixingbu");
        

        set("inquiry", ([
                "教主" : (: do_work :),
                "神龙教" : (: do_work :),
                "jiao" : (: do_work :),
                    "work" : (: do_work :),
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/shenlong/obj/zhutong");

}

void init()
{
        add_action("do_comfort", "comfort");
}


int do_work()
{
        object me = this_player();
        string fword, fwant;
        object ob;

        if( me->query("family/family_name") != "神龙教" ) {
                say("方怡哼了一声说：假仁假义的东西，还不给我滚！\n");
                return 1;
        }

        if( me->query_temp("sg/方a") ) {
                say("方怡不耐烦地说道：有完没完了？\n");
                return 1;
        }

        if( time() < (int)me->query("sg/方t") + 180 ) {
                command("slap " + me->query("id"));
                say("方怡大怒道：蠢猪，这么快就忘了！\n");
                return 1;
        }

        me->set_temp("sg/方a", 1);
        me->set("sg/方t", time());

        fwant = fjob[random(sizeof(fjob))];
        fword = sprintf("方怡叹了口气，说道：奉教主之命，捉%s来配药。\n", fwant);
        say(fword);
        me->set_temp("sg/毒蛇", fwant);
        ob = new("/d/shenlong/obj/zhutong");
        if (! ob->move(me))
                ob->move(environment(me));
        tell_object(me, HIM "你获得了一" + ob->query("unit") + ob->name() +
                    HIM "。\n" NOR);
        return 1;
}

int do_comfort(string arg)
{
        object me = this_player();

        if( !arg || !(arg == "fang yi" || arg == "fang") )
                return notify_fail("你要安慰谁？\n");

        message_vision("$N笑嘻嘻地安慰着方怡。\n", me);

        if( !me->query_temp("sg/方a") )  {
                say("方怡冷笑道：别假惺惺了。\n");
                return 1;
        }

        me->delete_temp("sg/方a");

        message_vision("$N道：方姑娘，请放心！我这就给你去抓。\n", me);
        command("thank " + me->query("id"));
        me->set_temp("sg/方b", 1);

        return 1;
}

int accept_object(object who, object ob)
{
        int expgain, faccept,reward;

        if( !who->query_temp("sg/方b") )
                return 0;

        if( ob->query("name") != who->query_temp("sg/毒蛇")
        ||  (strsrch(base_name(ob), "/d/shenlong/npc/") != 0) )  {
                command("angry " + who->query("id"));
                command("disapp " + who->query("id"));
                return 0;
        }

        who->delete_temp("sg/方b");
        who->delete_temp("sg/毒蛇");

        call_out("destroy_it", 1, ob);

        command("jump " + who->query("id"));
        
        message_vision("方怡在$N耳边悄悄的说了几句话。\n", who);
        if( who->query_skill("medical", 1) < 30 )
        {        who->improve_skill("medical", random(2 * who->query("int")));
                tell_object(who,"听了方怡的话，你似乎对医术有进一步的领悟。\n");
                return 1;
         }      
        if( (expgain = who->query("combat_exp")) > 50000 )
                 return 1;
   
        expgain = (50000 - expgain) / 400;
        reward=random(expgain)/2;
        who->add("combat_exp", reward);
        tell_object(who,"你得到了"+chinese_number(reward)+"点经验。\n");
        expgain /= 3;
        who->add("potential", reward/3);
        if( who->query("potential") > who->query("max_potential") )
        who->set("potential", who->query("max_potential"));
        tell_object(who,"你得到了"+chinese_number(reward/3)+"点潜能。\n");
        return 1;              
}

void destroy_it(object ob)
{
        if(ob)
        destruct (ob);
}

