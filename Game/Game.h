//Scenes
class TestScene;

class Game
{
public:
	//Ctor
	Game();
	//Dtor
	~Game();
	//Public member functions
	void Run();
private:
	//Private datamembers
	TestScene* m_TestScene;
	//Private functions
	void Initialize();
};
