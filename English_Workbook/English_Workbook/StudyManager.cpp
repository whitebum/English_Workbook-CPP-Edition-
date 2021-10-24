#include "Header.h"

void Launcher::MainMenu()
{
	while (Act != 3) {
		Clear;

		printf("[영어 워크북] %s\n", Version.c_str());

		printf("1. [공부하기]\n");
		printf("2. [복습하기]\n");
		printf("3. [종료하기]\n");
		printf("(올바른 숫자를 입력해주세요.) ===>>> ");

		Act = 0;
		scanf("%d", &Act);

		if (1 > Act || Act > 3) {
			printf("올바르지 않은 명령입니다...!");
			ControlManager::GetInstance().Press_Enter();
			continue;
		}

		switch (Act)
		{
		case 1:
			Clear;
			StudyMenu();
			break;
		case 2:
			Clear;
			PreviewMenu();
			break;
		case 3:
			Clear;
			printf("프로그램을 종료합니다...");
			return;
		default:
			break;
		}
	}
}

void Launcher::StudyMenu()
{
	while (Act != 3) {
		Clear;

		printf("[공부하기]\n");
		printf("(단어, 불규칙동사, 속담 테스트를 볼 수 있습니다.)\n");
		printf("(또한, [문제 대난투]를 통해 모든 문제들을 테스트할 수도 있습니다.)\n\n");

		printf("1. [단어 테스트]\n");
		printf("2. [불규칙동사 테스트]\n");
		printf("3. [속담 테스트]\n");
		printf("4. [문제 대난투]\n");
		printf("5. [뒤로 가기]\n");
		printf("(올바른 숫자를 입력해주세요.) ===>>> ");

		Act = 0;
		scanf("%d", &Act);

		if (1 > Act && Act > 5) {
			printf("올바르지 않은 명령입니다...!");
			ControlManager::GetInstance().Press_Enter();
			continue;
		}

		switch (Act)
		{
		case 1:
			Clear;
			WorkbookManager::GetInstance().Study_Word();
			break;
		case 2:
			Clear;
			WorkbookManager::GetInstance().Study_IVerb();
			break;
		case 3:
			Clear;
			WorkbookManager::GetInstance().Study_Proverb();
			break;
		case 4:
			Clear;
			WorkbookManager::GetInstance().Study_All();
			break;
		case 5:
		default:
			return;
		}
	}
}

