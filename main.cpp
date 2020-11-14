#include "MusicMci.h"
#include <stdio.h>
#include <locale.h>

// wstring��stringת��������Ҫ�õ�ͷ
#include <comutil.h>  
#pragma comment(lib, "comsuppw.lib")

#include <string>
using namespace std;

// ��Դ�ļ�·��
#define RES_PATH L"./res/"

// ����
struct ChineseWord
{
	wstring word;
	int syllable_num = 0;
	wstring syllable[6];
};

int nDictionarySize = 0/*25*/;
ChineseWord* chDictionary;/*[] = {
{ L"��", 1, { L"a1" } },
{ L"��", 1, { L"a1" } },
{ L"��", 2, { L"a1", L"i1" } },
{ L"��", 2, { L"a1", L"i1" } },
{ L"��", 2, { L"a1", L"i1" } },
{ L"��", 2, { L"a3", L"i1" } },
{ L"��", 2, { L"a4", L"i1" } },
{ L"��", 2, { L"a4", L"i1" } },
{ L"��", 2, { L"a1", L"n" } },
{ L"��", 2, { L"a4", L"n" } },
{ L"��", 2, { L"a4", L"n" } },
{ L"��", 2, { L"a4", L"n" } },
{ L"��", 2, { L"a4", L"n" } },
{ L"��", 3, { L"a2", L"n", L"g" } },
{ L"��", 2, { L"a3", L"o" } },
{ L"��", 2, { L"a4", L"o" } },
{ L"��", 2, { L"a4", L"o" } },

{ L"��", 5, { L"c", L"h", L"e2", L"n", L"g" } },
{ L"��", 2, { L"k", L"e3" } },
{ L"��", 3, { L"j", L"i1", L"a1" } },
{ L"��", 3, { L"s", L"h", L"i4" } },

{ L"��", 3, { L"z", L"o1", L"u1" } },
{ L"��", 3, { L"h", L"u1", L"i4" } },
{ L"��", 4, { L"d", L"o1", L"n", L"g" } },

{ L"��", 2, { L"w", L"o3" } },
{ L"��", 2, { L"n", L"i3" } },
{ L"��", 2, { L"t", L"a1" } },
{ L"��", 2, { L"h", L"a1" } },
};*/

// ƴ��
MusicMCI sound_a1, sound_a2, sound_a3, sound_a4,
sound_b, sound_c, sound_d, sound_e1, sound_e2, sound_e3, sound_e4,
sound_f, sound_g, sound_h, sound_i1, sound_i2, sound_i3, sound_i4,
sound_j, sound_k, sound_l, sound_m, sound_n, sound_o1, sound_o2, sound_o3, sound_o4,
sound_p, sound_q, sound_r, sound_s, sound_t, sound_u1, sound_u2, sound_u3, sound_u4,
sound_v1, sound_v2, sound_v3, sound_v4, sound_w, sound_x, sound_y, sound_z;

// string -> wstring
wstring s2ws(const string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	wstring result = pwchar;
	return result;
}

// ��ȡ�ļ������Զ�ת��Ϊwstring
wstring ReadFileWstring(const WCHAR* file_path)
{
	FILE* fp;
	_wfopen_s(&fp, file_path, L"r");

	int size = _filelength(_fileno(fp)) * 2;
	char* ch = new char[size];
	memset(ch, 0, size);
	fread_s(ch, size, size, 1, fp);
	fclose(fp);
	return s2ws(ch);
}

bool wstringWordCmp(const WCHAR word1, wstring word2)
{
	return word1 == word2[0];
}

