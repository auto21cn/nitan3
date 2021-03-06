// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;
inherit F_VENDOR;

int ask_me();
int do_sell(string arg);
int do_hit(string arg);

void create()
{
        set_name( "冯铁匠" ,({ "feng tiejiang", "feng", "smith" }));
        set("gender", "男性");
        set("age", 39);
        set("long", "冯铁匠想是常年弯腰打铁，背已驼了，双眼被烟火薰的又红又细，\n"
                    "左腿残废，肩窝下撑著一根拐杖。\n");
        /*          "冯默风是黄药师最小的一个徒弟，他的根基不错，但性子\n"
                    "较为愚鲁。他的基本功扎实，一副忠厚老实的样子。\n");
        */
        set("attitude", "friendly");
        set("class", "scholar");
        set("str", 30);
        set("int", 24);
        set("con", 27);
        set("dex", 23);
        set("shen_type",1);
        set("max_qi", 4200);
        set("max_jing", 2100);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 800000);

        set_skill("force", 180);
        set_skill("bibo-shengong", 180);
        set_skill("unarmed", 160);
        set_skill("xuanfeng-tui", 160);
        set_skill("strike", 160);
        set_skill("luoying-shenzhang", 160);
        set_skill("finger", 140);
        set_skill("tanzhi-shentong", 140);
        set_skill("dodge", 160);
        set_skill("luoying-shenfa", 160);
        set_skill("parry", 160);
        set_skill("sword", 160);
        set_skill("luoying-shenjian", 160);
        set_skill("literate", 140);
        set_skill("martial-cognize", 140);

        map_skill("force", "bibo-shengong");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "luoying-shenzhang");
        map_skill("finger", "tanzhi-shentong");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "luoying-shenjian");
        map_skill("sword", "luoying-shenjian");

        prepare_skill("unarmed", "xuanfeng-tui");
        prepare_skill("strike", "luoying-shenzhang");

        // create_family("桃花岛", 2, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sui" :),
                (: perform_action, "finger.jinglei" :),
                (: perform_action, "strike.qimen" :),
                (: perform_action, "unarmed.kuang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        
        /*
        set("chat_chance", 1);
        set("chat_msg", ({
                CYN "冯默风说道：师父疼爱小师妹，他的软猬甲一直由小师妹穿着。\n" NOR,
                CYN "冯默风自言自语地说道：家师所布置的这个桃花阵真是不简单！\n" NOR,
        }));
        */

        set("vendor_goods", ({
                "/d/village/npc/obj/hammer",
		"/clone/weapon/gangdao",
        }));
        
        set("inquiry", ([
                /*
                "拜师" : (: ask_me :),
                "投师" : (: ask_me :),
                "东邪" : "家师人称东邪！呵呵。",
                "西毒" : "欧阳锋是与家师并世齐名的高手，人称老毒物。",
                "南帝" : "听家师说段王爷现在出家当了和尚，法名一灯。",
                "北丐" : "北丐洪七公是丐帮帮主，现在扬州城外。",
                "黄蓉" : "她是师父的爱女。",
                "黄药师" : "你要拜访家师？",
                "桃花岛" : "这儿就是桃花岛，你若不是本派弟子，要过桃花阵。",
                "桃花阵" : "往南就是了。",
                "碧浪滔天" : (: ask_skill1 :),
                */
                "name"    : "小人姓冯，村里人都叫我冯铁匠。",
		"here"    : "这里是小人糊口的铺子，小人就住在後边的屋子。",
		"锄头"    : "锄头... 抱歉，锄头已经卖光了...",
		"铁锤"    : "铁锤？小人做的铁锤坚固又耐用，一把只要三百文钱。",
		"剑"      : "哦，那是给华山派岳掌门打的，小人用了三个月，总算没浪费那块好铁。\n"
                            "嗯，岳掌门前不久率门徒下山去了，不知什麽时候才会派人来取剑。",
		"取剑"    : "小人一定要见了岳掌门的手信才能给剑。",
		"冯默风"  : "唉～，这个名字小人已经好久没有听到过了...",
		"奇门遁甲": "那都是小时候学的，平时没事解解闷罢了。",
		"工作"    : (: ask_me :),
		"打铁"    : (: ask_me :),
        ]));
        set("master_ob", 4);
	setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/village/npc/obj/hothammer")->wield();
}

void init()
{
        ::init();
        add_action("do_buy", "buy");
	add_action("do_list", "list");
	add_action("do_sell", "sell");
	add_action("do_hit", "hit");
	add_action("do_hit", "da");
}

int ask_me()
{
	say("冯铁匠咳了一声，说道：想干活？好！不过我这里废铁不够了，你先去找几十斤废铁来吧。\n");
	this_player()->set_temp("marks/铁", 1);
	return 1;
}	

