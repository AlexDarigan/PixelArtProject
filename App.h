#pragma once
#include "SFML/Graphics.hpp"



class App {

	static App instance;
	sf::Sprite mouseCursor;
	sf::Texture mouseCursorTexture;
	sf::RectangleShape Background;
	sf::RenderWindow Window{ sf::VideoMode(800, 600), "Project" };
	GameObject root;
	

	App() {
		Background.setFillColor(sf::Color(211, 211, 211));
		Background.setSize(sf::Vector2f(800, 600));
		Window.setMouseCursorVisible(false);
		setCursor("Cursor.png");
	}

public:

	static App* getInstance();
	bool isOpen() { return Window.isOpen(); }
	void close() { Window.close(); }
	GameObject* getRoot() { return &root; }
	bool poll(sf::Event& event) { return Window.pollEvent(event); }
	void process(sf::Event& event) { 
		root.process(event); 
		mouseCursor.setPosition(Position(getMousePosition()) - Position(32, 32));
	}

	void redraw() {
		Window.clear();
		Window.draw(Background);
		Window.draw(root);
		Window.draw(mouseCursor);
		Window.display();
	}

	void setCursor(const std::string& texture_path) {
		mouseCursorTexture.loadFromFile(texture_path);
		mouseCursor.setTexture(mouseCursorTexture);
		mouseCursor.setScale(sf::Vector2f(0.125, 0.125));
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