void init_dictionary()
{
	/*

	���ֿ��ʽ��׼������

	��
	��
	��
	��
	��i
	��

	��������ƴ����ż���������Σ�ƴ������һ�������Ӧ�����Σ��Դ����ơ�

	*/

	// ��ȡ���ֿ�
	wstring str_dictionary = ReadFileWstring(RES_PATH L"dictionary/dictionary.txt");

	// �����ļ���������ʻ���
	int nLinesNum = 1;
	for (int i = 0; i < (int)str_dictionary.size(); i++)
		if (str_dictionary[i] == '\n')
			nLinesNum++;

	nDictionarySize = nLinesNum;
	chDictionary = new ChineseWord[nDictionarySize];

	int nNowDictionaryNums = 0;

	for (int i = 0; i < (int)str_dictionary.size(); i++)
	{
		// ��ǰ�ֵ�ҳ��ָ��
		ChineseWord* thisWord = &chDictionary[nNowDictionaryNums];

		// ��ȡ�ֽ����ֵ�
		for (int j = 0;; j++)
		{
			// ���������У���ʾ����ƴ���Ѿ�����
			if (str_dictionary[i + j] == '\n')
			{
				// i��λ���ƶ����û��еĺ�һ���ַ�
				i += j + 1;
				// ���к�ĵ�һ���ַ����Ǹ�ƴ������Ӧ�ĺ��֣����������ֵ䡣
				thisWord->word = str_dictionary[i];
				// ���ֺ�����һ�����У���i������
				i++;
				break;
			}

			// ���ɸ���ƴ��
			if (wstringWordCmp(str_dictionary[i + j], L"a"))
				thisWord->syllable[thisWord->syllable_num] = L"a1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"a1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"a2";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"a3";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"a4";
			else if (wstringWordCmp(str_dictionary[i + j], L"b"))
				thisWord->syllable[thisWord->syllable_num] = L"b";
			else if (wstringWordCmp(str_dictionary[i + j], L"c"))
				thisWord->syllable[thisWord->syllable_num] = L"c";
			else if (wstringWordCmp(str_dictionary[i + j], L"d"))
				thisWord->syllable[thisWord->syllable_num] = L"d";
			else if (wstringWordCmp(str_dictionary[i + j], L"e"))
				thisWord->syllable[thisWord->syllable_num] = L"e1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"e1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"e2";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"e3";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"e4";
			else if (wstringWordCmp(str_dictionary[i + j], L"f"))
				thisWord->syllable[thisWord->syllable_num] = L"f";
			else if (wstringWordCmp(str_dictionary[i + j], L"g"))
				thisWord->syllable[thisWord->syllable_num] = L"g";
			else if (wstringWordCmp(str_dictionary[i + j], L"h"))
				thisWord->syllable[thisWord->syllable_num] = L"h";
			else if (wstringWordCmp(str_dictionary[i + j], L"i"))
				thisWord->syllable[thisWord->syllable_num] = L"i1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"i1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"i2";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"i3";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"i4";
			else if (wstringWordCmp(str_dictionary[i + j], L"j"))
				thisWord->syllable[thisWord->syllable_num] = L"j";
			else if (wstringWordCmp(str_dictionary[i + j], L"k"))
				thisWord->syllable[thisWord->syllable_num] = L"k";
			else if (wstringWordCmp(str_dictionary[i + j], L"l"))
				thisWord->syllable[thisWord->syllable_num] = L"l";
			else if (wstringWordCmp(str_dictionary[i + j], L"m"))
				thisWord->syllable[thisWord->syllable_num] = L"m";
			else if (wstringWordCmp(str_dictionary[i + j], L"n"))
				thisWord->syllable[thisWord->syllable_num] = L"n";
			else if (wstringWordCmp(str_dictionary[i + j], L"o"))
				thisWord->syllable[thisWord->syllable_num] = L"o1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"o1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"o2";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"o3";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"o4";
			else if (wstringWordCmp(str_dictionary[i + j], L"p"))
				thisWord->syllable[thisWord->syllable_num] = L"p";
			else if (wstringWordCmp(str_dictionary[i + j], L"q"))
				thisWord->syllable[thisWord->syllable_num] = L"q";
			else if (wstringWordCmp(str_dictionary[i + j], L"r"))
				thisWord->syllable[thisWord->syllable_num] = L"r";
			else if (wstringWordCmp(str_dictionary[i + j], L"s"))
				thisWord->syllable[thisWord->syllable_num] = L"s";
			else if (wstringWordCmp(str_dictionary[i + j], L"t"))
				thisWord->syllable[thisWord->syllable_num] = L"t";
			else if (wstringWordCmp(str_dictionary[i + j], L"u"))
				thisWord->syllable[thisWord->syllable_num] = L"u1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"u1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"u2";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"u3";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"u4";
			else if (wstringWordCmp(str_dictionary[i + j], L"v"))
				thisWord->syllable[thisWord->syllable_num] = L"v1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"v1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"v1";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"v2";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"v3";
			else if (wstringWordCmp(str_dictionary[i + j], L"��"))
				thisWord->syllable[thisWord->syllable_num] = L"v4";
			else if (wstringWordCmp(str_dictionary[i + j], L"w"))
				thisWord->syllable[thisWord->syllable_num] = L"w";
			else if (wstringWordCmp(str_dictionary[i + j], L"x"))
				thisWord->syllable[thisWord->syllable_num] = L"x";
			else if (wstringWordCmp(str_dictionary[i + j], L"y"))
				thisWord->syllable[thisWord->syllable_num] = L"y";
			else if (wstringWordCmp(str_dictionary[i + j], L"z"))
				thisWord->syllable[thisWord->syllable_num] = L"z";

			// ƴ����������
			thisWord->syllable_num++;
		}

		nNowDictionaryNums++;
	}

	// �����ʻ�����
	nDictionarySize = nNowDictionaryNums;
}

