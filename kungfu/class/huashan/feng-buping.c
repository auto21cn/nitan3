// Copyright (C) 4003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// feng-buping.c  封不平

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "jianzong.h"

mixed ask_feilong();
mixed ask_sanxian();
string ask_me();

void create()
{
        set_name("封不平", ({ "feng buping", "feng" }) );
        set("gender", "男性");
        set("class", "swordsman");
        set("title", "华山剑宗第十三代弟子");
        set("age", 45);
        set("long", "封不平是华山剑宗第一高手，满脸戾气一张黄焦焦的面皮。\n");
        set("attitude", "peaceful");
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 29);

        set("max_qi", 6300);
        set("max_jing", 4000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 3000000);
        set("shen_type", -1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.long" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "strike.piao" :),
                (: perform_action, "cuff.song" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("unarmed", 400);
        set_skill("cuff", 400);
        set_skill("strike", 400);
        set_skill("hunyuan-zhang", 400);
        set_skill("sword", 400);
        set_skill("force", 400);
        set_skill("parry", 400);
        set_skill("dodge", 400);
        set_skill("literate", 400);
        set_skill("huashan-jianfa", 400);
        set_skill("kuangfeng-jian", 400);
        set_skill("huashan-neigong", 400);
        set_skill("huashan-quanfa", 400);
        set_skill("poyu-quan", 400);
        set_skill("huashan-shenfa", 400);
        set_skill("martial-cognize", 400); 

        map_skill("sword", "huashan-jianfa");
        map_skill("parry", "huashan-jianfa");
        map_skill("force", "huashan-neigong");
        map_skill("strike", "hunyuan-zhang");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("cuff", "poyu-quan");
        map_skill("dodge", "huashan-shenfa");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");
        
        set("no_teach", ([
                // "kuangfeng-jian" : "你想学的话还是找我成师弟吧！\n",
        ]));
        
        set("inquiry", ([
                "绝招"     : "我剑宗剑法精奇，你想学哪门绝招？\n",
                "绝技"     : "我剑宗剑法精奇，你想学哪门绝招？\n",
                "剑宗"     : "我就是剑宗传人！\n",
                "狂风快剑" : "你想学的话还是找我成师弟吧！\n",
        	"气宗"     : "哼！气宗武功庸俗不堪，奉气轻剑，乱七八糟。\n",
	        "岳不群"   : "别提那伪君子！可恶！\n",
	        "华山剑法" : "那便是本派绝学，天下一等一的剑法！尤其是「天外飞龙」一招，飞剑杀敌，无人能挡。\n",
	        "风清扬"   : "啊！我已多年不见风师叔，不清楚他的下落。\n",
	        "天外飞龙" : (: ask_me :),
        ]));

        set_temp("apply/attack", 220);
        set_temp("apply/defense", 220);
        set_temp("apply/damage", 400);
        set_temp("apply/unarmed_damage", 400);

        create_family("华山剑宗", 13, "弟子");

        set("master_ob",4);
	setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_ask(object me, string topic)
{
        if (me->query("family/family_name") != "华山剑宗")
                return 0;

        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;
                                
        case "风起云涌" :
                if (me->query("max_neili") > 1000000 || me->query_skill("force") > 1000)
                {
                      command("shake");
                      command("say 我剑宗以剑术为主，气为次！你的内功修为已入了气宗歧途，再不能修炼剑宗剑术。");
                      return 1;
                }
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuangfeng-jian/yong",
                           "name"    : "风起云涌",
                           "sk1"     : "kuangfeng-jian",
                           "lv1"     : 140,
                           "gongxian": 800,
                           "sk2"     : "dodge",
                           "lv2"     : 140, ]));
                break;

        case "夺命连环三仙剑" :
                if (me->query("max_neili") > 1000000 || me->query_skill("force") > 1000)
                {
                      command("shake");
                      command("say 我剑宗以剑术为主，气为次！你的内功修为已入了气宗歧途，再不能修炼剑宗剑术。");
                      return 1;
                }
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-jianfa/xian",
                           "name"    : "夺命连环三仙剑",
                           "sk1"     : "huashan-jianfa",
                           "lv1"     : 160,
                           "free"    : 1,
                           "gongxian": 1000,
                           "sk2"     : "dodge",
                           "lv2"     : 160, ]));
                break;

        default:
                return 0;
        }
}

void attempt_apprentice(object ob)
{
        if (query("apprentice_available")) 
        {
                if (find_call_out("do_recruit") != -1)
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } else 
        {
                command("say 老夫今天已经收了三个弟子，不想再收徒了。");
        }
}

