#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>

struct Rectangle
{
	int hight = 0;
	int width = 3;

	int x_location = 0;
	int y_location = 0;

	sf::Color colour = sf::Color(177, 237, 232);
};

void FillVector(Rectangle rec, std::vector<Rectangle>& recHolder, sf::Image Image)
{
	int xOffset = 0;
	while (xOffset < Image.getSize().x)
	{
		rec.hight = rand() % Image.getSize().y - 50;
		if (rec.hight < 5)
		{
			rec.hight = 5;
		}

		rec.x_location = xOffset;
		rec.y_location = Image.getSize().y - rec.hight;

		recHolder.push_back(rec);

		xOffset += 5;
	}
}
void PiantVector(sf::Image& image, std::vector<Rectangle> recHolder)
{

	for (int i = 0; i < recHolder.size(); i++)
	{
		for (int x = 0; x < recHolder[i].width; x++)
		{
			for (int y = 0; y < recHolder[i].hight; y++)
			{
				image.setPixel(recHolder[i].x_location + x, recHolder[i].y_location + y, recHolder[i].colour);
			}
		}
	}

}
void BuubleSort(std::vector<Rectangle>& recHolder, sf::Image& image, sf::RenderWindow& window, sf::Texture texture, sf::Sprite sprite)
{
	Rectangle tempRec;
	int tempXlocaion;

	for (int i = 0; i < recHolder.size(); i++)
	{
		for (int j = 0; j < recHolder.size() - 1; j++)
		{
			if (recHolder[j].hight > recHolder[j + 1].hight)
			{
				window.clear();
				//Moave bigge
				for (int x = 0; x < recHolder[j].width; x++)
				{
					for (int y = 0; y < recHolder[j].hight; y++)
					{
						image.setPixel(recHolder[j + 1].x_location + x, recHolder[j].y_location + y, recHolder[j].colour);
					}
				}
				//Delete the Big
				for (int x = 0; x < recHolder[j].width; x++)
				{
					for (int y = 0; y < recHolder[j].hight; y++)
					{
						image.setPixel(recHolder[j].x_location + x, recHolder[j].y_location + y, sf::Color(255, 255, 255));
					}
				}
				//Redraw Small 
				for (int x = 0; x < recHolder[j + 1].width; x++)
				{
					for (int y = 0; y < recHolder[j + 1].hight; y++)
					{
						image.setPixel(recHolder[j].x_location + x, recHolder[j + 1].y_location + y, recHolder[j].colour);
					}
				}


				tempXlocaion = recHolder[j].x_location;
				recHolder[j].x_location = recHolder[j + 1].x_location;
				recHolder[j + 1].x_location = tempXlocaion;


				tempRec = recHolder[j];
				recHolder[j] = recHolder[j + 1];
				recHolder[j + 1] = tempRec;
				texture.loadFromImage(image);
				sprite.setTexture(texture);

				window.draw(sprite);
				window.display();

			}
		}
	}
}

int main()
{

	srand(time(NULL));

	int width = 1000;
	int hight = 800;
	bool spaceIspressed = false;

	sf::RenderWindow window(sf::VideoMode(width, hight), "Bubble Srot");
	sf::Event ev;

	sf::Image image;
	image.create(width, hight);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < hight; j++)
		{

			image.setPixel(i, j, sf::Color(255, 255, 255));
		}
	}

	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprtie;
	sprtie.setTexture(texture);

	Rectangle rectanlge;
	std::vector<Rectangle> rectanlgeVector;

	FillVector(rectanlge, rectanlgeVector, image);
	PiantVector(image, rectanlgeVector);

	texture.loadFromImage(image);
	sprtie.setTexture(texture);

	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
			if (ev.type == sf::Event::KeyReleased)
			{
				if (ev.key.code == sf::Keyboard::Space)
				{
					spaceIspressed = true;
				}
			}
		}

		texture.loadFromImage(image);
		sprtie.setTexture(texture);

		window.clear();

		if (spaceIspressed)
		{
			BuubleSort(rectanlgeVector, image, window, texture, sprtie);
			spaceIspressed = false;
		}

		window.draw(sprtie);

		window.display();
	}

	return 0;
}