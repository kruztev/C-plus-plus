//
//  FilmStar_demo.cpp
//  Exam task for work with files.
//

#include <iostream>
#include <fstream>
#include "FilmStar.h"

const unsigned short BUFFER_SIZE = 1024;

void create3()
{
    FilmStar temp;
    unsigned long long id = 0; // It would be better to use Operator >>.
    std::cin >> id;
    temp.setId(id);
    char buffer1[MAX_NAME_LENGTH];
    std::cin >> buffer1;
    temp.setFirstName(buffer1);
    char buffer2[MAX_NAME_LENGTH];
    std::cin >> buffer2;
    temp.setLastName(buffer2);
    unsigned long long films = 0;
    std::cin >> films;
    temp.setFilms(films);
    
    std::ofstream file("Films.db", std::ios::binary | std::ios::app);
    if (!file)
    {
        std::cerr << "Cannot open file for writing\n";
        return;
    }
    file.write((const char*) &temp, sizeof(FilmStar));
    std::cout << "Record saved!\n";
    if (!file.good())
    {
        std::cerr << "There is a problem when writing to file\n";
    }
    file.close();
}

void search3()
{
    unsigned long long id = 0;
    std::cin >> id;
    std::ifstream file("Films.db", std::ios::binary);
    if (!file)
    {
        std::cerr << "Cannot open file for reading\n";
        return;
    }
    FilmStar temp;
    while(!file.eof())
    {
        file.read((char*)&temp, sizeof(FilmStar));
        if(file.eof())
        {
            break;
        }
        if(temp.getId() == id)
        {
            std::cout << temp.getId() << ' ' << temp.getFirstName() << ' ' << temp.getLastName() << ' ' << temp.getFilms() << '\n';
            file.close();
            return;
        }
    }
    std::cout << "Record not found!\n";
    file.close();
    return;
}

//int main()
//{
//    const char* dictionary[] = {"create", "search", "exit"};
//
//    while(true)
//    {
//        char buffer[BUFFER_SIZE];
//        std::cin >> buffer;
//        if(!strcmp(buffer, dictionary[0]))
//        {
//            create();
//        }
//        if(!strcmp(buffer, dictionary[1]))
//        {
//            search();
//        }
//        if(!strcmp(buffer, dictionary[2]))
//        {
//            break;
//        }
//    }
//    return 0;
//}
