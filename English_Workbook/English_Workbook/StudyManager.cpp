#include "Header.h"

bool WorkbookManager::Create_Workbook(Type type)
{
	ControlManager::GetInstance().Reset_Workbook(Workbook);
	string filePath;

#ifdef _DEBUG

	switch (type) {
	case Type::WORD:
		filePath = "StudyFile/Word";
		break;
	case Type::IVERB:
		filePath = "StudyFile/IVerb";
		break;
	case Type::PROVERB:
		filePath = "StudyFile/Proverb";
		break;
	case Type::DEFAULT:
	default:
		type = Type::DEFAULT;
		break;
	}

#else

	switch (type) {
	case Type::WORD:
		filePath = "English_Workbook/StudyFile/Word";
		break;
	case Type::IVERB:
		filePath = "English_Workbook/StudyFile/IVerb";
		break;
	case Type::PROVERB:
		filePath = "English_Workbook/StudyFile/Proverb";
		break;
	case Type::DEFAULT:
	default:
		type = Type::DEFAULT;
		break;
	}

#endif 

	ifstream _Que(filePath + "/Que.txt");
	ifstream _Sol(filePath + "/Sol.txt");

	if ((_Que.fail() || _Que.bad()) ||
		(_Sol.fail() || _Sol.bad())) {
		Oops;
		printf("파일 읽기에 실패했습니다!\n");
		printf("오류 파일 경로 ===>> [%s]\n", filePath.c_str());
		printf("(파일 안의 메모장을 지우거나 옮겼을 경우, 제대로 된 경로에 다시 옮겨주십시오.)");

		ControlManager::GetInstance().Press_Enter();
		return false;
	}

	while (!_Que.eof() && !_Sol.eof()) {
		string Param_Q, S, temp;
		vector<string>Param_S;

		getline(_Que, Param_Q);
		getline(_Sol, S);

		stringstream ss(S);

		while (getline(ss, temp, ';')) {
			Param_S.push_back(temp);
		}

		Workbook.push_back(Problem(Param_Q, Param_S, type));
	}

	_Que.close();
	_Sol.close();

	return true;
}

bool WorkbookManager::Create_All_Workbook()
{
	std::string Tags[3] = { "Word", "Iverb", "Proverb" };

	ControlManager::GetInstance().Reset_Workbook(Workbook);

	for (int i = 0; i < 3; ++i) {
		std::ifstream _Que("English_Workbook/StudyFile/" + Tags[i] + "/Que.txt");
		std::ifstream _Sol("English_Workbook/StudyFile/" + Tags[i] + "/Sol.txt");

		if ((_Que.fail() || _Que.bad()) ||
			(_Sol.fail() || _Sol.bad())) {
			Oops;
			printf("파일 읽기에 실패했습니다!\n");
			printf("오류 파일 경로 ===>> [English_Workbook/StudyFile/%s]\n", Tags[i].c_str());
			printf("파일 안의 메모장을 지우거나 옮겼을 경우, 제대로 된 경로에 다시 옮겨주십시오.");

			ControlManager::GetInstance().Press_Enter();
			return false;
		}

		while (!_Que.eof() && !_Sol.eof()) {
			string Param_Q, S, temp;
			vector<string>Param_S;
			Type type;

			getline(_Que, Param_Q);
			getline(_Sol, S);

			stringstream ss(S);

			while (getline(ss, temp, ';')) {
				Param_S.push_back(temp);
			}

			if (Tags[i] == "Word") { type = Type::WORD; }
			else if (Tags[i] == "IVerb") { type = Type::IVERB; }
			else if (Tags[i] == "Proverb") { type = Type::PROVERB; }
			else { type = Type::DEFAULT; }

			Workbook.push_back(Problem(Param_Q, Param_S, type));
		}

		_Que.close();
		_Sol.close();
	}
	return true;
}

