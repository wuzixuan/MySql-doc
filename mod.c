#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"
char * headname = "head.html";
char * footname = "footer.html";

int cgiMain()
{
	FILE * fd;
char ch;
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);
while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
	fclose(fd);

	

	char name[32] = "\0";
	char birth[16] = "\0";
	char stuId[32] = "\0";
	char dept[16] = "\0";
	char sex[10] = "\0";
	char grade[5] ="\0";
	int status = 0;

	status = cgiFormString("name",  name, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
		return 1;
	}



	status = cgiFormString("stuId",  stuId, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}

	status = cgiFormString("birth",  birth, 16);
  if (status != cgiFormSuccess)
  {
 	 fprintf(cgiOut, "get birth error!\n");
 	 return 1;
  }

	status = cgiFormString("dept",  dept, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get dept error!\n");
		return 1;
	}

	status = cgiFormString("sex",  sex, 10);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sex error!\n");
		return 1;
	}

	status = cgiFormString("grade",  grade, 5);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get grade error!\n");
		return 1;
	}
	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "Stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}


	sprintf(sql, "update stu set stuId='%s',name = '%s' ,birth=%d,dept='%s',sex='%s',grade=%d where stuId ='%s'",stuId,name,atoi(birth),dept,sex,atoi(grade),stuId);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return ;
	}



	fprintf(cgiOut, "update student ok!\n");
	mysql_close(db);
	return 0;
}
