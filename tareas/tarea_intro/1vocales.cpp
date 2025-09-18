#include <iostream>

int main() {
    std::string frase;
    int contador = 0;

    std::cout<<"Ingresa una frase"<<std::endl;
    std::cin>>frase;
    
    int len = frase.length();

    for (char temp : frase) {
        temp = tolower(temp);
        if (temp=='a' || temp=='e' || temp=='i' || temp=='o' || temp=='u') {
          contador++;
        }
    }

    std::cout << contador << std::endl;

    return 0;
}
