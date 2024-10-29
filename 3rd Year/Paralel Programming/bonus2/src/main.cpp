#include "utils.hpp"

std::mutex mutex;
std::condition_variable cv;
bool ready = false;
int current_product = 0;

void producer_task(const std::vector<int>& vector1, const std::vector<int>& vector2) {
    for (size_t index = 0; index < vector1.size(); index++) {
        std::unique_lock<std::mutex> lock(mutex);
        current_product = vector1[index] * vector2[index];
        ready = true;
        cv.notify_one();
        cv.wait(lock, [] { return !ready; });
    }
    std::unique_lock<std::mutex> lock(mutex);
    ready = true;
    current_product = -1;
    cv.notify_one();
}

void consumer_task() {
    int total = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [] { return ready; });
        if (current_product == -1)
            break;
        total += current_product;
        ready = false;
        cv.notify_one();
    }
    std::cout << "\nScalar product: " << total << "\n\n";
}

int main() {
    std::vector<int> vector1 = {1, 2};
    std::vector<int> vector2 = {3, 4};

    std::thread producer(producer_task, vector1, vector2);
    std::thread consumer(consumer_task);

    producer.join();
    consumer.join();

    return 0;
}
