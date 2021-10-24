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
			if (WrongProverb.empty() || WrongIverb.empty() || WrongProverb.empty()) {
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
			if (WrongProverb.empty() || WrongIverb.empty() || WrongProverb.empty()) {
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