void WorkbookManager::Study_All()
{
	if (!Create_All_Workbook()) return;
	ControlManager::GetInstance().Shuffle_Workbook(Workbook);

	printf("[문제 대난투 총 %d문제!]\n", static_cast<int>(Workbook.size()));
	printf("(모든 문제들이 섞여서 출제됩니다. 주의하세요!)\n");
	printf("(Enter를 누르면 바로 진행합니다...)\n");

	printf("\n\n\n<주의 사항>\n");
	printf("★(해당 모드에서 틀린 문제는 오답 노트에 기록되지 않습니다.)\n");
	printf("★(입력은 모두 한 줄로 받으며, 띄어쓰기를 구분합니다.)\n");
	printf("★(사용자가 정의한 txt파일을 통해 정답을 판단합니다.)\n");
	printf("★(사용 중에 txt파일을 건드릴 경우, 오류가 날 수 있습니다.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = Workbook.begin(); iter != Workbook.end(); ++iter, ++Turn) {

		switch (iter->type)
		{
		case Type::WORD:
			printf("<단어> [%d]문제! \"%s\"을(를) 해석하세요.", Turn + 1, iter->question.c_str());
			break;
		case Type::IVERB:
			printf("<불규칙동사> [%d번 문제] \"%s\"의 원형, 과거형, 과거분사형을 서술하세요!\n", Turn + 1, iter->question.c_str());
			break;
		case Type::PROVERB:
			printf("<속담> [%d번 문제] \"%s\"의 의미를 서술하세요!\n", Turn + 1, iter->question.c_str());
			break;
		default:
			break;
		}

#ifdef _DEBUG

		printf("정답 : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			system("cls");
			printf("[테스트 중도 포기!]\n");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[맞았습니다!] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);

			if (!WrongWord.empty()) {
				auto iter2 = remove(WrongWord.begin(), WrongWord.end(), Problem(iter->question, iter->solution, iter->type));
				WrongWord.resize(iter2 - WrongWord.begin());
			}
		}

		else if(!isRightAnswer(iter->solution, Answer)){
			++Wrong;
			printf("[틀렸습니다...] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);

			bool Trigger = false;

			if (!WrongWord.empty())
				for (auto iter2 = WrongWord.begin(); iter2 != WrongWord.end(); ++iter2)
					if (Problem(iter->question, iter->solution, iter->type) == Problem(iter2->question, iter2->solution, iter2->type))
						Trigger = true;

			if (Trigger == false) {
				switch (iter->type)
				{
				case Type::WORD:
					WrongWord.push_back(Problem(iter->question, iter->solution, iter->type));
					break;
				case Type::IVERB:
					WrongIverb.push_back(Problem(iter->question, iter->solution, iter->type));
					break;
				case Type::PROVERB:
					WrongProverb.push_back(Problem(iter->question, iter->solution, iter->type));
					break;
				default:
					break;
				}
			}

		}

		Sleep(800);
		Clear;
	}

	printf("[테스트 종료! 수고하셨습니다.]\n");
	printf("맞은 문제 : [%d]개 || 틀린 문제 : [%d]개\n", Right, Wrong);
	printf("(Enter를 누르면 메뉴로 넘어갑니다...)");

	ControlManager::GetInstance().Press_Enter();
}

