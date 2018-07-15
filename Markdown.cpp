// Markdown.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include<iostream>
#include <string>
using namespace std;

void header(string &s)
{
	int i = 0;
	while (s[i] == '#')i++;
	s.erase(0, i);
	string h = "<h"; 
	char c = i + '0';
	h = h +c+ ">";
	s = h + s;
	h.insert(1, "/");
	s = s+h;
}
void llist(string &s)
{
	string li = "<li>";
	s.erase(0, 1);
	s = li + s;
	li = "</li>";
	s = s + li;
}
void text(string &s)
{
	int i = 0;
	while (i < s.length())
	{
		if (s[i] == '*' && s[i + 1] == '*')
		{
			s.erase(i, 2);
			s.insert(i, "<strong>");
			i += 8;
			while (s[i] != '*' && s[i + 1] != '*') i++;
			i++;
			s.erase(i, 2);
			s.insert(i, "</strong>");
			i += 8;
		}
		if (s[i] == '_')
		{
			s.erase(i, 1);
			s.insert(i, "<em>");
			i += 4;
			while (s[i] != '_') i++;
			s.erase(i, 1);
			s.insert(i, "</em>");
			i += 4;
		}
		i++;
		if (s[i] == '`')
		{
			s.erase(i, 1);
			s.insert(i, "<code>");
			i += 6;
			while (s[i] != '`') i++;
			s.erase(i, 1);
			s.insert(i, "</code>");
			i += 6;
		}

	}


}
void check(string &s, bool &IfThisIsList, bool &IfThisIsParagraph)
{
	if (s[0] == '#')
	{
		header(s);
		if (IfThisIsList) {
			s =  "</ul>\n"+s;
			IfThisIsList = false;
		}
		if (IfThisIsParagraph)
		{
			s = "</p>\n" + s;
			IfThisIsParagraph = false;
		}
	}
	else {
		if (s[0] == '*')
		{
			llist(s);
			if (!IfThisIsList) {
				IfThisIsList = true;
				s = "<ul>\n" + s;
			}
			if (IfThisIsParagraph)
			{
				s = "</p>\n" + s;
				IfThisIsParagraph = false;
			}
		}
		else {
			text(s);
			if (!IfThisIsParagraph) {
				s = "<p>\n"+s;
				IfThisIsParagraph = true;
			}
			else
				s = "<br /> " + s;
			if (IfThisIsList) {
				s = "</ul>\n" + s;
				IfThisIsList = false;
			}
			
		}
	}
}

int main()
{
	fstream input("input.txt");
	fstream output("output.txt");
	string s, result;
	s = "<html>\n<body>\n";
	output << s;
	bool IfThisIsList = false;
	bool IfThisIsParagraph = false;
	while (!input.eof())
	{
		getline(input, s);
		 check(s,IfThisIsList, IfThisIsParagraph);
		output << s<<endl;
	}
	if (IfThisIsParagraph) s = "</p>\n";
	if (IfThisIsList) s = "</ul>\n";
	s = s+ "</body> \n</html>\n";
	output << s;
    return 0;
}

