#include <SFML/Graphics.hpp>
// 不解释，目前只需要包含图像部分就行了。
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Application");	// 对新建窗口的封装，第一个参数是一个VideoMode，表示窗口大小，第二个表示窗口标题
	sf::CircleShape shape;		// 目前的物体，一个圆，暂时把他当成精灵就行了。
	shape.setPosition(400, 300);
	shape.setRadius(40.0f);
	shape.setFillColor(sf::Color::Cyan);

	while (window.isOpen())
	{							// 不断执行这个循环
		sf::Event event;

		while (window.pollEvent(event))
		{						// sfml中的事件，每次读取窗口的事件。
			if (event.type == sf::Event::Closed)	// 关闭事件，也就是按了窗口上的叉叉
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{					// 按键事件
				if (event.key.code == sf::Keyboard::Escape)	// 如果按了esc，也是关闭的效果
					window.close();
			}					// end if
		}						// end while

		 window.clear();		// 每次清屏
		window.draw(shape);		// 东西还是要画的
		window.display();		// 画完之后还是要显示的
	}							// end while

	return 0;
 }