void WorkbookManager::Study_Word()
{
	if (!Create_Workbook(Type::WORD)) return;
	ControlManager::GetInstance().Shuffle_Workbook(Workbook);

	printf("[단어 테스트 %d선!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter를 누르면 바로 진행합니다...)");

	printf("\n\n\n<주의 사항>\n");
	printf("★(입력은 모두 한 줄로 받으며, 띄어쓰기를 구분합니다.)\n");
	printf("★(사용자가 정의한 txt파일을 통해 정답을 판단합니다.)\n");
	printf("★(사용 중에 txt파일을 건드릴 경우, 오류가 날 수 있습니다.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = Workbook.begin(); iter != Workbook.end(); ++iter, ++Turn) {

		printf("[%d번 문제] \"%s\"을(를) 해석하세요!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("정답 : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			system("cls");
			printf("[테스트 중도 포기!]\n");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[맞았습니다!] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);

			if (!WrongWord.empty()) {
				auto iter2 = remove(WrongWord.begin(), WrongWord.end(), Problem(iter->question, iter->solution, iter->type));
				WrongWord.resize(iter2 - WrongWord.begin());
			}
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[틀렸습니다...] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);

			bool Trigger = false;

			if (!WrongWord.empty())
				for (auto iter2 = WrongWord.begin(); iter2 != WrongWord.end(); ++iter2)
					if (Problem(iter->question, iter->solution, iter->type) == Problem(iter2->question, iter2->solution, iter2->type))
						Trigger = true;

			if (Trigger == false)
				WrongWord.push_back(Problem(iter->question, iter->solution, Type::WORD));
		}

		Sleep(800);
		Clear;
	}

	printf("[테스트 종료! 수고하셨습니다.]\n");
	printf("맞은 문제 : [%d]개 || 틀린 문제 : [%d]개\n", Right, Wrong);
	printf("(Enter를 누르면 메뉴로 넘어갑니다...)");

	ControlManager::GetInstance().Press_Enter();
}

void WorkbookManager::Study_IVerb()
{
	if (!Create_Workbook(Type::IVERB)) return;
	ControlManager::GetInstance().Shuffle_Workbook(Workbook);

	printf("[불규칙동사 테스트 %d선!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter를 누르면 바로 진행합니다...)");

	printf("\n\n\n<주의 사항>\n");
	printf("★(입력은 모두 한 줄로 받으며, 띄어쓰기를 구분합니다.)\n");
	printf("★(사용자가 정의한 txt파일을 통해 정답을 판단합니다.)\n");
	printf("★(사용 중에 txt파일을 건드릴 경우, 오류가 날 수 있습니다.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = Workbook.begin(); iter != Workbook.end(); ++iter, ++Turn) {

		printf("[%d번 문제] \"%s\"의 원형, 과거형, 과거분사형을 서술하세요!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("정답 : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			printf("[테스트 중도 포기!]\n");
			system("cls");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[맞았습니다!] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);

			if (!WrongIverb.empty()) {
				auto iter2 = remove(WrongIverb.begin(), WrongIverb.end(), Problem(iter->question, iter->solution, iter->type));
				WrongIverb.resize(iter2 - WrongIverb.begin());
			}
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[틀렸습니다...] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);

			bool Trigger = false;

			if (!WrongIverb.empty())
				for (auto iter2 = WrongIverb.begin(); iter2 != WrongIverb.end(); ++iter2)
					if (Problem(iter->question, iter->solution, iter->type) == Problem(iter2->question, iter2->solution, iter2->type))
						Trigger = true;

			if (Trigger == false)
				WrongIverb.push_back(Problem(iter->question, iter->solution, Type::IVERB));
		}

		Sleep(800);
		Clear;
	}

	printf("[테스트 종료! 수고하셨습니다.]\n");
	printf("맞은 문제 : [%d]개 || 틀린 문제 : [%d]개\n", Right, Wrong);
	printf("(Enter를 누르면 메뉴로 넘어갑니다...)");

	ControlManager::GetInstance().Press_Enter();
}

