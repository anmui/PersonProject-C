#include"pch.h"
#include"readword.h"
#include"structword.h"
#include<fstream>
using namespace std;


/**********************读取文件中单词*********************/
int readword(struct word*&head,char *filename, int word_num)
{
	int flag = 0;
	int flag1 = 0;
	int flag2 = 0;
	int i = 0;
	FILE *fp;
	if ((fp = _fsopen(filename, "r", _SH_DENYNO)) == NULL)
	{
		printf("无法打开此文件!\n");
		exit(0);
	}
	char ch, b_chars[30];
	struct word *p=new word;
	p->next = NULL;
	struct word *chars[30];
	int z = 1;
	while (!feof(fp))
	{
		i = 0;
		ch = fgetc(fp);
		while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9'))
		{
			b_chars[i] = ch;
			i++;
			ch = fgetc(fp);
			if (feof(fp)) break;
		}
		b_chars[i] = '\0';
		if (((b_chars[0] <= 'z') && (b_chars[0] >= 'a')) || ((b_chars[0] <= 'Z') && (b_chars[0] >= 'A')))
		{
			if (((b_chars[1] <= 'z') && (b_chars[1] >= 'a')) || ((b_chars[1] <= 'Z') && (b_chars[1] >= 'A')))
			{
				if (((b_chars[2] <= 'z') && (b_chars[2] >= 'a')) || ((b_chars[2] <= 'Z') && (b_chars[2] >= 'A')))
				{
					if (((b_chars[3] <= 'z') && (b_chars[3] >= 'a')) || ((b_chars[3] <= 'Z') && (b_chars[3] >= 'A')))
					{
						flag = 1;
						word_num++;
					}
				}
			}
		}
		i = 0;
		if (flag == 1 && b_chars[0] != '\0')
		{
			while (b_chars[i])
			{
				if (b_chars[i] >= 'A'&&b_chars[i] <= 'Z')
				{
					b_chars[i] += 32;
				}
				i++;
			}
		}
		p = head->next;
		struct word *q = new word;
		q->next = NULL;
		if (flag == 1 && b_chars[0] != '\0')
		{
			for (int j = 1;j < z;j++)
			{
				if (chars[j]->name[0]== b_chars[0])
				{
					flag1 = j;
					break;
				}
			}
			if (flag1!=0)
			{
				strcpy_s(q->name, b_chars);
				q->num = 1;
				q->next = chars[flag1]->next;
				chars[flag1]->next = q;
			}
			else
			{
				strcpy_s(q->name, b_chars);
				q->num = 1;
				q->next = head->next;
				head->next = q;
				chars[z] = new word;
				chars[z] = q;
				z++;

			}
		}
		flag1 = 0;
		flag = 0;
		
	}
	printf("单词录入完毕！\n");
	struct word* p1 = new word;
	p = head->next;
	while (p)
	{
		p1 = p->next;
		if (p->num != 0)
		{
			while (p1 != NULL)
			{
				if (p1->name[0] == p->name[0])
				{
					if (p1->num != 0)
					{
						if (!_stricmp(p->name, p1->name))
						{
							p->num++;
							p1->num = 0;
						}
					}
					p1 = p1->next;
				}
				else
					break;
			}
		}
		p = p->next;
	}
	printf("统计完成");
	std::ofstream openfile("result.txt", std::ios::app);
	openfile << "words:" << word_num << endl;
	openfile.close();
	return 0;
	
}


