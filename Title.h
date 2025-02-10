#pragma once
#include "Scene.h"
#include "Struct.h"

class Title : public Scene {
private:
	Select select;
public:

	Title();
	~Title();

	void Update(const char* keys,const char *preKeys) override;
	void Draw() override;

};

