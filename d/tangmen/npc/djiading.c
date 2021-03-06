// bguanli

inherit NPC;

int do_giveto(object me, object obj);

void create()
{
	set_name("家丁", ({ "jia ding", "ding"}));
	set("long", 
"家丁xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx。\n");
	set("gender", "男性");
	set("age", 35);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 18);
	set("int", 25);
	set("con", 24);
	set("dex", 28);

	set("combat_exp", 30000);

	set_skill("force", 30);
	set_skill("dodge", 60);
	set_skill("parry", 40);
	set_skill("sword", 50);
	set_skill("blade", 40);
	set_skill("strike", 50);

	create_family("唐门世家", 4, "家丁");

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_give","give");
}

int do_give(string arg)
{
	object obj, obj2, me, *inv, who;
	string item;
	int amount, i;

	me = this_player();

	if(!arg) return notify_fail("你要给谁什么东西？\n");

	if( sscanf(arg, "%s to ding", item) == 1 || sscanf(arg, "ding %s", item)==1 );
		else 
			return notify_fail("你要给谁什么东西？\n");

	if(!objectp(who = present("jia ding", environment(me))) || !living(who))
		return notify_fail("这里没有这个人。\n");

	if(sscanf(item, "%d %s", amount, item)==2)
	{
		if( !objectp(obj = present(item, me)) )	
			return notify_fail("你身上没有这样东西。\n");
		if( !obj->query_amount() )	
			return notify_fail( obj->name() + "不能被分开给人。\n");
		if( amount < 1 )
			return notify_fail("东西的数量至少是一个。\n");
		if( amount > obj->query_amount() ) 
			return notify_fail("你没有那么多的" + obj->name() + "。\n");
		else 
			if( amount == (int)obj->query_amount() )
				return do_giveto(me, obj2);
			else
			{
				obj->set_amount( (int)obj->query_amount() - amount );
				obj2 = new(base_name(obj));
				obj2->set_amount(amount);
				if (do_giveto(me, obj2))
					return 1;
				else
				{
					obj->set_amount((int)obj->query_amount() + amount);
					return 0;
				}
			}
	}

	if(arg=="all")
	{
		inv = all_inventory(me);
		for(i=0; i<sizeof(inv); i++)
		{
			do_giveto(me, inv[i]);
		}
		write("Ok.\n");
		return 1;
	}

	if(!objectp(obj = present(item, me)))
		return notify_fail("你身上没有这样东西。\n");
	return do_giveto(me, obj);
}

int do_giveto(object me, object obj)
{
	string tar, targ;
	int tarm;
	string *duwu = ({
		"","蜈蚣","毒蝎子","竹叶青","金环蛇","蝮蛇","千年毒王",
	});
	tar = (string)obj->query("name");
	tarm = (int)me->query_temp("duyao");
	targ = (string)duwu[tarm];

	if( !environment() || base_name(environment()) != query("startroom") )
	{
		write("家丁说道：真是抱歉，请您等一下到储料房来找我吧。\n");
		return 0;
	}

//      printf("1%s1 == 1%s1 == %d/%d\n",tar,targ,tarm,sizeof(duwu));

	if ( !(int)me->query_temp("duyao") || !(int)me->query_temp("tangmen") )
	{
		message_vision("家丁很怪异的看着$N，欠身说道：“您应该没有做这里的工作吧！”\n", me);
		return 0;
	}	

	if ( (tar == targ) && objectp(obj) && !userp(obj) && !obj->is_character())
	{
		message_vision("家丁冲着$N一恭身，说道：“辛苦您了，东西就交给我吧！”\n", me);
		destruct(obj);
		me->delete_temp("tangmen");
		me->delete_temp("duyao");
		me->add("combat_exp", 150 + random(150));
		me->add("potential", 80 + random(30));
		return 1;
	}
	else
	{
		message_vision("家丁很为难的看着$N，欠身说道：“这不是你应该找到的东西吧！”\n", me);
		return 0;
	}
}
