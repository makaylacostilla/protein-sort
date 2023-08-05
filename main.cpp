#include <iostream>
//#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Parser.h"
#include "Sorts.h"

using namespace  std;



int main() {
    //test
    //int arr[] = {12, 11, 13, 5, 6, 7};
    //int size = sizeof(arr)/sizeof(arr[0]);

    //Set up protein data objects
    std::vector<std::string> proteinIdVec;
    std::unordered_map<std::string, Protein> proteinsMap;
    Parser ToUse;
    ToUse.ParseFile("../uniprotkb.fasta", proteinsMap, proteinIdVec);
    int idVectorIndex = 0;

    sf::RenderWindow window(sf::VideoMode(1000, 750), "Protein Sort", sf::Style::Close);
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::RectangleShape inputBox(sf::Vector2f(952, 57));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(1);
    inputBox.setPosition(24, 84);
    //sf::FloatRect iB(24, 84, 952, 57);

    sf::Text output("Type name of protein here", font, 18);
    output.setFillColor(sf::Color::Black);
    output.setPosition(34, 103);
    string input;


    sf::RectangleShape resultBox(sf::Vector2f(952.f, 134.f));
    resultBox.setFillColor(sf::Color(191, 230, 245, 255));
    resultBox.setPosition(26, 175);

    sf::Text text(" ", font, 17);
    text.setFillColor(sf::Color(58, 58, 58, 255));
    text.setPosition(24, 84);

    sf::Text proteinName("[Protein Name]", font, 24);
    proteinName.setFillColor(sf::Color(58, 58, 58, 255));
    proteinName.setPosition(34, 216);

    sf::Text proteinSequence("[Protein Sequence]", font, 16);
    proteinSequence.setFillColor(sf::Color(58, 58, 58, 255));
    proteinSequence.setPosition(34, 261);


    sf::RectangleShape listBox(sf::Vector2f(952, 234));
    listBox.setFillColor(sf::Color(191, 230, 245, 255));
    listBox.setPosition(24, 485);


    sf::Text verifiedText("Include Unverified Proteins", font, 12);
    verifiedText.setFillColor(sf::Color(35, 35, 35, 255));
    verifiedText.setPosition(97, 43);


    sf::Text s("Sort By:", font, 18);
    s.setFillColor(sf::Color(58, 58, 58, 255));
    s.setPosition(24, 393);

    sf::RectangleShape ascending(sf::Vector2f(139.f, 40.f));
    ascending.setOutlineColor(sf::Color::Black);
    ascending.setFillColor(sf::Color(68, 119, 207));
    ascending.setOutlineThickness(1);
    ascending.setPosition(605, 387);
    sf::FloatRect a(605, 387, 139, 40);
    sf::Text ascText("Ascending", font, 13);
    ascText.setFillColor(sf::Color::Black);
    ascText.setPosition(640, 399);

    sf::RectangleShape descending(sf::Vector2f(139.f, 40.f));
    descending.setOutlineColor(sf::Color::Black);
    descending.setOutlineThickness(1);
    descending.setPosition(788, 387);
    sf::FloatRect d(788, 387, 139, 40);
    sf::Text desText("Descending", font, 13);
    desText.setFillColor(sf::Color::Black);
    desText.setPosition(820, 399);

    //regarding these two, the two sorts have to be used somewhere, so here unless not
    sf::RectangleShape merge(sf::Vector2f(139, 40));
    merge.setOutlineColor(sf::Color::Black);
    merge.setFillColor(sf::Color(68, 119, 207));
    merge.setOutlineThickness(1);
    merge.setPosition(132, 387);
    sf::FloatRect m(132, 387, 139, 40);
    sf::Text mergeText("Merge Sort", font, 13);
    mergeText.setFillColor(sf::Color::Black);
    mergeText.setPosition(164, 399);

    sf::RectangleShape quick(sf::Vector2f(139, 40));
    quick.setOutlineColor(sf::Color::Black);
    quick.setOutlineThickness(1);
    quick.setPosition(319, 387);
    sf::FloatRect q(319, 387, 139, 40);
    sf::Text quickText("Quick Sort", font, 13);
    quickText.setFillColor(sf::Color::Black);
    quickText.setPosition(351, 399);

    //will be used to decide how to sort
    int choice1 = 1;
    int choice2 = 1;

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered){

                input.push_back(event.text.unicode);
                output.setString(input + "|");
                output.setPosition(34, 103);

                //backspace does not work :(
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && input.length() != 0){
                    input.pop_back();
                    output.setString(input + "|");
                    output.setPosition(34, 103);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && input.length() != 0){
                    //search for protein name
                    try {
                        current = proteinsMap[input];
                        //change proteinName to name
                        proteinName.setString(current._id);
                        //change proteinSequence to sequence
                        proteinSequence.setString(current._sequence);
                    }
                    catch(std::out_of_range) {
                        std::cout << "Protein does not exist in dataset" << endl;
                        proteinName.setString("Not found");
                        proteinSequence.setString("The protein Id was not found in this dataset. Please try again.");
                    }
                }
            }

            //switch between sort options
            if (event.type == sf::Event::MouseButtonPressed){
                if (m.contains(event.mouseButton.x, event.mouseButton.y)){
                    merge.setFillColor(sf::Color(68, 119, 207));
                    quick.setFillColor(sf::Color::White);
                    choice1 = 1;
                }
                if (q.contains(event.mouseButton.x, event.mouseButton.y)){
                    quick.setFillColor(sf::Color(68, 119, 207));
                    merge.setFillColor(sf::Color::White);
                    choice1 = 2;
                }
                if (a.contains(event.mouseButton.x, event.mouseButton.y)){
                    ascending.setFillColor(sf::Color(68, 119, 207));
                    descending.setFillColor(sf::Color::White);
                    choice2 = 1;
                }
                if (d.contains(event.mouseButton.x, event.mouseButton.y)){
                    descending.setFillColor(sf::Color(68, 119, 207));
                    ascending.setFillColor(sf::Color::White);
                    choice2 = 2;
                }
            }
        }
        if (choice1 == 1 && choice2 == 1){
            //do merge ascending
            mergeSortAscending(proteinIdVec, 0, proteinIdVec.size() - 1);
        }
        if (choice1 == 1 && choice2 == 2 ){
            mergeSortDescending(proteinIdVec, 0, proteinIdVec.size() - 1);
        }
        if (choice1 == 2 && choice2 == 1){
            //do quick sort ascending
            quickSortAscending(proteinIdVec, 0, proteinIdVec.size() - 1);
        }
        if (choice1 == 2 && choice2 == 2){
            //do quick descending
            quickSortReversed(proteinIdVec, 0, proteinIdVec.size() - 1);
        }//and then somehow print the sorted stuff

        text.setString(
                proteinIdVec[idVectorIndex    ] + "\n" +
                proteinIdVec[idVectorIndex + 1] + "\n" +
                proteinIdVec[idVectorIndex + 2] + "\n" +
                proteinIdVec[idVectorIndex + 3] + "\n" +
                proteinIdVec[idVectorIndex + 4]
        )

        window.clear(sf::Color::White);
        window.draw(verifiedText);

        window.draw(inputBox);
        window.draw(output);

        window.draw(resultBox);
        window.draw(proteinName);
        window.draw(proteinSequence);

        window.draw(listBox);

        window.draw(s);
        window.draw(merge);
        window.draw(mergeText);
        window.draw(quick);
        window.draw(quickText);
        window.draw(ascending);
        window.draw(ascText);
        window.draw(descending);
        window.draw(desText);

        window.display();
    }

    return 0;
}
