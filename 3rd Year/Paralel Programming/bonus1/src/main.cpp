#include "utils.hpp"

const auto thread_count = std::thread::hardware_concurrency();
std::barrier thread_barrier = std::barrier(thread_count);
std::vector<std::thread> threads;
std::unordered_map<std::string, uint16_t> words;
std::mutex mutex_words;
std::string buffer;

void process_words(uint32_t left_index, uint32_t right_index)
{
    thread_barrier.arrive_and_wait();

    std::unordered_map<std::string, uint16_t> current_words;
    std::string current;

    // buffer[right_index] should be a space.
    for(uint32_t index = left_index; index < right_index; index++)
    {
        // Word is done.
        const char current_char = buffer[index];
        if('a' <= current_char && 'z' >= current_char)
            current += current_char;
        else if(current != "")
        {
            current_words[current]++;
            current = "";
        }
    }
    if(current != "")
        current_words[current]++;

    // Join the maps.
    mutex_words.lock();
    for(auto element : current_words)
        words[element.first] += element.second;
    mutex_words.unlock();
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage: bonus1 <path_to_file>\n";
        return EXIT_FAILURE;
    }

    std::cout << "Using " << thread_count << " threads.\n";

    std::ifstream file(argv[1]);
    file.seekg(0, std::ios::end);
    auto size = (uint32_t)file.tellg();
    buffer = std::string((size_t)size, ' ');
    file.seekg(0);
    file.read(&buffer[0], size); 
    file.close();

    threads.reserve(thread_count);
    uint32_t left_index = (uint32_t)-1, right_index = (uint32_t)-1;
    for(auto index = 0u; index < thread_count; index++)
    {
        if(left_index == (uint32_t)-1)
            left_index = 0;

        if(index != thread_count - 1)
        {
            right_index = (size / thread_count) * (index + 1);
            while(right_index != ' ')
                right_index--;
        }
        else
            right_index = size;

        threads[index] = std::thread(process_words, left_index, right_index);
        left_index = right_index;
    }

    auto start = high_resolution_clock::now();
    for(auto index = 0u; index < thread_count; index++)
        threads[index].join();
    auto end = high_resolution_clock::now();

    auto duration_read = duration_cast<milliseconds>(end - start);

    std::cout << "Duration time: " << duration_read << "\n";

    std::ofstream fout("./output.txt");
    for(auto element : words)
        fout << element.first << " " << element.second << "\n";
    fout.close();
    return EXIT_SUCCESS;
}
