#include <SFML/Graphics.hpp>
#include "point.h"
#include "splitandmerge.h"
#include <iostream>
#include <vector>
#include <fstream>

std::vector<Point> readCSV(const std::string& filename)
{
    std::vector<Point> points;
    std::string line;
    std::ifstream myfile(filename);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            int delim_index = line.find_first_of(';');
            float x = atof(line.substr(0, delim_index).c_str());
            float y = atof(line.substr(delim_index + 1).c_str());
            points.push_back(Point(x, y));
        }
        myfile.close();
    }
    return points;
}

int main()
{
    const int gameWidth = 550;
    const int gameHeight = 550;
    const int dotSize = 1;
    const int threshold = 20;
    const float collinearity = .5;
    const float gapThreshold = 20;

    std::vector<Point> points = readCSV("data.csv");

    std::vector<sf::CircleShape> drawPoints;
    for (std::size_t i = 0; i < points.size(); i++)
    {
        sf::CircleShape circle(dotSize);
        circle.setPosition(points.at(i).x - dotSize, points.at(i).y - dotSize);
        circle.setFillColor(sf::Color::Black);
        drawPoints.push_back(circle);
    }

    bool drawLines = false;
    std::vector<sf::VertexArray> segments;

    // Create the window of the application
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Split and Merge",
                            sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }

            // Space key pressed
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space) && !drawLines)
            {
                drawLines = true;

                std::vector<std::vector<Point> > linestrips;
                linestrips = SplitAndMergeGap(points, threshold, gapThreshold, collinearity);

                for (std::size_t i = 0; i < linestrips.size(); i++)
                {
                    segments.push_back(sf::VertexArray(sf::LinesStrip, linestrips[i].size()));
                    for (std::size_t j = 0; j < linestrips[i].size(); j++)
                    {
                        segments.at(i)[j] = sf::Vector2f(linestrips[i][j].x, linestrips[i][j].y);
                        segments.at(i)[j].color = sf::Color::Red;
                    }
                }
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        for (std::size_t i = 0; i < drawPoints.size(); i++)
        {
            window.draw(drawPoints.at(i));
        }

        if (drawLines)
        {
            for (int i = 0; i < segments.size(); i++)
            {
                window.draw(segments.at(i));
            }
        }

        // Display things on screen
        window.display();
    }

    return EXIT_SUCCESS;
}
