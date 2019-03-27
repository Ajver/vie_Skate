#include "MainClass.h"

#include "Player.h"

#include <vie/ObjectsManager.h>
#include <vie/Input.h>

MainClass::MainClass() {
	runEngine("Skate", 1280, 728);
}

MainClass::~MainClass() {
	delete cameraControll;
	delete map;
}

void MainClass::onCreate() {
	createWorld(glm::vec2(0, 10.0f));

	Player* player = new Player(objectsManager, b_world);

	objectsManager->appendObject(player);
	objectsManager->appendKeyListener(player);

	mainCamera->setScale(120);
	cameraControll = new CameraControll(player, mainCamera);

	map = new Map(b_world, objectsManager);
}

void MainClass::update(float et) {
	objectsManager->update(et);
	//cameraControll->update(et);

	if (vie::Input::isKeyPressed(SDLK_ESCAPE)) {
		destroyEngine();
	}
}

void MainClass::render(vie::Graphics* g) {
	g->setBackgroundColor(vie::COLOR::DARK_GRAY);

	map->render(g);

	objectsManager->render(g);
}

void MainClass::onFatalError(const std::string& errMsg) {
	system("pause");
}

void MainClass::onLog(const std::string& errMsg) {

}
