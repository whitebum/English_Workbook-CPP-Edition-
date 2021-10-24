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
		printf("���� �б⿡ �����߽��ϴ�!\n");
		printf("���� ���� ��� ===>> [%s]\n", filePath.c_str());
		printf("(���� ���� �޸����� ����ų� �Ű��� ���, ����� �� ��ο� �ٽ� �Ű��ֽʽÿ�.)");

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
			printf("���� �б⿡ �����߽��ϴ�!\n");
			printf("���� ���� ��� ===>> [English_Workbook/StudyFile/%s]\n", Tags[i].c_str());
			printf("���� ���� �޸����� ����ų� �Ű��� ���, ����� �� ��ο� �ٽ� �Ű��ֽʽÿ�.");

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

	printf("[���� �볭�� �� %d����!]\n", static_cast<int>(Workbook.size()));
	printf("(��� �������� ������ �����˴ϴ�. �����ϼ���!)\n");
	printf("(Enter�� ������ �ٷ� �����մϴ�...)\n");

	printf("\n\n\n<���� ����>\n");
	printf("��(�ش� ��忡�� Ʋ�� ������ ���� ��Ʈ�� ��ϵ��� �ʽ��ϴ�.)\n");
	printf("��(�Է��� ��� �� �ٷ� ������, ���⸦ �����մϴ�.)\n");
	printf("��(����ڰ� ������ txt������ ���� ������ �Ǵ��մϴ�.)\n");
	printf("��(��� �߿� txt������ �ǵ帱 ���, ������ �� �� �ֽ��ϴ�.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = Workbook.begin(); iter != Workbook.end(); ++iter, ++Turn) {

		switch (iter->type)
		{
		case Type::WORD:
			printf("<�ܾ�> [%d]����! \"%s\"��(��) �ؼ��ϼ���.", Turn + 1, iter->question.c_str());
			break;
		case Type::IVERB:
			printf("<�ұ�Ģ����> [%d�� ����] \"%s\"�� ����, ������, ���źл����� �����ϼ���!\n", Turn + 1, iter->question.c_str());
			break;
		case Type::PROVERB:
			printf("<�Ӵ�> [%d�� ����] \"%s\"�� �ǹ̸� �����ϼ���!\n", Turn + 1, iter->question.c_str());
			break;
		default:
			break;
		}

#ifdef _DEBUG

		printf("���� : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			system("cls");
			printf("[�׽�Ʈ �ߵ� ����!]\n");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[�¾ҽ��ϴ�!] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);

			if (!WrongWord.empty()) {
				auto iter2 = remove(WrongWord.begin(), WrongWord.end(), Problem(iter->question, iter->solution, iter->type));
				WrongWord.resize(iter2 - WrongWord.begin());
			}
		}

		else if(!isRightAnswer(iter->solution, Answer)){
			++Wrong;
			printf("[Ʋ�Ƚ��ϴ�...] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);

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

	printf("[�׽�Ʈ ����! �����ϼ̽��ϴ�.]\n");
	printf("���� ���� : [%d]�� || Ʋ�� ���� : [%d]��\n", Right, Wrong);
	printf("(Enter�� ������ �޴��� �Ѿ�ϴ�...)");

	ControlManager::GetInstance().Press_Enter();
}

void WorkbookManager::Study_Word()
{
	if (!Create_Workbook(Type::WORD)) return;
	ControlManager::GetInstance().Shuffle_Workbook(Workbook);

	printf("[�ܾ� �׽�Ʈ %d��!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter�� ������ �ٷ� �����մϴ�...)");

	printf("\n\n\n<���� ����>\n");
	printf("��(�Է��� ��� �� �ٷ� ������, ���⸦ �����մϴ�.)\n");
	printf("��(����ڰ� ������ txt������ ���� ������ �Ǵ��մϴ�.)\n");
	printf("��(��� �߿� txt������ �ǵ帱 ���, ������ �� �� �ֽ��ϴ�.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = Workbook.begin(); iter != Workbook.end(); ++iter, ++Turn) {

		printf("[%d�� ����] \"%s\"��(��) �ؼ��ϼ���!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("���� : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			system("cls");
			printf("[�׽�Ʈ �ߵ� ����!]\n");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[�¾ҽ��ϴ�!] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);

			if (!WrongWord.empty()) {
				auto iter2 = remove(WrongWord.begin(), WrongWord.end(), Problem(iter->question, iter->solution, iter->type));
				WrongWord.resize(iter2 - WrongWord.begin());
			}
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[Ʋ�Ƚ��ϴ�...] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);

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

	printf("[�׽�Ʈ ����! �����ϼ̽��ϴ�.]\n");
	printf("���� ���� : [%d]�� || Ʋ�� ���� : [%d]��\n", Right, Wrong);
	printf("(Enter�� ������ �޴��� �Ѿ�ϴ�...)");

	ControlManager::GetInstance().Press_Enter();
}

void WorkbookManager::Study_IVerb()
{
	if (!Create_Workbook(Type::IVERB)) return;
	ControlManager::GetInstance().Shuffle_Workbook(Workbook);

	printf("[�ұ�Ģ���� �׽�Ʈ %d��!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter�� ������ �ٷ� �����մϴ�...)");

	printf("\n\n\n<���� ����>\n");
	printf("��(�Է��� ��� �� �ٷ� ������, ���⸦ �����մϴ�.)\n");
	printf("��(����ڰ� ������ txt������ ���� ������ �Ǵ��մϴ�.)\n");
	printf("��(��� �߿� txt������ �ǵ帱 ���, ������ �� �� �ֽ��ϴ�.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = Workbook.begin(); iter != Workbook.end(); ++iter, ++Turn) {

		printf("[%d�� ����] \"%s\"�� ����, ������, ���źл����� �����ϼ���!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("���� : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			printf("[�׽�Ʈ �ߵ� ����!]\n");
			system("cls");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[�¾ҽ��ϴ�!] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);

			if (!WrongIverb.empty()) {
				auto iter2 = remove(WrongIverb.begin(), WrongIverb.end(), Problem(iter->question, iter->solution, iter->type));
				WrongIverb.resize(iter2 - WrongIverb.begin());
			}
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[Ʋ�Ƚ��ϴ�...] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);

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

	printf("[�׽�Ʈ ����! �����ϼ̽��ϴ�.]\n");
	printf("���� ���� : [%d]�� || Ʋ�� ���� : [%d]��\n", Right, Wrong);
	printf("(Enter�� ������ �޴��� �Ѿ�ϴ�...)");

	ControlManager::GetInstance().Press_Enter();
}

void WorkbookManager::Study_Proverb()
{
	if(!Create_Workbook(Type::PROVERB)) return;
	ControlManager::GetInstance().Shuffle_Workbook(Workbook);

	printf("[�ұ�Ģ���� �׽�Ʈ %d��!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter�� ������ �ٷ� �����մϴ�...)");

	printf("\n\n\n<���� ����>\n");
	printf("��(�Է��� ��� �� �ٷ� ������, ���⸦ �����մϴ�.)\n");
	printf("��(����ڰ� ������ txt������ ���� ������ �Ǵ��մϴ�.)\n");
	printf("��(��� �߿� txt������ �ǵ帱 ���, ������ �� �� �ֽ��ϴ�.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = Workbook.begin(); iter != Workbook.end(); ++iter, ++Turn) {

		printf("[%d�� ����] \"%s\"�� ����, ������, ���źл����� �����ϼ���!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("���� : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			printf("[�׽�Ʈ �ߵ� ����!]\n");
			system("cls");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[�¾ҽ��ϴ�!] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);

			if (!WrongIverb.empty()) {
				auto iter2 = remove(WrongIverb.begin(), WrongIverb.end(), Problem(iter->question, iter->solution, iter->type));
				WrongIverb.resize(iter2 - WrongIverb.begin());
			}
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[Ʋ�Ƚ��ϴ�...] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);

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

	printf("[�׽�Ʈ ����! �����ϼ̽��ϴ�.]\n");
	printf("���� ���� : [%d]�� || Ʋ�� ���� : [%d]��\n", Right, Wrong);
	printf("(Enter�� ������ �޴��� �Ѿ�ϴ�...)");

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
	printf("[Ʋ�� �ܾ�]\n");
	Turn = 1;

	if (!WrongWord.empty())
		for (auto iter : WrongWord) {
			printf("[%d]. %s : \n", Turn, iter.question.c_str());
			for (auto iter2 : iter.solution)
				printf("%s ", iter2.c_str());
			putchar('\n');
			++Turn;
		}
	else { printf("(�����Ʈ�� �����մϴ�.)\n"); }

	printf("\n[Ʋ�� �ұ�Ģ����]\n");
	Turn = 1;

	if (!WrongIverb.empty())
		for (auto iter : WrongIverb) {
			printf("[%d]. %s : \n", Turn, iter.question.c_str());
			for (auto iter2 : iter.solution)
				printf("%s ", iter2.c_str());
			putchar('\n');
			++Turn;
		}
	else { printf("(�����Ʈ�� �����մϴ�.)\n"); }

	printf("\n[Ʋ�� �Ӵ�]\n");
	Turn = 1;

	if (!WrongProverb.empty())
		for (auto iter : WrongProverb) {
			printf("[%d]. %s : \n", Turn, iter.question.c_str());
			for (auto iter2 : iter.solution)
				printf("%s ", iter2.c_str());
			putchar('\n');
			++Turn;
		}
	else { printf("(�����Ʈ�� �����մϴ�.)\n"); }

	printf("\n\n(����Ű�� ������ ���� �޴��� �����ϴ�.)");
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


	printf("[�ܾ� ���� %d��!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter�� ������ �ٷ� �����մϴ�...)");

	printf("\n\n\n<���� ����>\n");
	printf("��(�Է��� ��� �� �ٷ� ������, ���⸦ �����մϴ�.)\n");
	printf("��(����ڰ� ������ txt������ ���� ������ �Ǵ��մϴ�.)\n");
	printf("��(��� �߿� txt������ �ǵ帱 ���, ������ �� �� �ֽ��ϴ�.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = WrongWord.begin(); iter != WrongWord.end(); ++iter, ++Turn) {

		printf("[%d�� ����] \"%s\"��(��) �ؼ��ϼ���!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("���� : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			system("cls");
			printf("[�׽�Ʈ �ߵ� ����!]\n");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[�¾ҽ��ϴ�!] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[Ʋ�Ƚ��ϴ�...] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);
		}

		Sleep(800);
		Clear;
	}

	printf("[�׽�Ʈ ����! �����ϼ̽��ϴ�.]\n");
	printf("���� ���� : [%d]�� || Ʋ�� ���� : [%d]��\n", Right, Wrong);
	printf("(Enter�� ������ �޴��� �Ѿ�ϴ�...)");

	ControlManager::GetInstance().Press_Enter();
}

