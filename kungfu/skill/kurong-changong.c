inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

int valid_force(string force)
{
        return 1;
        return force == "xiantian-gong" ||
               force == "quanzhen-xinfa"  ||
               force == "duanshi-xinfa";
}

int query_neili_improve(object me)
{
    	int lvl;

    	lvl = (int)me->query_skill("kurong-changong", 1);
    	return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        int nb, nk;
        int lvl = (int)me->query_skill("kurong-changong", 1);
        
        if (me->query("gender") == "无性" && lvl > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的枯荣禅功。\n");

        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的基本内功火候还不够。\n");
                
        nb = (int)me->query_skill("buddhism", 1);
        nk = (int)me->query_skill("kurong-changong", 1);
        
        if (nb < 120 && nb <= nk)
                return notify_fail("你的禅宗心法修为不够，无法领会更高深的枯荣禅功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("枯荣禅功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"kurong-changong/" + func;
}
