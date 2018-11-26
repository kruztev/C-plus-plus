//
//  Tab.hpp
//  SDP Practs
//


#ifndef Tab_hpp
#define Tab_hpp


class LinkedList
{
public:
    LinkedList();
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;
    ~LinkedList();
    
public:
    
private:
    void clear();
    
private:
    struct Tab {
        std::string url; // адрес на отворената в раздела страница
        time_t timestamp; // времево клеймо - кога е създаден разделът
        Tab* pNext; // указател към следващия раздел
        
    };
    Tab* front;
    Tab* back;
};

#endif /* Tab_hpp */
