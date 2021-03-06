// suicide.c

#include <ansi.h>
#include <login.h>
inherit F_DBASE;
inherit F_CLEAN_UP;
private int slow_suicide(object me);
private int halt_suicide(object me);
int help(object me);

void create() 
{
	seteuid(getuid());
	set("name", "自杀指令");
	set("id", "suicide");
	set("channel_id", "投胎精灵");
}

int main(object me, string arg)
{
	object *inv;
	int *res;
	int i;
	int real_suicide=0;
	int is_member=0;
	
	if (me->is_busy())
		return notify_fail("你上一个动作还没完成。\n");
	real_suicide=0;
	inv = deep_inventory(me);
	for (i = 0; i < sizeof(inv); i++)
	{
		if (! userp(inv[i]) && ! playerp(inv[i])) continue;
		return notify_fail("你身上还有个大活人呢，想不开也别急呀？\n");
	}

	if (! arg)
	{
		write(HIR"你必须加参数运行。\n"NOR);
		help(me);
		return 1;
	}
	arg=lower_case(arg);
	res=DATABASE_D->do_sql("select fee_time from users where id='"+me->query("id")+"'");
	is_member= (res[0] > 18)?1:0;
	switch(arg)
	{
		case "-f":
			real_suicide=(is_member)?0:1;
			break;
		case "-x":
			if(!is_member)
				return notify_fail("对不起，你不是交费会员，无权使用 -x 选项。\n");
			real_suicide=1;
			break;
		default:
			return help(me);
	}
	if(!real_suicide&&!is_member)
		return notify_fail("对不起，只有交费会员才可以使用投胎功能。\n");
	if(real_suicide)//自杀模式
		write(ALERT("请注意，如果你已经为这个帐号购买了游戏时间，$$自杀将会把购买的时间一并清除！$$")+
			HIR+"请注意，如果你已经为这个帐号购买了游戏时间，永远自杀将会把购\n"+
			"买的时间一并清除！\n"+NOR+
			"您选择了"+HIG+"永远死掉"+NOR+"的自杀方式，这个人物的资料将永远删除，请务必\n"+
			"考虑清楚，确定的话请输入正确的密码，否则输入错误的密码退出。\n请输入您的管理密码：");
	else//投胎模式
		write("请注意，你选择了"+HIG+"重新投胎"+NOR+"，重新投胎将重新初始化你的人物，\n"+
			"但是保留你的中英文名，性别，年龄和购买、已消费时间等\n"+
			"资料。"+HIR+"请慎重抉择，巫师不会为你错误的选择进行弥补的。\n"+NOR+
			"如果你确定，请输入正确的管理密码，否则请输入错误的密\n"+
			"码退出。请输入您的管理密码：");
	input_to("check_password", 1, me, real_suicide);
	return 1;
}

private void check_password(string passwd, object me, int forever)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("ad_password");
	if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
	{
		write(HIR "密码错误！请注意，你必须输入管理密码。\n");
		return;
	}

	tell_object(me, HIR "\n你决定要"+((forever)?"自杀":"重新投胎")+"了，如果三十秒"
		    "钟内不后悔，就真的不可挽回了。\n\n" NOR);
	me->set_temp("suicide/time", time());
	me->set_temp("suicide/last", 0);
	me->set_temp("suicide/forever",forever);
	me->set_temp("suicide/from", query_ip_number(me));
	me->start_busy((: slow_suicide, me :),
	       (: halt_suicide, me :));
}

