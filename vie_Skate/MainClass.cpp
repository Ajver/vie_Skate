#include "MainClass.h"

MainClass::MainClass()
{
	runEngine("Skate", 1280, 728);
}

MainClass::~MainClass() {}

void MainClass::onCreate() {}

void MainClass::update(float et) {}

void MainClass::render(vie::Graphics* g)
{
	g->setBackgroundColor(vie::COLOR::BLUE);
}