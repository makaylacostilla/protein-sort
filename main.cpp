#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace  std;

//generic merge sort
void merge(int arr[], int left, int mid, int right){
    int arr1 = mid - left + 1;
    int arr2 = right - mid;
    auto *leftArr = new int[arr1];
    auto *rightArr = new int[arr2];

    for (auto i = 0; i < arr1; i++){
        leftArr[i] = arr[left+i];
    }
    for (auto j = 0; j < arr2; j++){
        rightArr[j] = arr[mid + 1 + j];
    }

    auto i = 0;
    auto j = 0;
    int k = left;

    while (i < arr1 && j < arr2){
        if (leftArr[i] <= rightArr[j]){
            arr[k] = leftArr[i];
            i++;
        }
        else{
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < arr1){
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < arr2){
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int l, int r){
    if (l >= r){
        return;
    }

    int m = l + (r - l)/2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

//generic quick sort
int partition(int arr[], int low, int high){
    int pivot = arr[high];

    int i = low - 1;
    for (int j = low; j <= high - 1; j++){
        if (arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i+1);
}

void quickSort(int arr[], int low, int high){
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int main() {
    //test
    //int arr[] = {12, 11, 13, 5, 6, 7};
    //int size = sizeof(arr)/sizeof(arr[0]);

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
        sf::Event event{};
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
                    //change proteinName to name
                    //change proteinSequence to sequence
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
        }
        if (choice1 == 1 && choice2 == 2 ){
            //do merge descending
        }
        if (choice1 == 2 && choice2 == 1){
            //do quick sort ascending
        }
        if (choice1 == 2 && choice2 == 2){
            //do quick descending
        }//and then somehow print the sorted stuff

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
