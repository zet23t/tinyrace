#include "font_asset.h"
namespace FontAsset {
	static const SpriteGlyph fontGlyphs[93] = {
			{' ',0,0,0,0,2,0,0},
		{'A',0,0,3,6,4,0,0},
		{'B',4,0,3,6,4,0,0},
		{'C',8,0,3,6,4,0,0},
		{'D',12,0,3,6,4,0,0},
		{'E',16,0,3,6,4,0,0},
		{'F',20,0,3,6,4,0,0},
		{'G',24,0,3,6,4,0,0},
		{'H',28,0,3,6,4,0,0},
		{'I',32,0,3,6,4,0,0},
		{'J',36,0,3,6,4,0,0},
		{'K',40,0,3,6,4,0,0},
		{'L',44,0,3,6,4,0,0},
		{'M',48,0,5,6,6,0,0},
		{'N',54,0,4,6,5,0,0},
		{'O',59,0,4,6,5,0,0},
		{'P',64,0,3,6,4,0,0},
		{'Q',68,0,4,6,5,0,0},
		{'R',73,0,3,6,4,0,0},
		{'S',77,0,3,6,4,0,0},
		{'T',81,0,3,6,4,0,0},
		{'U',85,0,4,6,5,0,0},
		{'V',90,0,5,6,6,0,0},
		{'W',96,0,5,6,6,0,0},
		{'X',102,0,3,6,4,0,0},
		{'Y',106,0,3,6,4,0,0},
		{'Z',110,0,3,6,4,0,0},
		{'a',0,7,3,4,4,0,1},
		{'b',4,6,3,5,4,0,0},
		{'c',8,7,3,4,4,0,1},
		{'d',12,6,3,5,4,0,0},
		{'e',16,7,3,4,4,0,1},
		{'f',20,6,3,5,3,0,0},
		{'g',23,7,3,5,4,0,1},
		{'h',27,6,3,5,4,0,0},
		{'i',31,6,1,5,2,0,0},
		{'j',33,6,2,6,3,0,0},
		{'k',36,6,3,5,4,0,0},
		{'l',40,6,2,5,3,0,0},
		{'m',43,7,5,4,6,0,1},
		{'n',49,7,3,4,4,0,1},
		{'o',53,7,3,4,4,0,1},
		{'p',57,7,3,5,4,0,1},
		{'q',61,7,3,5,4,0,1},
		{'r',65,7,3,4,4,0,1},
		{'s',69,7,3,4,4,0,1},
		{'t',73,6,2,5,3,0,0},
		{'u',76,7,3,4,4,0,1},
		{'v',80,7,3,4,4,0,1},
		{'w',84,7,5,4,6,0,1},
		{'x',90,7,3,4,4,0,1},
		{'y',94,7,3,5,4,0,1},
		{'z',98,7,3,5,4,0,1},
		{'0',0,13,3,5,4,0,0},
		{'1',4,13,3,5,4,0,0},
		{'2',8,13,3,5,4,0,0},
		{'3',12,13,3,5,4,0,0},
		{'4',16,13,3,5,4,0,0},
		{'5',20,13,3,5,4,0,0},
		{'6',24,13,3,5,4,0,0},
		{'7',28,13,3,5,4,0,0},
		{'8',32,13,3,5,4,0,0},
		{'9',36,13,3,5,4,0,0},
		{'-',40,13,3,5,4,0,0},
		{'+',44,13,3,5,4,0,0},
		{'/',48,13,4,5,5,0,0},
		{':',53,13,1,5,2,0,0},
		{';',55,13,2,6,3,0,0},
		{',',58,17,2,2,3,0,4},
		{'.',61,17,2,2,3,0,4},
		{'?',63,13,3,5,4,0,0},
		{0,0,0,0,0,0,0,0},
		{'%',71,13,5,5,6,0,0},
		{'&',77,13,4,5,5,0,0},
		{'$',82,13,5,5,6,0,0},
		{'(',88,13,2,5,3,0,0},
		{')',91,13,2,5,3,0,0},
		{'[',94,13,2,5,3,0,0},
		{']',97,13,2,5,3,0,0},
		{'<',100,13,3,5,4,0,0},
		{'>',104,13,3,5,4,0,0},
		{'=',108,13,3,5,4,0,0},
		{'{',112,13,3,5,4,0,0},
		{'}',116,13,3,5,4,0,0},
		{'\'',120,13,1,2,2,0,0},
		{'"',122,13,3,2,4,0,0},
		{'^',0,19,3,2,4,0,0},
		{0,0,0,0,0,0,0,0},
		{'\\',8,19,4,5,5,0,0},
		{'!',13,19,1,5,2,0,0},
		{'*',15,19,3,4,4,0,0},
		{'|',19,19,1,5,2,0,0},
		{'_',21,23,3,1,4,0,4},
	};
	const SpriteFont font = {6,fontGlyphs,93,&ImageAsset::font};
		static const SpriteGlyph font2Glyphs[93] = {
			{' ',0,0,0,7,3,0,0},
		{'A',0,0,4,7,5,0,0},
		{'B',5,0,4,7,5,0,0},
		{'C',10,0,4,7,5,0,0},
		{'D',15,0,4,7,5,0,0},
		{'E',20,0,4,7,5,0,0},
		{'F',25,0,4,7,5,0,0},
		{'G',30,0,4,7,5,0,0},
		{'H',35,0,4,7,5,0,0},
		{'I',40,0,3,7,4,0,0},
		{'J',44,0,4,7,5,0,0},
		{'K',49,0,4,7,5,0,0},
		{'L',54,0,4,7,5,0,0},
		{'M',59,0,5,7,6,0,0},
		{'N',65,0,4,7,5,0,0},
		{'O',70,0,4,7,5,0,0},
		{'P',75,0,4,7,5,0,0},
		{'Q',80,0,4,7,5,0,0},
		{'R',85,0,4,7,5,0,0},
		{'S',90,0,4,7,5,0,0},
		{'T',95,0,5,7,6,0,0},
		{'U',101,0,4,7,5,0,0},
		{'V',106,0,5,7,6,0,0},
		{'W',112,0,5,7,6,0,0},
		{'X',118,0,5,7,6,0,0},
		{'Y',123,0,5,7,6,0,0},
		{'Z',0,8,5,7,6,0,0},
		{'a',7,10,4,5,5,0,2},
		{'b',12,8,4,7,5,0,0},
		{'c',17,10,4,5,5,0,2},
		{'d',22,8,4,7,5,0,0},
		{'e',27,10,4,5,5,0,2},
		{'f',32,8,2,7,3,0,0},
		{'g',35,10,4,7,5,0,2},
		{'h',40,8,4,7,5,0,0},
		{'i',45,8,1,7,2,0,0},
		{'j',47,8,2,9,2,-1,0},
		{'k',50,8,4,7,5,0,0},
		{'l',55,8,2,7,3,0,0},
		{'m',58,10,5,5,6,0,2},
		{'n',64,10,4,5,5,0,2},
		{'o',68,10,4,5,5,0,2},
		{'p',73,10,4,7,5,0,2},
		{'q',78,10,4,7,5,0,2},
		{'r',83,10,4,5,5,0,2},
		{'s',88,10,4,5,5,0,2},
		{'t',92,8,3,7,4,0,0},
		{'u',96,10,4,5,5,0,2},
		{'v',101,10,5,5,6,0,2},
		{'w',107,10,5,5,6,0,2},
		{'x',113,10,5,5,6,0,2},
		{'y',119,10,4,7,5,0,2},
		{'z',124,10,4,5,5,0,2},
		{'0',0,18,3,7,4,0,0},
		{'1',4,18,3,7,4,0,0},
		{'2',8,18,3,7,4,0,0},
		{'3',12,18,3,7,4,0,0},
		{'4',16,18,3,7,4,0,0},
		{'5',20,18,3,7,4,0,0},
		{'6',24,18,3,7,4,0,0},
		{'7',28,18,3,7,4,0,0},
		{'8',32,18,3,7,4,0,0},
		{'9',36,18,3,7,4,0,0},
		{'-',40,13,3,5,4,0,0},
		{'+',44,13,3,5,4,0,0},
		{'/',48,13,4,5,5,0,0},
		{':',53,13,1,5,2,0,0},
		{';',55,13,2,6,3,0,0},
		{',',58,17,2,2,3,0,4},
		{'.',61,17,2,2,3,0,4},
		{'?',63,13,3,5,4,0,0},
		{0,0,0,0,0,0,0,0},
		{'%',71,13,5,5,6,0,0},
		{'&',77,13,4,5,5,0,0},
		{'$',82,13,5,5,6,0,0},
		{'(',88,13,2,5,3,0,0},
		{')',91,13,2,5,3,0,0},
		{'[',94,13,2,5,3,0,0},
		{']',97,13,2,5,3,0,0},
		{'<',100,13,3,5,4,0,0},
		{'>',104,13,3,5,4,0,0},
		{'=',108,13,3,5,4,0,0},
		{'{',112,13,3,5,4,0,0},
		{'}',116,13,3,5,4,0,0},
		{'\'',120,13,1,2,2,0,0},
		{'"',122,13,3,2,4,0,0},
		{'^',0,19,3,2,4,0,0},
		{0,0,0,0,0,0,0,0},
		{'\\',8,19,4,5,5,0,0},
		{'!',13,19,1,5,2,0,0},
		{'*',15,19,3,4,4,0,0},
		{'|',19,19,1,5,2,0,0},
		{'_',21,23,3,1,4,0,4},
	};
	const SpriteFont font2 = {9,font2Glyphs,93,&ImageAsset::font2};
	
}
