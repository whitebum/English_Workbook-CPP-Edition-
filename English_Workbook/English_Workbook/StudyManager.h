#pragma once

static vector<Problem>Workbook;
static vector<Problem>WrongWord;
static vector<Problem>WrongIverb;
static vector<Problem>WrongProverb;

class Launcher : public Singleton<Launcher>
{
private:

	string Version = "Ver 1.7";
	int Act = 0;

public:

	void MainMenu();
	void StudyMenu();
	void PreviewMenu();

	Launcher() {}
	~Launcher() {}

};

static bool isRightAnswer(vector<string>Solution, string Answer)
{
	for (auto iter : Solution) {
		if (iter == Answer) { return true; }
		else if (Answer == " " + iter) { return true; }
		else if (Answer == iter + " ") { return true; }
	}

	return false;
}

class WorkbookManager : public Singleton<WorkbookManager>
{
private: 

	int Act = 0;

	int Right = 0;
	int Wrong = 0;
	int Turn = 0;
	std::string Answer = "This Is Default Answer.";

private:

	bool Create_Workbook(Type type);
	bool Create_All_Workbook();

public:

	void Study_All();
	void Study_Word();
	void Study_IVerb();
	void Study_Proverb();

	WorkbookManager() {}
	~WorkbookManager() {}

};

class WrongbookManager : public Singleton<WrongbookManager>
{
private:

	int Act = 0;

	int Right = 0;
	int Wrong = 0;
	int Turn = 0;
	std::string Answer = "This Is Default Answer.";

	vector<Problem>Copy;

public:

	inline void Copy_Wrongbook();
	inline void Copy_Wrongbook(vector<Problem>Reference);

	void WrongNote_List();

	void Review_All();
	void Preview_Word();
	void Preview_IVerb();
	void Preview_Proverb();

	WrongbookManager() {}
	~WrongbookManager() {}

};