#pragma once
class App {

	static App instance;
	sf::RectangleShape Background;
	sf::RenderWindow Window{ sf::VideoMode(800, 600), "Project" };
	GameObject root;

	App() {
		Background.setFillColor(sf::Color(211, 211, 211));
		Background.setSize(sf::Vector2f(800, 600));
	}

public:

	static App* getInstance();
	bool isOpen() { return Window.isOpen(); }
	GameObject* getRoot() { return &root; }
	bool poll(sf::Event& event) { return Window.pollEvent(event); }
	void process(sf::Event& event) {
		if (event.type == sf::Event::Closed) {
			Window.close();
		}
		root.process(event);
	}

	void redraw() {
		Window.clear();
		Window.draw(Background);
		Window.draw(root);
		Window.display();
	}

	static sf::Vector2i getMousePosition();

};

App App::instance;
App* App::getInstance() {
	return &instance;
}
sf::Vector2i App::getMousePosition() {
	return sf::Mouse::getPosition(instance.Window);
}