void init_pinyin()
{
	sound_a1.open(RES_PATH L"pinyin/a1.mp3");
	sound_a2.open(RES_PATH L"pinyin/a2.mp3");
	sound_a3.open(RES_PATH L"pinyin/a3.mp3");
	sound_a4.open(RES_PATH L"pinyin/a4.mp3");
	sound_b.open(RES_PATH L"pinyin/b.mp3");
	sound_c.open(RES_PATH L"pinyin/c.mp3");
	sound_d.open(RES_PATH L"pinyin/d.mp3");
	sound_e1.open(RES_PATH L"pinyin/e1.mp3");
	sound_e2.open(RES_PATH L"pinyin/e2.mp3");
	sound_e3.open(RES_PATH L"pinyin/e3.mp3");
	sound_e4.open(RES_PATH L"pinyin/e4.mp3");
	sound_f.open(RES_PATH L"pinyin/f.mp3");
	sound_g.open(RES_PATH L"pinyin/g.mp3");
	sound_h.open(RES_PATH L"pinyin/h.mp3");
	sound_i1.open(RES_PATH L"pinyin/i1.mp3");
	sound_i2.open(RES_PATH L"pinyin/i2.mp3");
	sound_i3.open(RES_PATH L"pinyin/i3.mp3");
	sound_i4.open(RES_PATH L"pinyin/i4.mp3");
	sound_j.open(RES_PATH L"pinyin/j.mp3");
	sound_k.open(RES_PATH L"pinyin/k.mp3");
	sound_l.open(RES_PATH L"pinyin/l.mp3");
	sound_m.open(RES_PATH L"pinyin/m.mp3");
	sound_n.open(RES_PATH L"pinyin/n.mp3");
	sound_o1.open(RES_PATH L"pinyin/o1.mp3");
	sound_o2.open(RES_PATH L"pinyin/o2.mp3");
	sound_o3.open(RES_PATH L"pinyin/o3.mp3");
	sound_o4.open(RES_PATH L"pinyin/o4.mp3");
	sound_p.open(RES_PATH L"pinyin/p.mp3");
	sound_q.open(RES_PATH L"pinyin/q.mp3");
	sound_r.open(RES_PATH L"pinyin/r.mp3");
	sound_s.open(RES_PATH L"pinyin/s.mp3");
	sound_t.open(RES_PATH L"pinyin/t.mp3");
	sound_u1.open(RES_PATH L"pinyin/u1.mp3");
	sound_u2.open(RES_PATH L"pinyin/u2.mp3");
	sound_u3.open(RES_PATH L"pinyin/u3.mp3");
	sound_u4.open(RES_PATH L"pinyin/u4.mp3");
	sound_v1.open(RES_PATH L"pinyin/v1.mp3");
	sound_v2.open(RES_PATH L"pinyin/v2.mp3");
	sound_v3.open(RES_PATH L"pinyin/v3.mp3");
	sound_v4.open(RES_PATH L"pinyin/v4.mp3");
	sound_w.open(RES_PATH L"pinyin/w.mp3");
	sound_x.open(RES_PATH L"pinyin/x.mp3");
	sound_y.open(RES_PATH L"pinyin/y.mp3");
	sound_z.open(RES_PATH L"pinyin/z.mp3");
}

