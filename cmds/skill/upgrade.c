// upgrade

#include <ansi.h>

inherit F_CLEAN_UP;

#define PERIOD          864
#define PERIOD_POT      20000
#define PERIOD_MAR      12000

int clossing(object me);
int halt_closing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;
        
        seteuid(getuid());
        where = environment(me);
        
        if (! arg)
                return notify_fail("你要修炼什么武功？\n");
        
        if (! me->query_skill(arg) || 
            file_size(SKILL_D(arg) + ".c") < 0)    
               return notify_fail("你要修炼的武功不存在或你不会该武功。\n");
        
        if (! SKILL_D(arg)->is_invent_skill())
               return notify_fail(to_chinese(arg) + "并不是自创武功，无法通过这种方式修炼。\n");  
               
        if (where->query("pigging"))
                return notify_fail("你还是专心拱猪吧！\n");

        if (! where->query("no_fight"))
                return notify_fail("在这里修炼？不太安全吧？\n");

        if (! where->query("sleep_room"))
                return notify_fail("你得找一个能够休息的地方修炼。\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");
                        
        if (count_lt(count_sub(me->query("potential"), me->query("learned_points")), 1000000)) 
                return notify_fail("你的潜能不够，没法修炼。\n");

        if (count_lt(me->query("experience"), count_add(me->query("learned_experience"), 600000))) 
                return notify_fail("你现在积累的实战体会还太少。\n"); 
        
        if ((int)me->query("qi") * 100 / me->query("max_qi") < 90)
                return notify_fail("你现在的气太少了，无法静心修炼。\n");

        if ((int)me->query("jing") * 100 / me->query("max_jing") < 90)
                return notify_fail("你现在的精太少了，无法静心修炼。\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("你觉得内力颇有不足，看来目前还难以"
                                   "进行长时间的修炼。\n");

        if ((int)me->query("neili") * 100 / me->query("max_neili") < 90)
                return notify_fail("你现在的内力太少了，无法静心修炼。\n");

        message_vision("$N盘膝坐下，开始冥神运功，闭关修炼" + to_chinese(arg) + "。\n", me);
        me->set("startroom", base_name(where));
        me->set("doing", "invent");
        me->set("upgrade", arg);
        CLOSE_D->user_closed(me, "invent");
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("大宗师%s(%s)开始闭关修炼%s。",
                              me->name(1), me->query("id"), to_chinese(arg)));

        return 1;
}

int continue_upgradeing(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n你继续闭关修炼" + to_chinese(me->query("upgrade")) + "...\n" NOR);
        return 1;
}

int closing(object me)
{
        int t;
        int tn;
        mixed pot, mar;
        int r;
        int exp_inc;
        string skill;
        
        skill = me->query("upgrade");  
        pot = me->query("potential");
        mar = me->query("experience");
        if (count_le(pot, me->query("learned_points")) 
        ||  count_le(mar, me->query("learned_experience")))
        {
                tell_object(me, "你的潜能或体会耗尽了。\n");
                message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("听说%s(%s)修炼%s功德圆满。",
                                      me->name(1), me->query("id"), to_chinese(skill)));
                if (! interactive(me))
                {
                        me->force_me("chat* haha");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        if (count_gt(me->add("learned_points", PERIOD_POT / 2 + random(PERIOD_POT)), pot))
                me->set("learned_points", pot);

        if (count_gt(me->add("learned_experience", PERIOD_MAR / 2 + random(PERIOD_MAR)), mar))
                me->set("learned_experience", mar);
                
        t = me->query_temp("last_closing");
        tn = time();
        if (tn - t < 0)
        {
                me->set_temp("last_closing", tn);
                return 1;
        }

        if (tn - t < PERIOD)
                return 1;

        me->set_temp("last_closing", tn);
                
        if (random(10) == 0)
                tell_object(me, "闭关修炼" + to_chinese(skill) + "中...\n");
        
        /*
        if ((random(100) < 3) && me->can_improve_neili())
        {
                tell_object(me, HIR "你对内功有所领悟，感到内力进步了！\n" NOR);
                me->add("improve/neili", 1);
                me->improve_neili(10 + random(20));
        }

        if ((random(100) < 3) && me->can_improve_jingli())
        {
                tell_object(me, HIM "你对神通有所领悟，感到精力进步了！\n" NOR);
                me->add("improve/jingli", 1);
                me->improve_jingli(5 + random(10));
        }
        */

        exp_inc = 50 + random(100);
        exp_inc = exp_inc * (100 + me->query_skill("martial-cognize", 1)) / 500;
        exp_inc = exp_inc * (100 + me->query("int")) / 100;
        me->add("combat_exp", exp_inc);
        me->improve_skill("martial-cognize", 800 + random(800));

        tell_object(me, HIY "你对" + to_chinese(skill) + "有所感悟。\n" NOR);
        me->improve_skill(skill, 5000 + random(1000));
        SKILLS_D->upgrade_skill_power(skill); 

        return 1;
}

int halt_closing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "你中止了闭关修炼" + to_chinese(me->query("upgrade")) + "。\n");
        message_vision(HIY "$N" HIY "大喝一声，睁开眼来，一股气流登时"
                       "将众人迫退四步。\n\n" NOR, me);

        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "修炼" + to_chinese(me->query("upgrade")) + "中途突然复出。");
        return 1;
}

protected void user_quit(object me)
{
        if (! objectp(me) || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
指令格式 : upgrade

闭关修炼自创武功，只有你自创武功以后才能够闭关修炼你的自创武功。
要求必须在一个安全并且可以休息的地方才能修炼，修炼前需要有一百
万点潜能及六十万体会，闭关开始以后，玩家离线以后其角色将仍然在
线修行，直到玩家中止修炼(halt)或是潜能或体会耗尽。期间内玩家的
经验、自创武功、武学修养、自创武功威力将会提升。

HELP );
        return 1;
}

