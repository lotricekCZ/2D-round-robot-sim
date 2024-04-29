#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <filesystem>
// #include <QApplication>
// #include <QPushButton>

class interface
{
private:
    /* data */
public:
    std::filesystem::path source;
    interface(/* args */);
    void open();
    void mainloop();
    ~interface();
};


#endif