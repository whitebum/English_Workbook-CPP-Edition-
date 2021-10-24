#pragma once

enum class Type
{
	DEFAULT = 0,
	WORD = 1,
	IVERB = 2,
	PROVERB = 3,
};

class Problem
{
public:

	string question;
	vector<string> solution;
	Type type = Type::DEFAULT;

	Problem() {};
	Problem(string question, vector<string> solution, Type type) {
		this->question = question;
		this->solution = solution;
		this->type = type;
	};

	~Problem() {};


	bool operator == (Problem obj) // �񱳸� ���� ���۷����� �����ε�
	{
		if (this->question == obj.question &&
			this->solution == obj.solution)
			return true;

		return false;
	}

	bool operator != (Problem obj) // �񱳸� ���� ���۷����� �����ε�
	{
		if (this->question != obj.question ||
			this->solution != obj.solution)
			return true;

		return false;
	}

};