void Launcher::PreviewMenu()
{
	while (Act != 3) {
		Clear;

		printf("[복습하기]\n");
		printf("([오답노트]를 통해, 자신이 틀린 문제들을 확인하거나, 재시험을 볼 수 있습니다.)\n");
		printf("(또한, [오답 대난투]를 통해 모든 오답들을 테스트할 수도 있습니다.)\n\n");

		printf("1. [오답노트 확인]\n");
		printf("2. [단어 복습]\n");
		printf("3. [불규칙동사 복습]\n");
		printf("4. [속담 복습]\n");
		printf("5. [오답 대난투]\n");
		printf("6. [뒤로 가기]\n");
		printf("(올바른 숫자를 입력해주세요.) ===>>> ");

		Act = 0;
		scanf("%d", &Act);

		if (1 > Act && Act > 5) {
			printf("올바르지 않은 명령입니다...!");
			ControlManager::GetInstance().Press_Enter();
			continue;
		}

		switch (Act)
		{
		case 1:
			if (WrongWord.empty() && WrongIverb.empty() && WrongProverb.empty()) {
				printf("(오답노트가 비워져 있습니다.)");
				ControlManager::GetInstance().Press_Enter();
			}
			else {
				Clear;
				WrongbookManager::GetInstance().WrongNote_List();
			}
			break;
		case 2:
			if (WrongWord.empty()) {
				printf("(오답노트가 비워져 있습니다.)");
				ControlManager::GetInstance().Press_Enter();
			}
			else {
				Clear;
				WrongbookManager::GetInstance().Preview_Word();
			}
			break;
		case 3:
			if (WrongIverb.empty()) {
				printf("(오답노트가 비워져 있습니다.)");
				ControlManager::GetInstance().Press_Enter();
			}
			else {
				Clear;
				WrongbookManager::GetInstance().Preview_IVerb();
			}
			break;
		case 4:
			if (WrongProverb.empty()) {
				printf("(오답노트가 비워져 있습니다.)");
				ControlManager::GetInstance().Press_Enter();
			}
			else {
				Clear;
				WrongbookManager::GetInstance().Preview_Proverb();
			}
			break;
		case 5:
			if (WrongWord.empty() && WrongIverb.empty() && WrongProverb.empty()) {
				printf("(오답노트가 비워져 있습니다.)");
				ControlManager::GetInstance().Press_Enter();
			}
			else {
				Clear;
				WrongbookManager::GetInstance().Review_All();
			}
			break;
		case 6:
		default:
			return;
		}
	}
}

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

		else {
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

		else {
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

		else {
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
			printf("[%d] %s : ", Turn, iter.question.c_str());

			if (iter.solution.size() == 1) { printf("[%s]\n", iter.solution[0].c_str()); }
			else { printf("[%s] ...\n", iter.solution[0].c_str()); }
			++Turn;
		} else { printf("(오답노트가 깨끗합니다.)\n"); }

	printf("\n[틀린 불규칙동사]\n");
	Turn = 1;

	if (!WrongIverb.empty())
		for (auto iter : WrongIverb) {
			printf("[%d] %s : ", Turn, iter.question.c_str());

			if (iter.solution.size() == 1) { printf("[%s]\n", iter.solution[0].c_str()); }
			else { printf("[%s] ...\n", iter.solution[0].c_str()); }
			++Turn;

			++Turn;
		} else { printf("(오답노트가 깨끗합니다.)\n"); }

	printf("\n[틀린 속담]\n");
	Turn = 1;

	if (!WrongProverb.empty())
		for (auto iter : WrongProverb) {
			printf("[%d] %s : ", Turn, iter.question.c_str());

			if (iter.solution.size() == 1) { printf("[%s]\n", iter.solution[0].c_str()); }
			else { printf("[%s] ...\n", iter.solution[0].c_str()); }
			++Turn;

			++Turn;
		} else { printf("(오답노트가 깨끗합니다.)\n"); }

	printf("\n\n(엔터키를 누르면 이전 메뉴로 나갑니다.)");
	ControlManager::GetInstance().Press_Enter();
}

void WrongbookManager::Review_All()
{
	Copy_Wrongbook();
	ControlManager::GetInstance().Shuffle_Workbook(Copy);

	printf("[오답 대난투 총 %d문제!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter를 누르면 바로 진행합니다...)");

	printf("\n\n\n<주의 사항>\n");
	printf("★(해당 모드에선 정답이어도 오답노트에서 지워지지 않습니다.)\n");
	printf("★(입력은 모두 한 줄로 받으며, 띄어쓰기를 구분합니다.)\n");
	printf("★(사용자가 정의한 txt파일을 통해 정답을 판단합니다.)\n");
	printf("★(사용 중에 txt파일을 건드릴 경우, 오류가 날 수 있습니다.)");
}

void WrongbookManager::Preview_Word()
{
	Copy_Wrongbook(WrongWord);
	ControlManager::GetInstance().Shuffle_Workbook(Copy);


	printf("[단어 복습 %d선!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter를 누르면 바로 진행합니다...)");

	printf("\n\n\n<주의 사항>\n");
	printf("★(해당 모드에선 정답이어도 오답노트에서 지워지지 않습니다.)\n");
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

		else {
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
	printf("★(해당 모드에선 정답이어도 오답노트에서 지워지지 않습니다.)\n");
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

		else {
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
	printf("★(해당 모드에선 정답이어도 오답노트에서 지워지지 않습니다.)\n");
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

		else {
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
