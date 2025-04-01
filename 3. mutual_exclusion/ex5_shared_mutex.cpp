#include "../util/print.hpp"
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>

using namespace std::chrono_literals;

struct DnsEntry
{
    int id{};
};

std::ostream& operator<<(std::ostream& out, const DnsEntry& entry)
{
    out << "DnsEntry: " << entry.id;
    return out;
}

class DnsCache
{
  public:
    auto findEntry(const std::string& domain) const
    {
        std::shared_lock<std::shared_mutex> lock(mutex);
        return entries.find(domain)->second;
    }

    void updateOrAddEntry(const std::string& domain, const DnsEntry& dns_details)
    {
        std::lock_guard<std::shared_mutex> lock(mutex);
        entries[domain] = dns_details;
    }

  private:
    std::map<std::string, DnsEntry> entries;
    mutable std::shared_mutex mutex;
};

int main()
{
    DnsCache cache{};
    cache.updateOrAddEntry("id", {1});

    auto sharedThreadsAction = [&cache]() {
        for (int i = 0; i < 10; i++)
        {
            print("Got: ", cache.findEntry("id"));
            std::this_thread::sleep_for(200ms);
        }
    };

    auto exclusiveThreadAction = [&cache]() {
        for (int i = 0; i < 4; i++)
        {
            auto entry = cache.findEntry("id");
            ++entry.id;
            cache.updateOrAddEntry("id", entry);
            std::this_thread::sleep_for(500ms);
        }
    };

    std::jthread thr1(sharedThreadsAction);
    std::jthread thr2(sharedThreadsAction);
    std::jthread thr3(sharedThreadsAction);
    std::jthread thr4(sharedThreadsAction);
    std::jthread thr5(exclusiveThreadAction);
}