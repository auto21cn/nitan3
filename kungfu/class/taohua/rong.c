// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE; 

string ask_chicken();

void create()
{
        set_name("黄蓉", ({"huang rong", "huang", "rong"}));
        set("title", "东海桃花岛主之女");
        set("nickname", HIY "丐帮前任帮主" NOR);
        set("gender", "女性");
        set("age", 28);
        set("long", "这便是桃花岛岛主的独生女儿。由于岛主夫人\n"
                    "早死，岛主对这个女儿备加疼爱。她生性跳脱\n"
                    "飞扬，喜欢四处乱跑。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 28);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("qi", 4800);
        set("max_qi", 4800);
        set("jing", 3500);
        set("max_jing", 3500);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 200);
        set("level", 20);
        set("combat_exp", 3000000);

        set_skill("force", 240);
        set_skill("bibo-shengong", 240);
        set_skill("hand", 240);
        set_skill("strike", 240);
        set_skill("luoying-shenzhang", 240);
        set_skill("dodge", 240);
        set_skill("luoying-shenfa", 240);
        set_skill("parry", 220);
        set_skill("sword", 220);
        set_skill("luoying-shenjian", 220);
        set_skill("yuxiao-jianfa", 220);
        set_skill("lanhua-shou", 240);
        set_skill("staff", 240);
        set_skill("dagou-bang", 240);
        set_skill("unarmed", 200);
        set_skill("xiaoyaoyou", 200);
        set_skill("throwing", 200);
        set_skill("mantianhuayu", 200);
        set_skill("qimen-wuxing", 280);
        set_skill("count", 280);
        set_skill("literate", 280);
        set_skill("mathematics", 280);
        set_skill("cooking", 280);
        set_skill("martial-cognize", 220);

        map_skill("force", "bibo-shengong");
        map_skill("hand", "lanhua-shou");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "lanhua-shou");
        map_skill("staff", "dagou-bang");
        map_skill("sword", "yuxiao-jian");
        map_skill("strike", "xiaoyaoyou");
        map_skill("throwing", "mantianhuayu");

        prepare_skill("hand", "lanhua-shou");
        prepare_skill("strike", "xiaoyaoyou");

        create_family("桃花岛", 2, "爱女");
        
        set("inquiry", ([
                "叫化鸡" : (: ask_chicken :),
        ]) );
    
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.fu" :),
                (: perform_action, "hand.fei" :),
                (: perform_action, "strike.zhuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
	setup();
        carry_object("/clone/unique/ruanwei-jia")->wear();
        carry_object("/d/taohua/obj/shudai")->wear();
        set("startroom", "/d/taohua/wofang"); 
        check_clone(); 
}

void attempt_apprentice(object ob)
{
        command("say 现在国难当头，我哪里有时间收徒啊。");
        return;
}

string ask_chicken()
{
        if (this_player()->query_temp("marks/鸡", 1))
                return "你这个人怎么这么烦？老说车轱辘话！\n";
        else
        {
                say("蓉儿神往地说：叫化鸡可是杭州著名特产，我爹当年费了好大的劲才搞到了制作\n"
                    "它的秘方。你问它来干什么？\n");
                    
                this_player()->set_temp("marks/鸡", 1);
                
                return "你可以出去了。\n";
        }
}
