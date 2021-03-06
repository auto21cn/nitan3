// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// gao-laozhe.c

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "qizong.h"

void create()
{
        set_name("高老者", ({ "gao laozhe", "gao" }));
        set("title", HIR"华山第十二代长老"NOR);
        set("long", 
"他就是华山的长老高老者。一副浑不在乎的模样，开朗乐天，万事不萦怀，\n"
"但事事追随他的师兄矮老者。\n");
        set("gender", "男性");
        set("age", 65);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 26);
        set("int", 25);
        set("con", 28);
        set("dex", 25);        
        set("qi", 4200);
        set("max_qi", 4200);
        set("jing", 2100);
        set("max_jing", 2100);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 60);
        set("level", 30);
        set("combat_exp", 1750000);
        set("score", 60000);

        set_skill("cuff", 380);
        set_skill("force", 380);
        set_skill("blade", 380);
        set_skill("sword", 380);
        set_skill("dodge", 380);
        set_skill("parry", 380);
        set_skill("strike", 380);
        set_skill("huashan-neigong", 380);
        set_skill("zixia-shengong", 380);
        set_skill("huashan-shenfa", 380);
        set_skill("poyu-quan", 380);
        set_skill("fanliangyi-dao", 380);
        set_skill("huashan-jianfa", 380);
        set_skill("hunyuan-zhang", 380);
        set_skill("feiyan-huixiang", 380);
        set_skill("literate", 400);
        set_skill("martial-cognize", 320); 
        
        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "fanliangyi-dao");
        map_skill("blade", "fanliangyi-dao");
        map_skill("sword", "huashan-jian");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        create_family("华山派", 12, "弟子");
        
        set("inquiry", ([
	        "紫霞神功" : "那是本门无上的内功心法。据说紫霞有个大秘密，可惜已失传多年了。\n",
	        "密室"     : "你胡说八道些甚麽？\n",
	]));
	
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "blade.sanshen" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 5);
	setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        string ob_fam;

        ob_fam = ob->query("family/family_name");
        if (! permit_recruit(ob))
                return;

        if (ob_fam == "华山派" && ob->query_skill("zixia-shengong", 1) < 100)
	{
		command("say 我看你的紫霞神功还没学到家吧，本派有本的"
                        "紫霞秘籍，你可曾研读？");
		return;
	}

        if ((int)ob->query_skill("sword", 1) < 100)
	{
                command("say 你的剑法还没学到家，快回去练好基本剑法。");
		return;
	}

        if (ob_fam == "华山派" && (int)ob->query_skill("huashan-jianfa", 1) < 100 ||
            ob_fam == "华山剑宗" && (int)ob->query_skill("kuangfeng-jian", 1) < 100)
	{
                command("say 华山剑法和狂风剑法是本派弟子必须精通的武技，多练练"
                        "本门剑术。");
		return;
	}

        if ((int)ob->query("shen") < 10000)
	{
		command("say 我华山派乃是堂堂名门正派，对弟子要求极"
                        "严，你还得多作些行侠仗义的事！");
		return;
	}
	
        if (ob_fam == "华山剑宗")
        {
                command("say 你啊你... 唉！也算是剑气之争的受害者，罢了，不提也罢。");
                ob->delete("family");
        }
        
	command("say 好吧，我就收下你了，光大我们华山派还要靠你们这些后生啊。");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "fighter")
		ob->set("class", "fighter");
}

#include "zhanglao.h"
