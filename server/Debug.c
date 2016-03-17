#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include "Debug.h"



void DisplayCurTime()
{
   	   //��ʾ��ǰʱ��
	   time_t rawtime;
	   struct tm * timeinfo;
	   time ( &rawtime );
	   timeinfo = localtime ( &rawtime );
	   printf ( "\n\nThe current date/time is: %s", asctime (timeinfo) );
}

void DebugString(char * pcToDisplay)
{
    //��ӡ������Ϣ
    printf("\n/*****************************************************************/\n");
	printf("Debug_Information!\n%s",pcToDisplay);
	printf("\n/*****************************************************************/\n");
}

void Debug(char *fmt, ...)
{  
	printf("\n/*****************************************************************/\n");
    printf("Debug_Information!\n");
	va_list ap;
	char *p,*sval;
	int ival;
	double dval;

	va_start(ap,fmt);
	for(p=fmt;*p;p++)
	{
		if(*p!='%')  //�������ռλ�����Ͱ�������ֵ���
		{
			putchar(*p);
			continue;
		}
		switch(*++p)
		{
			case 'd':
				ival=va_arg(ap,int);
				printf("%d",ival);
				break;
			case 'f':
				dval=va_arg(ap,double);
				printf("%f",dval);
				break;
			case 's':
				for(sval=va_arg(ap,char *);*sval;sval++)
				putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);
	printf("\n/*****************************************************************/\n");
}