private int slow_suicide(object me)
{
	object link_ob, *inv;
	int t, i;

	if (! objectp(me))
		return 0;

	t = time() - me->query_temp("suicide/time");
	if (t < me->query_temp("suicide/last"))
	{
		me->delete_temp("suicide/");
		return 0;
	}

	if (t < 30)
	{
		if (t - me->query_temp("suicide/last") < 5)
			return 1;

		tell_object(me, HIR "\n你还有" + chinese_number(30 - t) +
			    "秒钟仔细考虑(" HIC "halt停止" HIR ")。\n" NOR);
		me->set_temp("suicide/last", t / 5 * 5);
		return 1;
	}

	link_ob = me->query_temp("link_ob");
	if (! link_ob || ! interactive(me)) return 0;

	log_file("static/suicide",
		 sprintf("%s %s commits a suicide from %s\n",
			log_time(), log_id(me),
			me->query_temp("suicide/from")));

	seteuid(getuid());
	
	// add by Shure@tomud.com
	inv = deep_inventory(me);
	for (i = 0; i < sizeof(inv); i++)
	{
		if (! userp(inv[i]) && ! playerp(inv[i])) continue;
		tell_object(me, HIR"你身上还有个大活人呢，想不开也别急呀？\n"NOR);
		return 0;
	}
        	
	if(me->query_temp("suicide/forever"))
	{
		//永久自杀
		write("\n好吧，永别了:)。\n\n");
		CHANNEL_D->do_channel(this_object(), "rumor",
			sprintf("%s自杀了，以后你再也看不到这个人了。",
			me->name()));
		tell_room(environment(me), me->name() +
			"在你的面前化作轻烟，渐渐消失了...\n"+REM0(me), ({me}));
		message("system",REM2(me),users());
		UPDATE_D->remove_user(me->query("id"));
	}
	else
	{
		//重新投胎
		object ob,user;
		string *res;
		mapping my=me->query_entire_dbase();
		ob=me->query_temp("link_ob");//肯定能返回正确OB
		user=LOGIN_D->make_body(ob);
		res=DATABASE_D->do_sql("select fee_time from users where id='"+me->query("id")+"'");
		
		//应该保存的属性
		user->set("name",my["name"]);
		user->set("id",my["id"]);
		user->set_name(my["name"],({my["id"]}) );
		user->set("str", 14);
		user->set("dex", 14);
		user->set("con", 14);
		user->set("int", 14);
		user->set("per", 20);
		user->set("type", my["type"]);
		user->set("gender", my["gender"]);
		user->set("onl_time",my["onl_time"]);//记录已经使用的费用
		user->set_temp("fee_time",res[0]);//记录总费用
		user->set("age",my["age"]);
		if(my["monfee"]>0) user->set("monfee",my["monfee"]);

		user->set("surname",my["surname"]);
		user->set("purename",my["purename"]);
		user->set_temp("link_ob",ob);
		ob->set_temp("body_ob",user);
		//显示信息
		tell_room(environment(me),me->query("name")+"突然跌倒在地，身形越缩越小，痛苦万分。一晃眼，竟然凭空消失了 ... ...\n");
		CHANNEL_D->do_channel(this_object(),"rumor","听说"+me->query("name")+"("+me->query("id")+")活不下去了。自杀重新投胎去了。\n");
		if(exec(user,me)) //将控制权转移到user上。
		{
			write("重新投胎成功！\n");
			log_file("static/suicide_f",ctime(time())+" "+me->name()+"("+me->query("id")+") 重新投胎成功！\n");
		}	
		else
			log_file("static/suicide_f",ctime(time())+" "+me->name()+"("+me->query("id")+") 重新投胎失败！\n");
		user->setup();
		UPDATE_D->clear_user_data(me->query("id"), "all"); //清除玩家数据
		destruct(me); //摧毁旧物件
		//创建新记录
		LOGIN_D->init_new_player(user);
		UPDATE_D->check_user(user);
		//DATABASE_D->db_new_player(ob,user);
		user->move(REGISTER_ROOM);//移动到注册处重新投胎
		user->set("startroom",REGISTER_ROOM);
		user->save();

	}
	return 0;
}

private int halt_suicide(object me)
{
	tell_object(me, HIG "你打消了"+(me->query_temp("suicide/forever")?"寻死":"重新投胎")+"的念头。\n" NOR);
	me->delete_temp("suicide");
	return 1;
}

int help (object me)
{
	write(@HELP
指令格式: suicide [-f]

请注意，如果你已经为这个帐号购买了游戏时间，
自杀将会把购买的时间一并清除！
如果因为某种原因你不想活了, 你可以选择自杀.
自杀分两种:
 
suicide    : 显示帮助
suicide -f : 非会员可以用此选项完全地抹去
             自己的资料。而会员用此项功能
             将是进行一次真正的重新投胎，
             会员的中英文名称，性别，游戏
             时间，年龄等将得到保存。
suicide -x : 会员专用选项，用来无条件的将
             会员的资料抹除。购买的游戏时
             间也将抹去。请慎重使用。我们
             将不对此行为负责或者做任何补
             救措施，玩家必须自己承担由此
             带来的任何损失。 
请慎重选择 :)
 
HELP );
	return 1;
}
