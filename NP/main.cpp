#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<stdio.h>
using namespace std;
#include <string>
#include "NLPIR.h"
#pragma comment(lib,"NLPIR.lib")

string change(int n)
{
	string s;
	s = "";
	if (n == 0)
		s = "0";

	while (n != 0)
	{
		if (n % 16 >9)
			s += n % 16 - 10 + 'A';
		else
			s += n % 16 + '0';
		n = n / 16;
	}

	reverse(s.begin(), s.end());//反转字符串
	return s;
}

const int M = 3000000;
char word[3000000][300];
int wp; // 单词定位
int pi = 1; // 代表空闲的节点位置

struct tree
{
	int next[36];
	int value;
	bool end;
} tree[M]; // 可用节点数组

void init()
{
	memset(tree, 0, sizeof(tree));
	pi = 1; // 空闲节点从1开始
	wp = 0;
}

void insert(char * keyword, int value)
{
	int index, p, i; // p代表当前的节点，开始为根节点

	for (i = p = 0; keyword[i]; i++)
	{
		if (keyword[i] >= '0'&&keyword[i] <= '9')
		{
			index = keyword[i] - '0';
		}

		else index = keyword[i] - 'A' + 10;

		if (tree[p].next[index] == 0)
			tree[p].next[index] = pi++;

		p = tree[p].next[index];
	}

	tree[p].value = value;
	tree[p].end = 1;
}

bool query(char * keyword, int &value)
{
	int index, p, i;

	for (i = p = 0; keyword[i]; i++)
	{
		if (keyword[i] >= '0'&&keyword[i] <= '9')
		{
			index = keyword[i] - '0';
		}

		else index = keyword[i] - 'A' + 10;

		if (tree[p].next[index] == 0)
			return 0;

		p = tree[p].next[index];
	}

	if (tree[p].end)
	{
		value = tree[p].value;

		return 1;
	}

	return 0;
}