int accept_object(object who, object ob)
{
	object sword;
        if ((string)ob->query("name") == "手信" && 
            (string)ob->query("id") == "letter" && ! userp(ob)) 
        {
                if (! query("yl_trigger")) 
                {
	                sword = new(__DIR__"obj/youlong");
                        if (! sword)
                        {
                                say("冯铁匠说道：那剑早被拿走了，怎麽又来一封信，一定是假的。\n");
	                        call_out("destroy", 1, ob);
	                        return 1;
	                }
		        say(
                            "冯铁匠说道：这把剑虽不起眼，可也是小人的心血，总算对得起岳掌门。\n"
                            "冯铁匠把" + sword->query("name") + "交给了" + who->query("name") + "。\n");
		        sword->move(who);
		        command ("rumor " + who->query("name") + "弄到了一柄游龙剑。");
                        set("yl_trigger", 1);
                } else 
                        say("冯铁匠眼也不抬，说道：要剑自己进去拿。\n");
                call_out("destroy", 1, ob);
	        return 1;
	}

        if ((string)ob->query("name") == "铁八卦") 
        {
		if (! query("accept_bagua")) 
		        return 0;
		call_out("accept_obj", 2, who, ob);
		return 1;
	}
	return 0;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

int accept_obj(object me, object obj)
{
        if (obj->query("name") == "铁八卦") 
        {
	        message_vision(CYN "$N摩挲着铁八卦，渐渐热泪盈眶！\n" NOR, this_object());
	        command("cry");
	        command("say 默风不肖，累师傅担忧，同门牵挂，有劳" + RANK_D->query_respect(me) + "了。\n");
	        me->set("help_mofeng", 1);
	}
	return 1;
}

int do_sell(string arg)
{
        object ob;

        if (! arg || ! (ob = present(arg, this_player())))
                return notify_fail("你要卖什么？\n");

        if (ob->query("material") != "steel" && ob->query("material") != "iron")
                return notify_fail("我这里只收废铁。\n");

        else {
                message_vision("$N卖掉了一" + ob->query("unit") +
                ob->query("name") + "给$n。\n", this_player(), this_object());
                MONEY_D->pay_player(this_player(), ob->query_weight() / 70);
                destruct(ob);
        }
	return 1;
}
int do_hit(string arg)
{
	object ob, weapon,  me = this_player();
	string file;
	
	if (! arg || ! (ob = present(arg, this_player()))
	||  me->query_temp("marks/铁") < 1)
                return notify_fail("你要干什么？\n");
                
	if (ob->query("material") != "steel" && ob->query("material") != "iron"
	||  ob->query("value") > 0) 
                return notify_fail("你还是找一块废铁来打吧。\n");
                
	if (! objectp(weapon = me->query_temp("weapon"))
        ||  (string)weapon->query("skill_type") != "hammer")
                return notify_fail("没有合适的家伙，你怎麽打铁？\n");
                
        if ((int)me->query("jing") < 50)
                return notify_fail("你的精气太低了，歇一会吧。\n");

	if (ob->weight() < 300)
	{
	        file = resolve_path(this_object()->query("cwd"), arg);
	        file = base_name(ob) + ".c";
	        destruct(ob);
                ob = new(file);
	        message_vision("不一会儿，你便打好了一"  + ob->query("unit") + ob->query("name") +
	                       "交给冯铁匠。\n", me);
	        command("thumb " + me->query("id"));
	        command("say " + RANK_D->query_respect(me) + "如此勤勉，日後必成一位大铁匠。");	
	        message_vision("冯铁匠给$N几文铜板工钱。\n", me);
	        MONEY_D->pay_player(this_player(), ob->query_weight() / 100);
	        destruct(ob);
	        return 1;
	}

	message_vision("$N把一" + ob->query("unit") + ob->query("name") + 
	               "扔进火炉烧红了箝了出来。\n", me);
	               
	message_vision("$N然後高高举起" + weapon->query("name") + "热火朝天地打起铁来。\n", me);
	
	me->recieve_damage("jing", -30);
	
        if ((int)me->query_skill("hammer",1) <= 100) 
        {
                me->improve_skill("hammer", 1);
                tell_object(me, "你的基本锤法进步了。\n");
	        ob->set_weight(ob->weight() - 10 * me->query("str"));
                if ((string)weapon->query("id") == "liuxing chui") 	
	        me->improve_skill("hammer", me->query("int"));
	        return 1;
	}
}

void unconcious()
{
	object obj;

	if (! query("revived"))  
	{
                set("eff_jing", (int)query("max_jing"));
                set("jing", (int)query("max_jing"));
                set("jingli", (int)query("max_jingli"));
                set("eff_qi", (int)query("max_qi"));
                set("qi", (int)query("max_qi"));
                set("neili", (int)query("max_neili"));	
                map_skill("strike", "luoying-shenzhang");
                map_skill("dodge", "luoying-shenfa");
                prepare_skill("strike", "luoying-shenzhang");
	        set("revived", 1);
	        message_vision(HIW "$N大喝一声，身形突然变得灵动异常，出手招式也大不相同！\n" NOR,
	                       this_object());
	
	        if (objectp(obj = query_last_damage_from())) 
	        {
		        if (present(obj->query("id"), environment(this_object()))) 
		        {
		                this_object()->fight_ob(obj);
		                if (obj->query("family/family_name") == "桃花岛")
		                        call_out("halt_fight", 5 + random(10), obj);
		        }
	        }
	        return 0;
	} else 
	::unconcious();
}

void halt_fight(object me)
{
	
        if (this_object()->is_fighting()) 
        {
        	this_object()->remove_all_enemy();
		me->remove_all_enemy();
	}
	message_vision(CYN "$N哈哈大笑道：冯默风，你所用功夫全是我桃花一派，难道你还要装下去吗？！\n" NOR, me);
	message_vision(CYN "$N一楞，手下不由得慢了下来，向后一跃，跳出战圈不打了。\n" NOR, this_object());
	message_vision(CYN "$N长叹一声，道：不想我冯默风有生之年还能见到桃花同门，不知恩师他老人家近来可好？\n",
	               this_object());
	this_object()->set("accept_bagua", 1);
}

/*
void attempt_apprentice(object ob)
{
        string master;
        if (! permit_recruit(ob))
                return;
        
        if (stringp(master = ob->query_temp("taohua/master")))
        {
                if (master != name())
                {
                        command("say 家师不是让你拜" + master + "的吗？你怎么来"
                                "找我来了？");
                        return;
                }

                command("say 好吧，既然家师有令，我就收下你了，不过要好好遵守桃"
                        "花岛的规矩。");
                command("recruit " + ob->query("id"));
                ob->delete_temp("taohua/master");
                return;
        }

        command("shake");
        command("say 我可不敢擅自收徒，你还是找家师黄岛主吧！");
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if (me->query("can_perform/canglang-zhi/tao"))
                return "这一招我不是已经教过你了吗？";

        if (me->query("family/family_name") != query("family/family_name"))
                return "你不是我们桃花岛的人，问这个干嘛？";

        if (me->query_skill("canglang-zhi", 1) < 1)
                return "你连沧浪指法都没学，还谈什么绝招可言？";

        if (me->query("family/gongji") < 50)
                return "师父吩咐过，不传功给无功劳的弟子。";

        if (me->query_skill("force") < 120)
                return "你的内功修为不够，还是多锻炼锻炼吧。";

        if (me->query_skill("canglang-zhi", 1) < 80)
                return "你的沧浪指法还不够熟练，练高了再来找我。";

        message_sort(HIY "\n$n" HIY "点了点头，道：“既然家师吩咐过，今日我就"
                     "传你这招，可要看好了。”说完只见$n" HIY "陡然伸出一指，"
                     "纷翻不定，顿听指气嗤然作响，全全笼罩$N" HIY "四周。\n\n"
                     NOR, me, this_object());

        command("nod");
        command("say 看懂了吗？");
        tell_object(me, HIC "你学会了「碧浪滔天」。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("canglang-zhi"))
                me->improve_skill("canglang-zhi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/canglang-zhi/tao", 1);
        me->add("family/gongji", -50);

        return 1;
}

mixed ask_me()
{
        object me;
        me = this_player();

        if (me->query("family/family_name"))
        {
                if (me->query("family/family_name") != "桃花岛")
                {
                        command("say 阁下已有门派，家师是不会收留你的，请走吧！");
                        return 1;
                }

                if (me->query("family/master_name"))
                {
                        command("say 你不是已经入了我们桃花岛吗？");
                        return 1;
                }
        }

        if (me->query("detach/桃花岛"))
        {
                command("say 当年你离开了桃花岛，今天还敢回来见家师？");
                return 1;
        }

        if (me->query("betrayer/times"))
        {
                command("say 你这判师之人，家师是绝对不会收你为徒的！");
                return 1;
        }
        command("say 好吧，我带你过桃花阵，你自己去找黄岛主吧。");
        message_vision(HIW "\n$N" HIW "大步的向南走去，$n" HIW "紧随其后。\n\n" NOR,
                       this_object(), me);
        this_object()->move("/d/taohua/damen");
        me->move("/d/taohua/damen");
        command("say 好了，我带你到大门，你进去就可以见到家师。");
        message_vision("$N头也不回的往北面离去。\n", this_object());
        this_object()->move(query("startroom"));
        message_vision("$N急匆匆的走了过来。\n", this_object());
        return 1;
}
*/
