// Room: youyi.c
// smallfish 2002/12/7 

#include <ansi.h>

inherit ROOM;

int is_chat_room() { return 1;} 
void create()
{
        set("short", "泥潭驿站·扬州");
    set("long",
"这里就是扬州驿站，里面一排排的都是整整齐齐、密密麻麻的小信\n"
"箱。江湖中大侠大魔们平时里所交发的信函都将发送到这里。由于排列\n"
"相当有秩序，你很容易就能找到("HIW"find"NOR")自己的信箱，你可以在这里查看\n"
"、整理自己的邮箱。并且也可给朋友写信。\n"
        );
    set("objects", ([
    ]));

 set("no_fight",1);
        set("exits", ([
                "west" : "/d/city/yizhan",
        ]));

        set("coor/x", -5);
	set("coor/y", 15);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_find","find");
   add_action("do_nothing",({
      "practice","lian","meditate","respirate","study","du",
               "tuna","exercise","dazuo","learn","xue","perform","xun"}));
}

int do_find()
{
        object me,ob;
        string id;
        
        me = this_player();
        id = me->query("id");
        
        if(present("mailbox",me))
        {
                write("你已经打开了信箱，如果不会用，请 look mailbox\n");
                return 1;
        }
        if(file_size("/data/mail/"+id[0..0]+"/"+id+".o")<0)
                write("你的信箱中目前没有任何信件。\n");
        ob = new("/clone/misc/mailbox");
        ob->move(me);
        
        write("你赶紧打开自己的信箱，现在可以使用以下指令来处理你的邮件：\n\n"
                "mail <某人>               寄信给别人。\n"
                "forward <信件编号> <某人> 将某封信转寄给别人。\n"
                "from                      查看信箱中的信件。\n"
                "read <信件编号>           阅读一封信件。\n"
                "discard <信件编号>        丢弃一封信件。\n");
        return 1;
}

int do_nothing()
{
   write("这里不是练功的地方。\n");
   return 1;
}
int valid_leave(object me, string dir)
{
        object obn;

        if( dir== "west"&&obn = present("mailbox",me))
        {
                destruct(obn);
                write("你把信箱锁好放下，就离开了这里。\n");
        }
        return ::valid_leave(me,dir);
}