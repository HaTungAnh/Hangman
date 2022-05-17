#pragma once
#include "TexOb.h"
#include <vector>

class MultiTexOb : public TexOb
{
private:
	std::vector<Texture*> list;
	int _i;
	int length = 0;
public:
	void addTex(Texture* tex) {
		list.push_back(tex);
		length++;
	}

	void setCurTexture(int i = 0) {
		_i = i;
		texture = list[_i];
	}

	void nextTex() {
		_i++;
		_i = _i % length;
		texture = list[_i];
	}
};

