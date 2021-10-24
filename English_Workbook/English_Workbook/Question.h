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


	bool operator == (Problem obj) // 비교를 위한 오퍼레이터 오버로딩
	{
		if (this->question == obj.question &&
			this->solution == obj.solution)
			return true;

		return false;
	}

	bool operator != (Problem obj) // 비교를 위한 오퍼레이터 오버로딩
	{
		if (this->question != obj.question ||
			this->solution != obj.solution)
			return true;

		return false;
	}

};