void WrongbookManager::Preview_IVerb()
{
	Copy_Wrongbook(WrongIverb);
	ControlManager::GetInstance().Shuffle_Workbook(Copy);

	printf("[�ұ�Ģ���� �׽�Ʈ %d��!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter�� ������ �ٷ� �����մϴ�...)");

	printf("\n\n\n<���� ����>\n");
	printf("��(�Է��� ��� �� �ٷ� ������, ���⸦ �����մϴ�.)\n");
	printf("��(����ڰ� ������ txt������ ���� ������ �Ǵ��մϴ�.)\n");
	printf("��(��� �߿� txt������ �ǵ帱 ���, ������ �� �� �ֽ��ϴ�.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = WrongIverb.begin(); iter != WrongIverb.end(); ++iter, ++Turn) {

		printf("[%d�� ����] \"%s\"�� ����, ������, ���źл����� �����ϼ���!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("���� : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());
		putchar('\n');

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			printf("[�׽�Ʈ �ߵ� ����!]\n");
			system("cls");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[�¾ҽ��ϴ�!] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[Ʋ�Ƚ��ϴ�...] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);
		}

		Sleep(800);
		Clear;
	}

	printf("[���� ����! �����ϼ̽��ϴ�.]\n");
	printf("���� ���� : [%d]�� || Ʋ�� ���� : [%d]��\n", Right, Wrong);
	printf("(Enter�� ������ �޴��� �Ѿ�ϴ�...)");

	ControlManager::GetInstance().Press_Enter();
}

