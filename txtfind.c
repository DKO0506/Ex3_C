#include <stdio.h>
#include <string.h>

#define LINE 256
#define WORD 30

int condition(char chosen[], char ch)
{
	if (!strcmp(chosen, "line") && ch == '\n') //strcmp(chosen, "line") == 0 means strings are equals
		return 0;
	else if (!strcmp(chosen, "word") && (ch == ' ' || ch == '\t' || ch == '\n')) 
		return 0;
	return 1;
}

int getChars(char chosen[], char s[], FILE* file)
{
	if (file == NULL)
		return 0;
	char ch = fgetc(file);
	if (ch == EOF)
		return 0;
	int numOfChars;

	for (numOfChars = 0; condition(chosen, ch) && ch != EOF ; numOfChars++)
	{
		s[numOfChars] = ch;
		ch = fgetc(file);
		if (ch == EOF)
			return numOfChars;
	}
	s[numOfChars] = '\0';
	return numOfChars;
}

int getLine(char s[], FILE* file)
{
	char line[] = "line";
	return getChars(line, s, file);
}

int getword(char w[], FILE* file)
{
	char word[] = "word";
	return getChars(word, w, file);
}

int substring(char * str1, char * str2)
{
	if (!strcmp(str1, str2))
		return 1;

	int i = 0;
	while (*(str1 + i) != '\0')
	{
		int j = 0;
		if (*(str1 + i) == *(str2 + j))
		{
			while((*(str1 + i) != '\n' || *(str2 + j) != '\n') && (*(str1 + i) == *(str2 + j)))
			{
				j++;
				i++;
			}
			if (*(str2 + j) == '\0')
				return 1;
		}
		i++;
	}
	return 0;
}

void print_lines(char * str, FILE* file)
{
	char line[LINE];
	char temp[LINE];

	int i = 0;
	int noChars = getLine(line, file);
	strcpy(temp, line);

	while (noChars != 0)
	{
		char *word;
		word = strtok(temp, " \n"); //split line to words

		//walk through other words
		while (word != NULL) 
		{
			if (substring(word, str))
			{
				printf("%s\n", line);
				break;
			}
			word = strtok(NULL, " \n");
		}
		
		noChars = getLine(line, file);
		strcpy(temp, line);
	}
}

int similar(char *s, char *t, int n)
{
	int j = 0;
	int diffChars = 0;
	int sizeT = strlen(t);

	for (int i = 0; *(s + i) != '\0'; i++)
	{
		if (*(s + i) == *(t + j))
			j++;
		
		else
			diffChars++;
	}
	if (j == sizeT && diffChars <= n)
		return 1;
	return 0;
}

void print_similar_words(char * str, FILE* f)
{
	char word[WORD];
	int noChars = getword(word, f);
	while (noChars != 0)
	{
		if(similar(word, str, 1) == 1)
			printf("%s\n", word);
		noChars = getword(word, f);
	}
}

//