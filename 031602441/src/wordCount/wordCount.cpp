#include"pch.h"
#include<iostream> 
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<fstream>
using namespace std;
/***********************单词结构体***********************/
struct word {
	char name[30];
	int num;
	struct word *next;
};
/**********************读取字符*********************/
int readchars(struct word*&head, char *filename, int file_chars)
{

	FILE *file = _fsopen(filename, "r",_SH_DENYNO);
	char chars = -1;
	while (1)
	{
		chars = fgetc(file);
		if (chars == EOF)
			break;
		file_chars++;
	}
	std::ofstream openfile("C:/Users/Mac/Desktop/result.txt", std::ios::trunc);
	openfile << "characters:" << file_chars << endl;
	openfile.close();
	return 0;
}
/**********************读取行数*********************/
int readlines(struct word*&head, char *filename, int file_lines)
{

	FILE *file = _fsopen(filename, "r", _SH_DENYNO);
	char chars = -1;
	char bb_chars = -1;//前一个字符 
	while (1)
	{
		chars = fgetc(file);
		if (chars == EOF)
			break;
		if (chars == '\n'&&bb_chars != '\n')
			file_lines++;
		bb_chars = chars;
	}
	file_lines++;
	std::ofstream openfile("C:/Users/Mac/Desktop/result.txt", std::ios::app);
	openfile << "lines:" << file_lines << endl;
	openfile.close();
	return 0;
}
/**********************读取文件中单词*********************/
void readword(struct word*&head, char *filename, int word_num)
{
	int flag = 0;
	FILE *fp;
	if ((fp = _fsopen(filename, "r", _SH_DENYNO)) == NULL)
	{
		printf("无法打开此文件!\n");
		exit(0);
	}
	char ch, b_chars[30];
	struct word *p;
	while (!feof(fp))
	{
		int i = 0;
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
		while (p&&flag == 1)
		{
			if (!_stricmp(b_chars, p->name))
			{
				p->num++;break;
			}
			p = p->next;
		}
		if (!p&&flag == 1 && b_chars[0] != '\0')
		{
			p = new word;
			strcpy_s(p->name, b_chars);
			p->num = 1;
			p->next = head->next;
			head->next = p;
		}
		flag = 0;
	}
	std::ofstream openfile("C:/Users/Mac/Desktop/result.txt", std::ios::app);
	openfile << "words:" << word_num << endl;
	openfile.close();
}
/****************************排序***********************/
void sort(struct word*&head)
{
	struct word *q;
	struct word a[10];
	int i;
	char s[30] = { 0 };
	for (i = 0;i < 10;i++)
	{
		a[i].num = 0;
		strcpy_s(a[i].name, s);
	}
	for (i = 0;i < 10;i++)
	{
		q = head;
		while (q != NULL)
		{
			if (q->num == a[i].num)
			{
				if (_stricmp(q->name, a[i].name) < 0)
				{
					strcpy_s(a[i].name, q->name);
				}
			}
			else if (q->num > a[i].num)
			{
				strcpy_s(a[i].name, q->name);
				a[i].num = q->num;

			}
			q = q->next;
		}
		q = head;
		while (q != NULL)
		{
			if (_stricmp(a[i].name, q->name) == 0)
			{
				q->num = 0;
				if (a[i].num != 0)
				{
					std::ofstream openfile("C:/Users/Mac/Desktop/result.txt", std::ios::app);
					openfile << "<" << a[i].name << ">:" << a[i].num << endl;
					openfile.close();
				}
				break;
			}
			else
				q = q->next;
		}
	}
}
/*****************************主函数****************************/
int main()
{
	char filename[30];
	struct word *head;
	head = new word;
	head->next = NULL;
	int file_lines = 0;
	int file_chars = 0;
	int word_num = 0;
	cin >> filename;
	FILE *file = _fsopen(filename, "r", _SH_DENYNO);
	if (!file)
	{
		cout << "打开文件错误！" << endl;
		return 0;
	}
	else
	{
		readchars(head, filename, file_chars);
		readword(head, filename, word_num);
		readlines(head, filename, file_lines);
		sort(head);
	}

}
