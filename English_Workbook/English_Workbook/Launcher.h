#pragma once

class Launcher : public Singleton<Launcher>
{
private:

	string Version = "Ver 1.5";
	int Act = 0;

public:

	void MainMenu();
	void StudyMenu();
	void PreviewMenu();

	Launcher() {}
	~Launcher() {}

};