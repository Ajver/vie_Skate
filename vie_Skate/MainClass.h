#include <vie/Engine.h>

class MainClass : public vie::Engine
{
public:
	MainClass();
	~MainClass();

	void onCreate();
	void update(float et);
	void render(vie::Graphics* g);

};