#include "Header.h"

void Launcher::MainMenu()
{
	while (Act != 3) {
		Clear;

		printf("[���� ��ũ��] %s\n", Version.c_str());

		printf("1. [�����ϱ�]\n");
		printf("2. [�����ϱ�]\n");
		printf("3. [�����ϱ�]\n");
		printf("(�ùٸ� ���ڸ� �Է����ּ���.) ===>>> ");

		Act = 0;
		scanf("%d", &Act);

		if (1 > Act || Act > 3) {
			printf("�ùٸ��� ���� ����Դϴ�...!");
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
			printf("���α׷��� �����մϴ�...");
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

		printf("[�����ϱ�]\n");
		printf("(�ܾ�, �ұ�Ģ����, �Ӵ� �׽�Ʈ�� �� �� �ֽ��ϴ�.)\n");
		printf("(����, [���� �볭��]�� ���� ��� �������� �׽�Ʈ�� ���� �ֽ��ϴ�.)\n\n");

		printf("1. [�ܾ� �׽�Ʈ]\n");
		printf("2. [�ұ�Ģ���� �׽�Ʈ]\n");
		printf("3. [�Ӵ� �׽�Ʈ]\n");
		printf("4. [���� �볭��]\n");
		printf("5. [�ڷ� ����]\n");
		printf("(�ùٸ� ���ڸ� �Է����ּ���.) ===>>> ");

		Act = 0;
		scanf("%d", &Act);

		if (1 > Act && Act > 5) {
			printf("�ùٸ��� ���� ����Դϴ�...!");
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

		printf("[�����ϱ�]\n");
		printf("([�����Ʈ]�� ����, �ڽ��� Ʋ�� �������� Ȯ���ϰų�, ������� �� �� �ֽ��ϴ�.)\n");
		printf("(����, [���� �볭��]�� ���� ��� ������� �׽�Ʈ�� ���� �ֽ��ϴ�.)\n\n");

		printf("1. [�����Ʈ Ȯ��]\n");
		printf("2. [�ܾ� ����]\n");
		printf("3. [�ұ�Ģ���� ����]\n");
		printf("4. [�Ӵ� ����]\n");
		printf("5. [���� �볭��]\n");
		printf("6. [�ڷ� ����]\n");
		printf("(�ùٸ� ���ڸ� �Է����ּ���.) ===>>> ");

		Act = 0;
		scanf("%d", &Act);

		if (1 > Act && Act > 5) {
			printf("�ùٸ��� ���� ����Դϴ�...!");
			ControlManager::GetInstance().Press_Enter();
			continue;
		}

		switch (Act)
		{
		case 1:
			if (WrongProverb.empty() || WrongIverb.empty() || WrongProverb.empty()) {
				printf("(�����Ʈ�� ����� �ֽ��ϴ�.)");
				ControlManager::GetInstance().Press_Enter();
			}
			else {
				Clear;
				WrongbookManager::GetInstance().WrongNote_List();
			}
			break;
		case 2:
			if (WrongWord.empty()) {
				printf("(�����Ʈ�� ����� �ֽ��ϴ�.)");
				ControlManager::GetInstance().Press_Enter();
			}
			else {
				Clear;
				WrongbookManager::GetInstance().Preview_Word();
			}
			break;
		case 3:
			if (WrongIverb.empty()) {
				printf("(�����Ʈ�� ����� �ֽ��ϴ�.)");
				ControlManager::GetInstance().Press_Enter();
			}
			else {
				Clear;
				WrongbookManager::GetInstance().Preview_IVerb();
			}
			break;
		case 4:
			if (WrongProverb.empty()) {
				printf("(�����Ʈ�� ����� �ֽ��ϴ�.)");
				ControlManager::GetInstance().Press_Enter();
			}
			else {
				Clear;
				WrongbookManager::GetInstance().Preview_Proverb();
			}
			break;
		case 5:
			if (WrongProverb.empty() || WrongIverb.empty() || WrongProverb.empty()) {
				printf("(�����Ʈ�� ����� �ֽ��ϴ�.)");
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