string Find_zds(char s[])
{
	char s1[30], s2[100];
	//用来强制转换 s_temp
	int i, value;
	string s_temp;
	string s_cout;

	ifstream f("HEX_JX.txt", ios::in);//读文件, 打开文件
	while (true)
	{
		if (f.eof())
		{
			break;
		}

		getline(f, s_temp);

		const char *s = s_temp.c_str();

		for (i = 1; i<strlen(s); i++)
		{
			if (s[i] == ' ')
				break;
		}

		strncpy(s1, s, i);
		s1[i] = 0;
		strcpy(s2, s + i + 1);
		strcpy(word[wp], s2); // 单词数组（二维）
		insert(s1, wp++); // 含义插入字典树
	}

	f.close();//读文件, 打开文件


	if (query(s, value))
		s_cout = word[value];
	else
		s_cout = "go";

	return s_cout;
}
int main(int argc, char *argv[])
{
	string s_temp;
	int i;
	char s1[300], s2[1000];
	ifstream f("HEX_JX.txt", ios::in);//读文件, 打开文件
	vector <string> cha;//情绪分类标识；
	while (true)
	{
		if (f.eof())
		{
			break;
		}

		getline(f, s_temp);

		const char *s = s_temp.c_str();

		for (i = 1; i<strlen(s); i++)
		{
			if (s[i] == ' ')
				break;
		}

		strncpy(s1, s, i);
		s1[i] = 0;
		strcpy(s2, s + i + 1);
		strcpy(word[wp], s2); // 单词数组（二维）
		insert(s1, wp++); // 含义插入字典树
						  //cout << s2;
	}

	f.close();//读文件, 关闭文件


	//while (true)
	//{
		string data;
		/*cin >> data;
		ofstream out("1.txt", ios::out);
		if (out.is_open())
		{
			out << " " << data;
			out.close();
		}*/
		ifstream fin("1.txt", ios::in);
		if (!fin) { cout << "1.txt file read error!" << endl; return -1; }
		string text, tempstr;
		while (!fin.eof())
		{
			getline(fin, tempstr);
			text += tempstr + "\r\n";
		}
		if (!NLPIR_Init())
		{
			cout << "NLPIR_Init() error!" << endl;
			return -1;
		}
		const char* p = text.c_str();
		string resulttext = NLPIR_ParagraphProcess(p, 1);
		string resulttext1 = NLPIR_GetKeyWords(p, 3);
		fin.close();
		cout << "本段关键字:"<<resulttext1 << endl;
		ofstream gjz("gjz.txt", ios::out);
		if (gjz.is_open())
		{
			gjz << " " << resulttext1;
			gjz.close();
		}
		NLPIR_Exit();

		vector <string> s;
		size_t s_s = 1, s_end = 0;
		while (true)
		{
			s_end = resulttext.find("/", s_s);
			string temp(resulttext, s_s + 1, s_end - s_s - 1);
			s_s = resulttext.find(" ", s_end);
			if (resulttext.find("/", s_end) == string::npos) break;
			s.push_back(temp);
		}
		//cout << s.size();
		int number;
		number = s.size();

		int j, k;
		for (j = 0; j < number; ++j)
		{
			int value = 0;
			int len = 0;
			int temp = 10000;
			char s_change[100];
			char s_other_in[100];
			i = 0;
			unsigned char a1, a2;
			//string s_input;
			string other;

			string s_cout;

			//cin >> s_input;

			len = s[j].size();
			const char *s_in = s[j].c_str();

			strcpy(s_change, s_in);

			for (i = 0; i < len;)
			{
				a1 = s_change[i];
				a2 = s_change[i + 1];

				//cout << hex << (int)a1<<(int)a2;
				other = other + change((int)a1) + change((int)a2);

				i += 2;
			}
			//cout << other<<endl;
			const char *s_other = other.c_str();

			strcpy(s_other_in, s_other);

			//const char*s = s_input.c_str();
			if (query(s_other_in, value)&&s[j-1]!="不")
				cha.push_back(word[value]);
			else if (query(s_other_in, value) && s[j - 1] == "不")
			{
				string temp = word[value];
				temp = "-" + temp;
				cha.push_back(temp);
			}
			else
				cha.push_back("No Word!");
		}


		double sort[7];
		memset(sort, 0.0, sizeof(sort));
		
		int num_cha = cha.size();
		for (i = 0; i < num_cha; ++i)
		{
			if (cha[i] == "PA" || cha[i] == "PE"||cha[i] == "-NB" || cha[i] == "-NJ" || cha[i] == "-NH" || cha[i] == "-PF")
				sort[0]++;
			if (cha[i] == "PD" || cha[i] == "PH" || cha[i] == "PG" || cha[i] == "PB" || cha[i] == "PK"|| cha[i] == "-NE" || cha[i] == "-ND" || cha[i] == "-NN" || cha[i] == "-NK" || cha[i] == "-NL"|| cha[i] == "-NI" || cha[i] == "-NC" || cha[i] == "-NG")
				sort[1]++;
			if (cha[i] == "NA"|| cha[i] == "-NA")
				sort[2]++;
			if (cha[i] == "NB" || cha[i] == "NJ" || cha[i] == "NH" || cha[i] == "PF"|| cha[i] == "-PA" || cha[i] == "-PE")
				sort[3]++;
			if (cha[i] == "NI" || cha[i] == "NC" || cha[i] == "NG")
				sort[4]++;
			if (cha[i] == "NE" || cha[i] == "ND" || cha[i] == "NN" || cha[i] == "NK" || cha[i] == "NL"|| cha[i] == "-PD" || cha[i] == "-PH" || cha[i] == "-PG" || cha[i] == "-PB" || cha[i] == "-PK")
				sort[5]++;
			if (cha[i] == "PC")
				sort[6]++;
		}
		double sort_sum=0;
		for (i = 0; i < 7; ++i)
		{
			sort_sum += sort[i];
		}

		if (sort_sum == 0)
			sort_sum = 1;
		cout << "乐指数：" << sort[0] / sort_sum * 100 << "%" << endl;
		cout << "好指数：" << sort[1] / sort_sum * 100 << "%" << endl;
		cout << "怒指数：" << sort[2] / sort_sum * 100 << "%" << endl;
		cout << "哀指数：" << sort[3] / sort_sum * 100 << "%" << endl;
		cout << "惧指数：" << sort[4] / sort_sum * 100 << "%" << endl;
		cout << "恶指数：" << sort[5] / sort_sum * 100 << "%" << endl;
		cout << "惊指数：" << sort[6] / sort_sum * 100 << "%" << endl;
		
		ofstream qx("qx.txt", ios::out);
		if (qx.is_open())
		{
			qx << "乐指数：" << sort[0] / sort_sum * 100 << "%" << endl;
			qx << "好指数：" << sort[1] / sort_sum * 100 << "%" << endl;
			qx << "怒指数：" << sort[2] / sort_sum * 100 << "%" << endl;
			qx << "哀指数：" << sort[3] / sort_sum * 100 << "%" << endl;
			qx << "惧指数：" << sort[4] / sort_sum * 100 << "%" << endl;
			qx << "恶指数：" << sort[5] / sort_sum * 100 << "%" << endl;
			qx << "惊指数：" << sort[6] / sort_sum * 100 << "%" << endl;
			qx.close();
		}

		s.clear();
		cha.clear();
	/*}*/
	return 0;
}