void WrongbookManager::Preview_Proverb()
{
	Copy_Wrongbook(WrongProverb);
	ControlManager::GetInstance().Shuffle_Workbook(Copy);

	printf("[�Ӵ� ���� %d��!]\n", static_cast<int>(Workbook.size()));
	printf("(Enter�� ������ �ٷ� �����մϴ�...)");

	printf("\n\n\n<���� ����>\n");
	printf("��(�Է��� ��� �� �ٷ� ������, ���⸦ �����մϴ�.)\n");
	printf("��(����ڰ� ������ txt������ ���� ������ �Ǵ��մϴ�.)\n");
	printf("��(��� �߿� txt������ �ǵ帱 ���, ������ �� �� �ֽ��ϴ�.)");

	ControlManager::GetInstance().Press_Enter();

	Right = 0, Wrong = 0, Turn = 0;
	Answer = "This Is Default Answer";

	for (auto iter = WrongProverb.begin(); iter != WrongProverb.end(); ++iter, ++Turn) {

		printf("[%d�� ����] \"%s\"�� ����, ������, ���źл����� �����ϼ���!\n", Turn + 1, iter->question.c_str());

#ifdef _DEBUG

		printf("���� : ");
		for (auto it : iter->solution)
			printf("[%s] ", it.c_str());

#endif // _DEBUG

		std::getline(std::cin, Answer);

		if (Answer == "Escape This Test") {
			printf("[�׽�Ʈ �ߵ� ����!]\n");
			system("cls");
			break;
		}

		if (isRightAnswer(iter->solution, Answer)) {
			++Right;
			printf("[�¾ҽ��ϴ�!] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);
		}

		else if (!isRightAnswer(iter->solution, Answer)) {
			++Wrong;
			printf("[Ʋ�Ƚ��ϴ�...] ���� ���� : %d�� Ʋ�� ���� : %d��", Right, Wrong);
		}

		Sleep(800);
		Clear;
	}

	printf("[���� ����! �����ϼ̽��ϴ�.]\n");
	printf("���� ���� : [%d]�� || Ʋ�� ���� : [%d]��\n", Right, Wrong);
	printf("(Enter�� ������ �޴��� �Ѿ�ϴ�...)");

	ControlManager::GetInstance().Press_Enter();
}