void WorkbookManager::Study_Proverb()
{
	if(!Create_Workbook(Type::PROVERB)) return;
	ControlManager::GetInstance().Shuffle_Workbook(Workbook);

	printf("[불규칙동사 테스트 %d선!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter를 누르면 바로 진행합니다...)");

	printf("\n\n\n<주의 사항>\n");
	printf("★(입력은 모두 한 줄로 받으며, 띄어쓰기를 구분합니다.)\n");
	printf("★(사용자가 정의한 txt파일을 통해 정답을 판단합니다.)\n");
	printf("★(사용 중에 txt파일을 건드릴 경우, 오류가 날 수 있습니다.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = Workbook.begin(); iter != Workbook.end(); ++iter, ++Turn) {

		printf("[%d번 문제] \"%s\"의 원형, 과거형, 과거분사형을 서술하세요!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("정답 : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			printf("[테스트 중도 포기!]\n");
			system("cls");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[맞았습니다!] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);

			if (!WrongIverb.empty()) {
				auto iter2 = remove(WrongIverb.begin(), WrongIverb.end(), Problem(iter->question, iter->solution, iter->type));
				WrongIverb.resize(iter2 - WrongIverb.begin());
			}
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[틀렸습니다...] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);

			bool Trigger = false;

			if (!WrongIverb.empty())
				for (auto iter2 = WrongIverb.begin(); iter2 != WrongIverb.end(); ++iter2)
					if (Problem(iter->question, iter->solution, iter->type) == Problem(iter2->question, iter2->solution, iter2->type))
						Trigger = true;

			if (Trigger == false)
				WrongIverb.push_back(Problem(iter->question, iter->solution, Type::PROVERB));
		}

		Sleep(800);
		Clear;
	}

	printf("[테스트 종료! 수고하셨습니다.]\n");
	printf("맞은 문제 : [%d]개 || 틀린 문제 : [%d]개\n", Right, Wrong);
	printf("(Enter를 누르면 메뉴로 넘어갑니다...)");

	ControlManager::GetInstance().Press_Enter();
}


inline void WrongbookManager::Copy_Wrongbook()
{
	ControlManager::GetInstance().Reset_Workbook(Copy);

	if (!WrongWord.empty())
		Copy.insert(Copy.begin(), WrongWord.begin(), WrongWord.end());
	if (!WrongIverb.empty())
		Copy.insert(Copy.begin(), WrongIverb.begin(), WrongIverb.end());
	if (!WrongProverb.empty())
		Copy.insert(Copy.begin(), WrongProverb.begin(), WrongProverb.end());
}

inline void WrongbookManager::Copy_Wrongbook(vector<Problem> Reference)
{
	ControlManager::GetInstance().Reset_Workbook(Copy);
	Copy.insert(Copy.begin(), Reference.begin(), Reference.end());
}

void WrongbookManager::WrongNote_List()
{
	printf("[틀린 단어]\n");
	Turn = 1;

	if (!WrongWord.empty())
		for (auto iter : WrongWord) {
			printf("[%d]. %s : \n", Turn, iter.question.c_str());
			for (auto iter2 : iter.solution)
				printf("%s ", iter2.c_str());
			putchar('\n');
			++Turn;
		}
	else { printf("(오답노트가 깨끗합니다.)\n"); }

	printf("\n[틀린 불규칙동사]\n");
	Turn = 1;

	if (!WrongIverb.empty())
		for (auto iter : WrongIverb) {
			printf("[%d]. %s : \n", Turn, iter.question.c_str());
			for (auto iter2 : iter.solution)
				printf("%s ", iter2.c_str());
			putchar('\n');
			++Turn;
		}
	else { printf("(오답노트가 깨끗합니다.)\n"); }

	printf("\n[틀린 속담]\n");
	Turn = 1;

	if (!WrongProverb.empty())
		for (auto iter : WrongProverb) {
			printf("[%d]. %s : \n", Turn, iter.question.c_str());
			for (auto iter2 : iter.solution)
				printf("%s ", iter2.c_str());
			putchar('\n');
			++Turn;
		}
	else { printf("(오답노트가 깨끗합니다.)\n"); }

	printf("\n\n(엔터키를 누르면 이전 메뉴로 나갑니다.)");
	ControlManager::GetInstance().Press_Enter();
}

void WrongbookManager::Review_All()
{
	Copy_Wrongbook();
	ControlManager::GetInstance().Shuffle_Workbook(Copy);
}

