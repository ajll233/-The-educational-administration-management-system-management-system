#include "teacher.h"
#include "tools.h"
int Ch;	//	输入账号、密码时接收的键盘键值
int Len;	//	输入账号、密码时的位数
void teacher_view(void)   //教师端口登录界面
{
	for(;;)					//进入死循环
	{
		End=0;
		tch_login();         //教师登录密码判断系统                   
		FILE* stdwfile = fopen("teacher_inf.txt","w"); //登录结束或者登录失败信息改变需要打开教师文件重新写入信息，记录登录密码错误次数或者帐号是否锁定
		if(NULL == stdwfile)
		{
		 printf("系统出错\n");
		 return;
		}
		for(int k=0; k<All_tch; k++)
		{
		 fprintf(stdwfile,"%s %c %s %s %hhd %d %hhd ",tea[k].name,tea[k].sex,tea[k].id,tea[k].key,tea[k].cnt,tea[k].flag,tea[k].is_school);
		}
		fclose(stdwfile);  
		while(End==0)     //end标志为0才能进入循环
		{
			menu();		//教师菜单
		}
		break;          //从教师菜单退出后break回到主菜单
	}
}

void add_stu(void)     //添加学生基本信息选择函数
{
	int num=0;
	printf("1.单个添加\n");
	printf("2.批量导入\n");
	printf("请输入你的选择：\n");
	scanf("%d",&num);
	if(num==1)
	{
		timport_stu();   //单个添加学生基本信息
	}
	else if(num==2)
	{
		tbatch_import_stu();  //批量添加学生基本信息
	}
	else
	printf("输入有误！请重新输入\n");
}

void timport_stu(void)	//单个添加学生
{
	char secret_key[7]="123456"; //初始化密码123456
	my_secret(secret_key);  //加密密码
	op_stufile("student_inf.txt");   //读取在校学生数量
    printf("请输入要添加的学生信息\n");
    for(;;)
    {
    	 printf("请输入姓名:");
    	stdin->_IO_read_ptr =stdin->_IO_read_end; //吃掉回车
		if(limit_len(20,stu[Tch_i].name)==100)        
    	{
    		printf("姓名不合法。请重新输入！\n");
    		continue;
    	}
    	else
    	break;
	}
    printf("请输入性别:");
    stdin->_IO_read_ptr =stdin->_IO_read_end;
    display_input(&stu[Tch_i].sex);
    FILE* fwp=fopen("student_inf.txt","w");
    for(int j=0;j<=Tch_i;j++)
    {
    	if(strcmp(stu[j].id,"")==0 && j==0 && stu[j].is_school==0)//如果本地文件中没有任何学生
    	{
    		strcpy(stu[j].id,"1001");         //给内存中对应的学生学号赋值1001
    		strcpy(stu[j].key,secret_key); //把加密后的初始化密码赋值给内存中新添加对应的学生
    		stu[j].flag=1;				   //判断是否帐号锁定赋值1,代表帐号可用
    	}
    	else if(j>0)	//除第一个学生以外所有学生
    	{
    		strcpy(stu[j].id,int_to_string(atoi(stu[j-1].id)+1));//在之前的学生的学号上加1,往后递增，其中用到atoi将字符串转换成转型后加1,再用自己写的函数将int转换成字符串型，最后用strcpy赋值给内存中学生的id
    		strcpy(stu[j].key,secret_key);  //将初始化的加密密码赋值给内存中的学生
    		stu[j].flag=1;					//判断是否帐号锁定赋值1,代表帐号可用
    	}
    	fprintf(fwp,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[j].name,stu[j].sex,stu[j].id,stu[j].key,stu[j].cnt,stu[j].flag,stu[j].chi,stu[j].math,stu[j].eng,stu[j].is_school);//每完成一个学生信息的赋值，就将内存中学生信息赋值给本地学生
     }
    Tch_i=0;   //全局变量置0防止干扰别的函数中学生数量读取
    fclose(fwp); //关闭文件
    msg_show("添加成功！\n",1.5);
}