// ��������
// str��Ҫ˵�Ļ�
// word_delay��ÿ���ֵķ�����ʱ��ms��
void speak(wstring str, int word_delay = 500)
{
	// ��ѭ��
	for (int _i = 0; _i < (int)str.length(); _i++)
	{
		// ������̬��ʱ
		int spend = clock();

		// ����ѭ��
		for (int _j = 0; _j < nDictionarySize; _j++)
		{
			// �ȶ����Ƿ�һ��
			if (chDictionary[_j].word[0] == str[_i])
			{
				// ����ÿ����
				for (int _k = 0; _k < chDictionary[_i].syllable_num; _k++)
				{
					if (chDictionary[_j].syllable[_k] == L"a1")
					{
						sound_a1.setStartTime(0);
						sound_a1.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"a2")
					{
						sound_a2.setStartTime(0);
						sound_a2.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"a3")
					{
						sound_a3.setStartTime(0);
						sound_a3.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"a4")
					{
						sound_a4.setStartTime(0);
						sound_a4.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"b")
					{
						sound_b.setStartTime(0);
						sound_b.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"c")
					{
						sound_c.setStartTime(0);
						sound_c.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"d")
					{
						sound_d.setStartTime(0);
						sound_d.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"e1")
					{
						sound_e1.setStartTime(0);
						sound_e1.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"e2")
					{
						sound_e2.setStartTime(0);
						sound_e2.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"e3")
					{
						sound_e3.setStartTime(0);
						sound_e3.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"e4")
					{
						sound_e4.setStartTime(0);
						sound_e4.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"f")
					{
						sound_f.setStartTime(0);
						sound_f.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"g")
					{
						sound_g.setStartTime(0);
						sound_g.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"h")
					{
						sound_h.setStartTime(0);
						sound_h.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"i1")
					{
						sound_i1.setStartTime(0);
						sound_i1.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"i2")
					{
						sound_i2.setStartTime(0);
						sound_i2.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"i3")
					{
						sound_i3.setStartTime(0);
						sound_i3.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"i4")
					{
						sound_i4.setStartTime(0);
						sound_i4.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"j")
					{
						sound_j.setStartTime(0);
						sound_j.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"k")
					{
						sound_k.setStartTime(0);
						sound_k.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"l")
					{
						sound_l.setStartTime(0);
						sound_l.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"m")
					{
						sound_m.setStartTime(0);
						sound_m.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"n")
					{
						sound_n.setStartTime(0);
						sound_n.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"o1")
					{
						sound_o1.setStartTime(0);
						sound_o1.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"o2")
					{
						sound_o2.setStartTime(0);
						sound_o2.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"o3")
					{
						sound_o3.setStartTime(0);
						sound_o3.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"o4")
					{
						sound_o4.setStartTime(0);
						sound_o4.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"p")
					{
						sound_p.setStartTime(0);
						sound_p.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"l")
					{
						sound_q.setStartTime(0);
						sound_q.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"r")
					{
						sound_r.setStartTime(0);
						sound_r.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"s")
					{
						sound_s.setStartTime(0);
						sound_s.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"t")
					{
						sound_t.setStartTime(0);
						sound_t.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"u1")
					{
						sound_u1.setStartTime(0);
						sound_u1.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"u2")
					{
						sound_u2.setStartTime(0);
						sound_u2.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"u3")
					{
						sound_u3.setStartTime(0);
						sound_u3.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"u4")
					{
						sound_u4.setStartTime(0);
						sound_u4.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"v1")
					{
						sound_v1.setStartTime(0);
						sound_v1.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"v2")
					{
						sound_v2.setStartTime(0);
						sound_v2.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"v3")
					{
						sound_v3.setStartTime(0);
						sound_v3.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"v4")
					{
						sound_v4.setStartTime(0);
						sound_v4.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"w")
					{
						sound_w.setStartTime(0);
						sound_w.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"x")
					{
						sound_x.setStartTime(0);
						sound_x.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"y")
					{
						sound_y.setStartTime(0);
						sound_y.play();
					}
					else if (chDictionary[_j].syllable[_k] == L"z")
					{
						sound_z.setStartTime(0);
						sound_z.play();
					}
				}

				break;
			}
		}

		// ����ķ�ʱ��
		spend = clock() - spend;
		// ��̬��ʱ
		Sleep(word_delay - spend > 0 ? word_delay - spend : 1);
	}
}

void user()
{
	while (true)
	{
		wchar_t str[1024] = { 0 };
		printf("\n");
		printf("���������֣��䣩��Ȼ��س���\n");
		wscanf_s(L"%s", str, 1024);
		speak(str);
		printf("�ѷ���������\n");
	}
}

int main()
{
	setlocale(LC_ALL, "chs");
	printf("speakor ������\n");

	printf("����ƴ����Դ�ļ�����\n");
	init_pinyin();

	printf("���غ��ֿ��ļ�����\n");
	init_dictionary();

	printf("������Դ�ļ���ϡ�\n");
	user();
	return 0;
}