void do_recruit(object ob)
{
        if ((int)ob->query("int") < 20)
                command("say 我华山派以剑法为主，依我看" + RANK_D->query_respect(ob) + "不适合于学剑法。");
        else 
        {
                command("say 好，好，好，很好。");
                command("recruit " + ob->query("id") );
        }
}

int recruit_apprentice(object ob)
{
        if (::recruit_apprentice(ob))
        {
                ob->set("title", "华山剑宗第十四代弟子");
                ob->set("class", "swordman");
        }
        add("apprentice_availavble", -1);
}

void reset()
{
        set("apprentice_available", 3);
}

// 下面的是方便气宗的弟子学习天外飞龙，剑宗的直接找成不忧询问
string ask_me()
{
	object ob = this_player(), me = this_object();
	mapping obfam;
	
	obfam = (mapping)ob->query("family");

	if (! obfam || obfam["family_name"] != "华山派") 
	{
	        if (obfam && obfam["family_name"] == "华山剑宗")
	        {
	                return "你还是找我的师弟成不忧吧。\n";
	        }
	        
	        if (ob->query_temp("feilong") < 3) 
	        {
		        command( "sneer" );
		        ob->add_temp("feilong", 1);
		        return "咱们豪无渊源，你问这做什么？还是别太好奇的好。\n";
	        }
	        else 
	        {
		        message_vision("$N脸色微变，目中阴鹭一闪，发出一阵冷笑。\n", me);
		        ob->delete_temp("feilong");
		        me->kill_ob(ob);
		        remove_call_out("fast_attack");
		        call_out("fast_attack", 0, me, ob);
		        return "你三番四次想探听华山剑法的奥密，居心叵测！是否想对本派不利？\n"
		               "你即然对华山剑法如此憧景，只好用华山剑法送你上路了。\n";
	        }
	}
	
	command("look " + ob->query("id"));

	if (ob->query_skill("huashan-jianfa", 1) < 400)
		return "你的华山剑法修为不够，学不了「天外飞龙」。";

	if (ob->query_skill("zixia-shengong", 1) < 70)
		return "剑宗以剑为宗，以气为辅，并非弃气不用，你的紫霞神功可得再下一番苦功。";

	if (ob->query_skill("zixia-shengong", 1) > ob->query_skill("huashan-jianfa", 1)) 
	{
		command( "sneer" );
		return "你是气宗的人，却来向我请教，教我如何担当得起？";
	}

	if (ob->query("can_perform/huashan-jianfa/long"))
		return "咦，我不是传了你「天外飞龙」吗？多下功夫好好练习，别堕了华山剑宗的威名！";

	command("say 好！我便传你「天外飞龙」。看仔细了！" );

	message_vision("$N剑走龙蛇，白光如虹，凝重处如山岳巍峙，轻灵处若清风无迹，变幻莫测。\n" +
		       "舞到急处，$N一声大喝，长剑脱手飞出，化作一道惊虹，直没至柄插入一株树中。\n", me);

	ob->set("can_perform/huashan-jianfa/long", 1);

	return "你今后得要勤加练习，别辜负了我的一番教导。";
}

int fast_attack(object me, object ob)
{
	int i, num;

	if (! me->query_temp("weapon")) return 1;
	num = random(2) + 3;

	message_combatd(RED "\n封不平脸色沉重，使出其绝技「狂风快剑」，运剑如风似电般向$N连刺了" + chinese_number(num) + "剑。\n" NOR, ob);

	for (i = 1; i < num + 1; i++) 
	{
	        if (! me->is_fighting(ob)) break;
	        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
	}

	return 1;
}

/*
mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/huashan-jianfa/feilong"))
                return "你还不快去练习武功，一雪我们剑宗羞耻？";

        if (me->query("family/family_name") != query("family/family_name"))
                return RANK_D->query_respect(me) + "不是我们华山剑宗的人，请走吧！";

        if (me->query_skill("huashan-jianfa", 1) < 150)
                return "你的华山剑法还不到家，不要再给我丢脸了！";

        message_vision(HIY "$n" HIY "大喝一声，手中粘了一个石子"
                       "奋力击出，飞至半空突然化作粉末！\n"
                       HIY "$n" HIY "回头凝视着$N" HIY "道：这一"
                       "招没什么稀奇，就是要舍生忘死，运足内力！"
                       "你虽为剑宗弟子，也要好好修炼内力！\n" NOR,
                       me, this_object());
        tell_object(me, HIG "你学会了天外飞龙。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        me->set("can_perform/huashan-jianfa/feilong", 1);
        return 1;
}
*/
