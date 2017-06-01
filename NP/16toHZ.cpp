#include"16toHZ.h"
#include <string>
#include<iostream>
using namespace std;
void HEX2HZ:: hex_hz() {
	int i = 0, v;
	char bs[33];
	char b[33];
	char hs[9];
	char h[9];
	char s[4];
	char *e;
	string h2;
	cin >> h2;
	const char *h3 = h2.c_str();
	strcpy_s(hs, h3);

	while (true)
	{
		if (1 != sscanf_s(hs + i * 2, "%2x", &v)) break;
		s[i] = (char)v;
		++i;
	}
	s[i] = 0;
	printf("hs=%s,s=%s\n", hs, s);
}
