//
//  main.cpp
//  Student Queue
//
//  Alexander Krustev FN 45314
//  Code ran and tested on Xcode 10.1
//


#include <iostream>
#include <string>
#include <fstream>
#include <list>


struct Student
{
    std::string name;
    size_t group;
    size_t minutesWaiting;
    
    Student(std::string newName, size_t newGroup, size_t minutes = 0) :
        name(newName),
        group(newGroup),
        minutesWaiting(minutes)
    {}
};

typedef std::list<Student> studentQueue;

void checkForFrinedsAndPushBack(studentQueue& queue, const Student& newStudent) // Checking the queue for "friends".
{
    for (studentQueue::iterator i = queue.begin(); i != queue.end(); ++i)
    {
        if (i->group == newStudent.group)
        {
            while (i->group == newStudent.group) // Skipping all friends from the group and adding the new student right after them.
            {
                ++i;
            }
            queue.insert(i, newStudent);
            return;
        }
    }
    queue.push_back(newStudent);
}

void incrementMinutesWaiting(studentQueue& queue) // Incrementing every student's minutesWaiting variable.
{
    for (studentQueue::iterator i = queue.begin(); i != queue.end(); ++i)
    {
        i->minutesWaiting++;
    }
}

void queueAndDequeue(studentQueue& queue) // Reading student's data from the file and calculating their time spent in the queue.
{
    std::ifstream inStream;
    inStream.open("students.txt");
    if (!inStream)
    {
        std::cerr << "Cannot open file for reading\n";
        return;
    }
    
    size_t minutes = 1;
    while (!inStream.eof())
    {
        std::string name;
        size_t group;
        inStream >> name >> group;
        if(inStream.eof()) // When all student's data is read from the file, the loop must end.
        {
            break;
        }
        Student temp(name, group);
        checkForFrinedsAndPushBack(queue, temp);
        incrementMinutesWaiting(queue);
        if (minutes % 2 == 0)
        {
            Student temp = queue.front();
            std::cout << temp.name << ' ' << temp.minutesWaiting << 'm' << '\n';
            queue.pop_front();
        }
        minutes++;
    }
    
    while(!queue.empty()) // Printing left in the queue student's data.
    {
        incrementMinutesWaiting(queue);
        if (minutes % 2 == 0)
        {
            Student temp = queue.front();
            std::cout << temp.name << ' ' << temp.minutesWaiting << 'm' << '\n';
            queue.pop_front();
        }
        minutes++;
    }
    
    inStream.close();
}

int main()
{
    
    studentQueue queue;
    
    queueAndDequeue(queue);
    
    return 0;
}
