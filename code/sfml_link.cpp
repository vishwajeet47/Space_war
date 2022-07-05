
#include <iostream>
#include "GameClass.h"
#include "menu.h"
#include "Score.h"
#include <fstream>
#include <map> 
#include "Header.h"

//using namespace sf;

Node* initTree( std::fstream& file);

int main()
{
    
    //menu
    int loops = 0;
    
    std::vector<GameClass> plays;
    sf::RenderWindow *MainWindow , *temp;
    sf::VideoMode MainVideoMode;
    MainVideoMode.height = 600;
    MainVideoMode.width = 400;
    bool wait = true;
    std::map <int , std::string > score_map;
    
    //leaderBoard text object which stores string 
    //of scores with names in a sorted manner

    sf::Text leaderText;
    sf::Font font;
    font.loadFromFile("Fonts/Minecraft.ttf");
    leaderText.setFont(font);
    leaderText.setFillColor(sf::Color::White);
    leaderText.setString("Leaderboard");
    leaderText.setPosition(100,200);
    leaderText.setCharacterSize(14);


    // main Window
    //temp = new sf::RenderWindow(sf::VideoMode(400, 600), "temp", sf::Style::Titlebar | sf::Style::Close);
    MainWindow = new sf::RenderWindow(sf::VideoMode(400, 600), "MAin window", sf::Style::Titlebar | sf::Style::Close);
    MainWindow->setFramerateLimit(144);
    
    // score object to store name and points
    Score playerName(MainWindow);
    playerName.updateScore();
    Menu menu(MainWindow);
    
    // initiallising avl tree root node
    Node* root = NULL;

    // fstream object
    std::fstream leaderBoard;
    leaderBoard.open("Text_File/gameleader.txt", std::ios::app | std::ios::out | std::ios::in);
    if (leaderBoard.is_open()) {
        std::cout << "File opened\n";
    }
    else {
        std::cout << "Failed to open text file\n";
    }
    //initMap(score_map, leaderBoard);
    root = initTree(leaderBoard);

    sf::Event MainEvent;
    std::string score_string;


    while (menu.GetPressedItem() != 2) {
        //menu
        score_string = "";
        TreeToText(root , score_string);
        leaderText.setString(score_string);
        while (!menu.ifChoosen()) {
            MainWindow->clear();
            menu.Move();
            MainWindow->display();

            //loop will conitnue until an option is choosen i.e. is pressed
            if (menu.GetPressedItem() == 2 && menu.ifChoosen()) {
                cout << "Thanks for playing this game !\n\nDeveloped by Vishwajeet\n";
                return 0;
            }
            if(menu.GetPressedItem() == 1 && menu.ifChoosen()) {
                std::cout << "in leaderBpoard\n";
                //MainWindow->pollEvent(MainEvent);
                bool goback = false;

                    while(!goback)
                    {   
                        MainWindow->clear();
                        MainWindow->draw(leaderText);
                        MainWindow->display();
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                            goback = true;
                    }
                menu.setChoosen(false);
            }
        }

        menu.setChoosen(false);
        
        GameClass game(MainWindow);

        //int GameObject_index = 0;
        {
            std::srand(static_cast <unsigned>(time(NULL)));
            //game loop
            while (game.running() && !game.getgameOver())
            {
                //game polling
                //Update
                friendTochangeBullet(game);
                game.update();
                //render
                game.render();
                //draw your game
                loops++;
            }
        }
        playerName.setScore(game.getPonts());
        //std::cout <<playerScore.getName()<<" "<<game.getPonts()<<"\n";
        
        leaderBoard.open("Text_File/gameleader.txt", std::ios::app | std::ios::out | std::ios::in);
        leaderBoard.seekg(0, std::ios::beg);
        leaderBoard << game.getPonts() << " " << playerName.getName() ;
        root = insertNode(root, game.getPonts(), playerName.getName());
        //score_map[game.getPonts()] = playerName.getName();
    }
    
    delete MainWindow;
    leaderBoard.close();
    
    //end of application

    return 0;
}

// functions reads from file and insert nodes in the tree
Node* initTree( std::fstream& file) {
    Node* t = NULL;
    int i = 1;
    std::string temp;
    int temp1 = 0;
    file.seekg(0, std::ios::beg);
    while (file)
    {
        if (file >> temp) {
            //std::cout << temp << " " << std::endl;
            if (i % 2 != 0) {
                std::stringstream geek(temp);
                geek >> temp1;
                std::cout << "score = " << temp1 << std::endl;
            }
            else {
                std::cout << "Player name = " << temp << std::endl;
                t = insertNode(t, temp1, temp);
            }
            i++;
        }
    }
    std::cout << "Tree is  \n";
    printTree(t);
    file.close();
    return t;
}