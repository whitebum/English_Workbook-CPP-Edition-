#pragma once

class ControlManager : public Singleton<ControlManager>
{
public:

	inline void Press_Enter() {
		while (_getch() != 13) {}
		Clear;
	}

	inline void Reset_Workbook(vector<Problem>& Vec) { 
		Vec.clear();
		vector<Problem>Swap(Vec);
	}

	inline void Shuffle_Workbook(vector<Problem>& Vec) {
		int Study_Type;

		printf("[문제 출제는 순번으로 하시겠습니까, 랜덤으로 하시겠습니까?]\n");
		printf("(1. 순번대로) (2. 랜덤으로)\n");
		scanf("%d", &Study_Type);

		if (Study_Type == 2) {
			std::random_device rd;
			std::default_random_engine rng(rd());
			std::shuffle(Vec.begin(), Vec.end(), rng);
		}

		std::cin.ignore();
		Clear;
	}

    void DoProgress(string label, int step, int total)
    {
        //progress width
        const int pwidth = 72;

        //minus label len
        int width = pwidth - label.length();
        int pos = (step * width) / total;

        int percent = (step * 100) / total;

        //set green text color, only on Windows
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("%s[", label.c_str());

        //fill progress bar with =
        for (int i = 0; i < pos; i++)  printf("%c", '=');

        //fill progress bar with spaces
        printf("% *c", width - pos + 1, ']');
        printf(" %3d%%\r", percent);

        //reset text color, only on Windows
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
    }

    void DoSome()
    {
        int total = 1000;
        int step = 0;

        while (step < total)
        {
            //do some action
            ::Sleep(50);

            step += 1;

            DoProgress( "파일 리드 : ", step, total);
        }

        printf("\n");

    }

	ControlManager() {}
	~ControlManager() {}

};