#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

class FileHandler
{
  public:
    FileHandler(std::string name) : fileName(name) {}

    void openFile()
    {
        std::lock_guard<std::recursive_mutex> lock(fileMutex);
        if (isOpen)
        {
            std::cout << "File " << fileName << " is already open.\n";
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate file open delay
        isOpen = true;
        std::cout << "File " << fileName << " opened.\n";
    }

    void readFile()
    {
        std::lock_guard<std::recursive_mutex> lock(fileMutex);
        if (!isOpen)
        {
            std::cout << "File " << fileName << " is not open. Opening now...\n";
            openFile(); // Call openFile() while holding the lock
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate reading delay
        std::cout << "Reading file " << fileName << ".\n";
    }

    void closeFile()
    {
        std::lock_guard<std::recursive_mutex> lock(fileMutex);
        if (!isOpen)
        {
            std::cout << "File " << fileName << " is already closed.\n";
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate file close delay
        isOpen = false;
        std::cout << "File " << fileName << " closed.\n";
    }

  private:
    std::recursive_mutex fileMutex;
    bool isOpen = false;
    std::string fileName;
};

void threadTask(FileHandler& handler)
{
    handler.readFile();
    handler.closeFile();
}

int main()
{
    FileHandler file{"example.txt"};

    std::thread t1{threadTask, std::ref(file)};
    std::thread t2{threadTask, std::ref(file)};

    t1.join();
    t2.join();

    return 0;
}
