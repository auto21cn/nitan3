// dongfang.c
//Updated by haiyan

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_book();
mixed ask_pfm();

void create()
{
    set_name("东方不败", ({"dongfang bubai", "dongfang", "bubai"}));
    set("nickname", HIY "天下无敌" NOR);
    set("title", HIM "日月神教教主" NOR);
    set("gender", "无性");
    set("shen_type", -1);
    set("age", 42);
    set("long",
        "他就是日月神教教主。号称无人可敌，因此有一称号为「东方不败」。\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 21);
    set("int", 30);
    set("con", 26);
    set("dex", 30);

    set("inquiry", ([
        "杨莲亭"   : "你敢直称我爱人的名字，想找死呀？ \n",
        "辟邪剑谱" : "这是研读葵花宝典的基础，只有读通了宝典，武功才算大成。\n",
        // "葵花宝典" : (: ask_book :),
        "绝招"     : (: ask_pfm :),
        "鬼影"     : (: ask_pfm :),
    ]));

    set("kuihua_count", 1);

    set("qi", 5000);
    set("max_qi", 5000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 4500);
    set("max_neili", 4500);
    set("jiali", 400);

    set("combat_exp", 3000000);
    set("score", 0);

    set_skill("force", 420);
    set_skill("unarmed", 400);
    set_skill("riyue-xinfa", 400);
    set_skill("riyue-guanghua", 420);
    set_skill("sword", 400);
    set_skill("riyue-jian", 390);
    set_skill("pixie-jian", 400);
    set_skill("dodge", 400);
    set_skill("piaomiao-shenfa", 400);
    set_skill("parry", 390);
    set_skill("cuff", 390);
    set_skill("xuwu-piaomiao", 390);
    set_skill("hand", 390);
    set_skill("huanmo-longtianwu", 390);
    set_skill("literate", 220);

    map_skill("force", "riyue-guanghua");
    map_skill("sword", "pixie-jian");
    map_skill("dodge", "pixie-jian");
    map_skill("parry", "pixie-jian");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("hand", "huanmo-longtianwu");

    prepare_skill("cuff", "xuwu-piaomiao");
    prepare_skill("hand", "huanmo-longtianwu");

    create_family("日月神教", 2, "教主");

    set("no_teach", ([
        "pixie-jian" : "辟邪剑法只能靠自己研读《葵花宝典》。他日待你小成，我自会指点于你。",
    ]));


    set("master_ob",5);
	setup();
    carry_object("/d/fuzhou/obj/xiuhua")->wield();
    carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
    carry_object("/d/heimuya/obj/yuxiao");
}

void attempt_apprentice(object ob)
{
     if(! permit_recruit(ob))  return;

     if((string)ob->query("family/master_name") == "任我行")
     {
          command("say 我越看你越不顺眼，快给我滚！");
          return;
     }

     if(count_lt(ob->query("combat_exp"), 250000))
     {
          command("say 就你这点微末功夫，还是先跟我属下各长老多练练吧！");
          return;
     }

     if((int)ob->query_skill("riyue-xinfa", 1) < 140)
     {
          command("say 本教的内功心法你还没练好，还要多下苦功才行！");
          return;
     }

     command("xixi");
     command("recruit " + ob->query("id")); 
     command("say 好！好！我日月神教真是人才辈出，一统江湖，指日可待！");
     ob->set("title", HIR "日月神教大护法" NOR);
}

string ask_book()
{
     mapping fam;
     object me, ob;

     me = this_player();
     if (me->query("family/family_name") != query("family/family_name"))
            return "你这个" + RANK_D->query_rude(this_player()) +
                   "，打听本教秘笈有何图谋？";

     if (me->query("family/master_id") != query("id"))
            return "你又非我亲传弟子，打听宝典做什么？";

     if (me->query_skill("riyue-guanghua", 1) < 100)
            return "你的日月光华学得还不到家，贸然修炼宝典，有害无益。";

     if (query("kuihua_count") < 1)
            return "你来晚了，宝典我已经借出去了。";

     add("kuihua_count", -1);
     ob = new("/clone/book/kuihua");
     ob->move(me);
     return "这本宝典你可要收好，弄丢了我找你算帐。";
}

void reset()
{
     set("kuihua_count", 1);
}

mixed ask_pfm()
{
     object me = this_player();

     if (me->query("can_perform/pixie-jian/ying"))
           return "我已指点于你，还多问什么？自己多练练去！";

     if (me->query("family/family_name") != query("family/family_name"))
           return "本教武功独步武林，这位" + RANK_D->query_respect(me) +
                  "既然想学，不如入我日月神教如何？";

     if (me->query_skill("pixie-jian", 1) < 90)
           return "宝典所载武功博大精深，你连一半都没看完，多问什么？快给我用功去！";

     if (me->query_skill("pixie-jian", 1) < 200)
           return "你的辟邪剑法尚欠火候，再多去钻研一下宝典！";

     message_vision(HIC "$n" HIC "对$N" HIC "点了点头：“很好，我来教你一招，看仔细了。”\n" HIR
                    "只见$n" HIR "身形微晃，霎时不见踪影，$N" HIR
                    "只觉无数黑影在身边飘过，数道寒气逼向周身，全身一阵刺痛。\n" NOR,
                    me, this_object());
     command("say 明白了没有？”"NOR);
     tell_object(me, HIW "你学会了「鬼影」这一招。\n" NOR);
     if (me->can_improve_skill("sword"))
             me->improve_skill("sword", 160000);
     me->set("can_perform/pixie-jian/ying", 1);
     return 1;
}