void tbatch_import_stu(void) //批量导入学生
{
	char secret_key[7]="123456"; //初始化密码123456
	my_secret(secret_key);  //加密密码
	int temp=0;   //定一个中间变量用来接读取的学生人数
	char filename[20];    //用来接批量导入学生的文件名
	op_stufile("student_inf.txt");   //读取在校学生数量
    temp=Tch_i;       //读出在校学生数量后将它赋值给中间变量temp
    Tch_i=0;			//全局变量置0来读取下一次文件人数
    for(;;)
    {
    	printf("请输入要导入的学生文件名：\n");
    	stdin->_IO_read_ptr =stdin->_IO_read_end; //吃掉回车
		if(limit_len(20,filename)==100)        //输入批量导入的学生文件名
    	{
    		printf("文件名不合法。请重新输入！\n");
    		continue;
    	}
    	else
    	break;
	}
    FILE* frpp=fopen(filename,"r");     //打开输入的文件
	if(NULL==frpp)
    {
         printf("文件有误！\n");
         anykey_continue();
         return;
    }
    while(-1!=fscanf(frpp,"%s %c",oth[Tch_i].name,&oth[Tch_i].sex)) //other结构体中只放名字和性别，专门为批量的导入设计的结构体
    {
    	Tch_i++;    //获得批量导入文件的人数
    }
    fclose(frpp);
    FILE* fwp=fopen("student_inf.txt","w");
    if(Tch_i>TEA_MAX)         //如果导入文件的人数大于我们内存容量，直接报错
    {
    	printf("系统维护中...请稍后再试\n");
    	anykey_continue();
    	return;
    }
    if(temp==0)     //如果本地文件中没有任何信息，就从0开始赋值给内存
    {
    	for(int j=0;j<Tch_i;j++)
    	{
    		strcpy(stu[j].name,oth[j].name);
    		stu[j].sex=oth[j].sex;
    	}
    }
    else			//如果本地文件中有任何信息，就从对应人数后开始赋值给内存
    {
    	for(int j=temp,z=0;j<temp+Tch_i;j++,z++)
    	{
    		strcpy(stu[j].name,oth[z].name);
    		stu[j].sex=oth[z].sex;
    	}
    }
    for(int j=0;j<Tch_i+temp;j++)    //从开始到尾遍历
    {
    	if(strcmp(stu[j].id,"")==0 && j==0 && stu[j].is_school==0)
    	{
    		strcpy(stu[j].id,"1001");    //给内存中的0号位赋初始学号1
    		strcpy(stu[j].key,secret_key);
    		stu[j].flag=1;
    	}
    	else if(j>0)	
    	{
    		strcpy(stu[j].id,int_to_string(atoi(stu[j-1].id)+1));//在之前的学生的学号上加1,往后递增，其中用到atoi将字符串转换成转型后加1,再用自己写的函数将int转换成字符串型，最后用strcpy赋值给内存中学生的id
    		strcpy(stu[j].key,secret_key);
    		stu[j].flag=1;
    	}
    	fprintf(fwp,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[j].name,stu[j].sex,stu[j].id,stu[j].key,stu[j].cnt,stu[j].flag,stu[j].chi,stu[j].math,stu[j].eng,stu[j].is_school);//每完成一个学生信息的赋值，就将内存中学生信息赋值给本地学生
     }
    Tch_i=0;	//全局变量置0防止干扰别的函数中学生数量读取
    fclose(fwp);
    msg_show("添加成功！\n",1.5);
}
void tch_del(void)	//删除学生
{
	int j=0;
	Student stuzz={};     //用来接第一次输入的帐号
	Student stuzzz={};		//用来接再次删除的帐号
	op_stufile("student_inf.txt");    //读取在校学生数量
	printf("请输入要删除人的学号：\n");
	scanf("%s",stuzz.id);       
	for(;j<Tch_i;j++)
	{
		if(strcmp(stuzz.id,stu[j].id)==0 && stu[j].is_school==0)  //如果在内存中密码和输入帐号一致
		{
			printf("请再次输入以确认删除：\n");
			scanf("%s",stuzzz.id);   //第二次输入的帐号
			if(strcmp(stuzz.id,stuzzz.id)==0)  //如果第一次输入的帐号和第二次帐号一致
			{
				stu[j].is_school=1;     //将在校标志位置1,flag为1代表离校
				msg_show("删除成功！\n",1.5);
				break;
			}
		}	
	}
	if(j==Tch_i)  //如果全部遍历下来找不到对应学号
	msg_show("查无此人！请重新查询\n",1.5);	
	wr_stufile("student_inf.txt");
}
void tch_find(void) //查找学生
{
	int j=0,num=0,jkl=0;  //jkl用来接找到的学生个数
	Student stuzz={};
	op_stufile("student_inf.txt");    //读取在校学生数量
    printf("************************\n");
    printf("     1.按姓名查找\n");
    printf("     2.按学号查找\n");
    printf("************************\n");
	printf("请输入您的选择：\n");
	scanf("%d",&num);
	if(num==1)
	{
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		printf("请输入要查找人的姓名：\n");
		//display_input(stuzz.name);
		scanf("%s",stuzz.name);
		for(;j<Tch_i;j++)
		{
			if(strcmp(stuzz.name,stu[j].name)==0 && stu[j].is_school==0)
			{
				printf("姓名：%s 性别：%s 学号：%s 语文：%.1lf 数学：%.1lf 英语：%.1lf \n",stu[j].name,'w'==stu[j].sex?"女":"男",stu[j].id,stu[j].chi,stu[j].math,stu[j].eng);
				jkl++;                //如果找到一个jkl就加一，因为可能有同名学生
			}
		}
		if(jkl>0)              //防止直接跳出
		{
			anykey_continue();   
		}	
		if(Tch_i==j && jkl==0)    
		msg_show("查无此人！请重新查询\n",1.5);		
	}
	if(num==2)
	{
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		printf("请输入要查找人的学号：\n");
 		stdin->_IO_read_ptr =stdin->_IO_read_end;
		display_input(stuzz.id);
		for(;j<Tch_i;j++)
		{
			if(strcmp(stuzz.id,stu[j].id)==0 && stu[j].is_school==0) //同id且在校
			{
				printf("姓名：%s 性别：%s 学号：%s 语文：%.1lf 数学：%.1lf 英语：%.1lf \n",stu[j].name,'w'==stu[j].sex?"女":"男",stu[j].id,stu[j].chi,stu[j].math,stu[j].eng);
				anykey_continue();
				break;
			}
		}
		if(Tch_i==j)
		msg_show("查无此人！请重新查询\n",1.5);		
	}
	FILE* fwp=fopen("student_inf.txt","w");   //重新写入学生文件
	if(NULL==fwp)
    {
         perror("fopen");
         return;
    }
    for(int j=0;j<Tch_i;j++)
    {
	fprintf(fwp,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[j].name,stu[j].sex,stu[j].id,stu[j].key,stu[j].cnt,stu[j].flag,stu[j].chi,stu[j].math,stu[j].eng,stu[j].is_school);
	}
	fclose(fwp);
	fwp=NULL;
	Tch_i=0;
}
void tch_mod(void)  //修改学生信息或者成绩
{
	int j=0,num=0;
	Student stuzz={};
	op_stufile("student_inf.txt");    //读取在校学生数量
    printf("************************\n");
    printf("     1.修改学生基础信息\n");
    printf("     2.修改学生成绩\n");
    printf("************************\n");
	printf("请输入您的选择：\n");
	scanf("%d",&num);
	if(num==1)
	{
		printf("请输入学生的学号：\n");
		stdin->_IO_read_ptr =stdin->_IO_read_end;
 		display_input(stuzz.id);
		for(;j<Tch_i;j++)
		{
			if(strcmp(stuzz.id,stu[j].id)==0 && stu[j].is_school==0)
			{
				printf("请输入修改后的信息(姓名，性别)：\n");
				scanf("%s %c",stuzz.name,&stuzz.sex);
				strcpy(stu[j].name,stuzz.name);  //将输入的学生名字赋值给内存
				stu[j].sex=stuzz.sex;	
				msg_show("修改成功！\n",1.5);
				break;
			}
		}
		if(Tch_i==j)
		msg_show("查无此人！请重新查询\n",1.5);	
	}
	if(num==2)
	{
		printf("请输入学生的学号：\n");
		stdin->_IO_read_ptr =stdin->_IO_read_end;
 		display_input(stuzz.id);
		for(;j<Tch_i;j++)
		{
			if(strcmp(stuzz.id,stu[j].id)==0 && stu[j].is_school==0)
			{
				printf("请输入修改后的信息(语文,数学,英语)：\n");
				scanf("%lf %lf %lf",&stuzz.chi,&stuzz.math,&stuzz.eng); //输入成绩
				stu[j].chi=stuzz.chi;
				stu[j].math=stuzz.math;
				stu[j].eng=stuzz.eng;
				msg_show("修改成功！\n",1.5);
				break;
			}
		}
		if(Tch_i==j)
		msg_show("查无此人！请重新查询\n",1.5);	
	}
	FILE* fwp=fopen("student_inf.txt","w");   //操作结束将内存中信息写入本地文件中
	if(NULL==fwp)
    {
         perror("fopen");
         return;
    }
    for(int j=0;j<Tch_i;j++)
    {
	fprintf(fwp,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[j].name,stu[j].sex,stu[j].id,stu[j].key,stu[j].cnt,stu[j].flag,stu[j].chi,stu[j].math,stu[j].eng,stu[j].is_school);
	}
	fclose(fwp);
	fwp=NULL;
	Tch_i=0;
	
}
void tch_input(void) //录入成绩
{
	int num=0;
	printf("1.单个添加\n");
	printf("2.批量导入\n");
	printf("请输入你的选择：\n");
	scanf("%d",&num);
	if(num==1)
	{
		tsingle_input();   //单个录入成绩
	}
	else if(num==2)
	{
		tbatch_input();		//批量导入成绩
	}
	else
	printf("输入有误！请重新输入\n");
}
void tsingle_input(void)	//单个录入成绩
{
	int j=0;
	Student stuzz={};
	op_stufile("student_inf.txt");    //读取在校学生数量
 	printf("请输入学生的学号：\n");
 	stdin->_IO_read_ptr =stdin->_IO_read_end;
 	display_input(stuzz.id);
	for(;j<Tch_i;j++)
	{
		if(strcmp(stuzz.id,stu[j].id)==0 && stu[j].is_school==0)
		{
				printf("请输入学生的成绩(语文/数学/英语)：\n");
				scanf("%lf %lf %lf",&stuzz.chi,&stuzz.math,&stuzz.eng);//输入成绩
				stu[j].chi=stuzz.chi;
				stu[j].math=stuzz.math;
				stu[j].eng=stuzz.eng;
				msg_show("录入成功！\n",1.5);
				break;
		}
	}	
	if(Tch_i==j)
	msg_show("查无此人！请重新查询\n",1.5);	
	FILE* fwp=fopen("student_inf.txt","w");   //将内存信息写入本地文件
	if(NULL==fwp)
    {
         perror("fopen");
         return;
    }
    for(int j=0;j<Tch_i;j++)
    {
	fprintf(fwp,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[j].name,stu[j].sex,stu[j].id,stu[j].key,stu[j].cnt,stu[j].flag,stu[j].chi,stu[j].math,stu[j].eng,stu[j].is_school);
	}
	fclose(fwp);
	fwp=NULL;
	Tch_i=0;
}
void tbatch_input(void)		//批量录入成绩
{
	int j=0,temp=0;   //temp为中间变量
	char score_file[20];      //用来接成绩单名
	op_stufile("student_inf.txt");    //读取在校学生数量
    temp=Tch_i;
    Tch_i=0;
	for(;;)
    {
    	printf("请输入要导入的学生成绩单名：\n");
    	stdin->_IO_read_ptr =stdin->_IO_read_end; //吃掉回车
		if(limit_len(20,score_file)==100)        //输入批量导入的学生文件名
    	{
    		printf("文件名不合法。请重新输入！\n");
    		continue;
    	}
    	else
    	break;
	}
    FILE* frpp=fopen(score_file,"r");
	if(NULL==frpp)
    {
         printf("无此文件！\n");
         anykey_continue();
         return;
    }
    while(-1!=fscanf(frpp,"%s %lf %lf %lf",ext[Tch_i].id,&ext[Tch_i].chi,&ext[Tch_i].math,&ext[Tch_i].eng))//extra内存专门用来写入学生成绩以及对应学号
    {
    	Tch_i++;
    }
    fclose(frpp);
    frpp=NULL; 
	for(;j<temp;j++)
	{
		for(int k=0;k<temp;k++)
		{
			if(strcmp(ext[k].id,stu[j].id)==0)    //只要找到对应的学号就把语数英导入对应学生内存中
			{
				stu[j].chi=ext[k].chi;
				stu[j].math=ext[k].math;
				stu[j].eng=ext[k].eng;
			}
		}
	}	
	FILE* fwp=fopen("student_inf.txt","w");      //将学生内存信息写回本地文件
	if(NULL==fwp)
    {
         perror("fopen");
         return;
    }
    for(int j=0;j<temp;j++)
    {
	fprintf(fwp,"%s %c %s %s %hhd %d %lf %lf %lf %hhd ",stu[j].name,stu[j].sex,stu[j].id,stu[j].key,stu[j].cnt,stu[j].flag,stu[j].chi,stu[j].math,stu[j].eng,stu[j].is_school);
	}
	fclose(fwp);
	fwp=NULL;
	Tch_i=0;
	msg_show("导入成功！\n",1.5);
}
void tch_setstupas(void) //重置学生密码
{
	int j=0;
	Student stuzz={};
	char secret_key[7]="123456";
	my_secret(secret_key);  //加密密码
	op_stufile("student_inf.txt");     //读取在校学生数量
	printf("请输入要重置密码的学生学号\n");
	stdin->_IO_read_ptr =stdin->_IO_read_end;
	display_input(stuzz.id);
	for(;j<Tch_i;j++)
	{
		if(strcmp(stuzz.id,stu[j].id)==0 && stu[j].is_school==0)
		{
			strcpy(stu[j].key,secret_key);   //把加密后的密码赋给内存里对应人
			msg_show("重置成功！\n",1.5);
			break;
		}
	}
	if(Tch_i==j)
	msg_show("查无此人！请重新查询\n",1.5);
	wr_stufile("student_inf.txt");	
}
void tch_show_instu(void) //显示所有在校学生
{
	op_stufile("student_inf.txt");    //读取在校学生数量
	for(int j=0;j<Tch_i;j++)			  //从0开始遍历查找
	{
		if(stu[j].is_school==0)     //判断是否在校，在校就打印出来
		{
		printf("姓名：%s 性别：%s 学号：%s 语文：%.1lf 数学：%.1lf 英语：%.1lf \n",stu[j].name,'w'==stu[j].sex?"女":"男",stu[j].id,stu[j].chi,stu[j].math,stu[j].eng);      //打印在校学生信息和成绩
		}
	}
	Tch_i=0;
	anykey_continue();					//防止清屏，将读取信息时间决定权交给用户
} 
void tch_show_dstu(void) //显示所有退出学生
{
	op_stufile("student_inf.txt");   //读取在校学生数量
	for(int j=0;j<Tch_i;j++)			 //从0开始遍历查找
	{
		if(stu[j].is_school==1)		//判断是否离校，离校就打印出来
		{
		printf("姓名：%s 性别：%s 学号：%s 语文：%.1lf 数学：%.1lf 英语：%.1lf \n",stu[j].name,'w'==stu[j].sex?"女":"男",stu[j].id,stu[j].chi,stu[j].math,stu[j].eng);   //打印离校学生信息
		}
	}
	Tch_i=0;
	anykey_continue();				//防止清屏，将读取信息时间决定权交给用户
}
void tch_unlock(void)  //解锁学生密码
{
	int j=0;
	Student stuzz={};                //初始化一个学生结构体用来接输入的学号
	op_stufile("student_inf.txt");   //读取在校学生数量
	printf("请输入要解锁的学生学号\n");
	stdin->_IO_read_ptr =stdin->_IO_read_end;
	display_input(stuzz.id);	
	for(;j<Tch_i;j++)
	{
		if(strcmp(stuzz.id,stu[j].id)==0 && stu[j].is_school==0) //判断是否学号一致并且是在校的
		{
			stu[j].flag=1;			//如果在校就把标志位置1,解锁账户
			stu[j].cnt=0;			//将错误密码输入次数清0
			msg_show("解锁成功！\n",1.5);   //提示信息
			break;
		}
	}
	if(Tch_i==j)       //遍历完后还没有找到对应学生，直接提示无此人后结束该函数
	msg_show("查无此人！请重新查询\n",1.5);
	wr_stufile("student_inf.txt");
}