void WrongbookManager::Preview_Word()
{
	Copy_Wrongbook(WrongWord);
	ControlManager::GetInstance().Shuffle_Workbook(Copy);


	printf("[단어 복습 %d선!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter를 누르면 바로 진행합니다...)");

	printf("\n\n\n<주의 사항>\n");
	printf("★(입력은 모두 한 줄로 받으며, 띄어쓰기를 구분합니다.)\n");
	printf("★(사용자가 정의한 txt파일을 통해 정답을 판단합니다.)\n");
	printf("★(사용 중에 txt파일을 건드릴 경우, 오류가 날 수 있습니다.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = WrongWord.begin(); iter != WrongWord.end(); ++iter, ++Turn) {

		printf("[%d번 문제] \"%s\"을(를) 해석하세요!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("정답 : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			system("cls");
			printf("[테스트 중도 포기!]\n");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[맞았습니다!] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[틀렸습니다...] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);
		}

		Sleep(800);
		Clear;
	}

	printf("[테스트 종료! 수고하셨습니다.]\n");
	printf("맞은 문제 : [%d]개 || 틀린 문제 : [%d]개\n", Right, Wrong);
	printf("(Enter를 누르면 메뉴로 넘어갑니다...)");

	ControlManager::GetInstance().Press_Enter();
}

void WrongbookManager::Preview_IVerb()
{
	Copy_Wrongbook(WrongIverb);
	ControlManager::GetInstance().Shuffle_Workbook(Copy);

	printf("[불규칙동사 테스트 %d선!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter를 누르면 바로 진행합니다...)");

	printf("\n\n\n<주의 사항>\n");
	printf("★(입력은 모두 한 줄로 받으며, 띄어쓰기를 구분합니다.)\n");
	printf("★(사용자가 정의한 txt파일을 통해 정답을 판단합니다.)\n");
	printf("★(사용 중에 txt파일을 건드릴 경우, 오류가 날 수 있습니다.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = WrongIverb.begin(); iter != WrongIverb.end(); ++iter, ++Turn) {

		printf("[%d번 문제] \"%s\"의 원형, 과거형, 과거분사형을 서술하세요!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("정답 : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			printf("[테스트 중도 포기!]\n");
			system("cls");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[맞았습니다!] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[틀렸습니다...] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);
		}

		Sleep(800);
		Clear;
	}

	printf("[복습 종료! 수고하셨습니다.]\n");
	printf("맞은 문제 : [%d]개 || 틀린 문제 : [%d]개\n", Right, Wrong);
	printf("(Enter를 누르면 메뉴로 넘어갑니다...)");

	ControlManager::GetInstance().Press_Enter();
}

void WrongbookManager::Preview_Proverb()
{
	Copy_Wrongbook(WrongProverb);
	ControlManager::GetInstance().Shuffle_Workbook(Copy);

	printf("[속담 복습 %d선!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter를 누르면 바로 진행합니다...)");

	printf("\n\n\n<주의 사항>\n");
	printf("★(입력은 모두 한 줄로 받으며, 띄어쓰기를 구분합니다.)\n");
	printf("★(사용자가 정의한 txt파일을 통해 정답을 판단합니다.)\n");
	printf("★(사용 중에 txt파일을 건드릴 경우, 오류가 날 수 있습니다.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = WrongProverb.begin(); iter != WrongProverb.end(); ++iter, ++Turn) {

		printf("[%d번 문제] \"%s\"의 원형, 과거형, 과거분사형을 서술하세요!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("정답 : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			printf("[테스트 중도 포기!]\n");
			system("cls");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[맞았습니다!] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[틀렸습니다...] 맞은 개수 : %d개 틀린 개수 : %d개", Right, Wrong);
		}

		Sleep(800);
		Clear;
	}

	printf("[복습 종료! 수고하셨습니다.]\n");
	printf("맞은 문제 : [%d]개 || 틀린 문제 : [%d]개\n", Right, Wrong);
	printf("(Enter를 누르면 메뉴로 넘어갑니다...)");

	ControlManager::GetInstance().Press_Enter();
}
