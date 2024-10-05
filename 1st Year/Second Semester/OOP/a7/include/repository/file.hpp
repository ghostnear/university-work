#pragma once

#include <fstream>
#include "memory.hpp"

template<typename TElem>
class FileRepository : public MemoryRepository<TElem>
{
protected:
    std::string filename;

public:
    FileRepository(std::string filename) : filename(filename) { read_from_file(); }

    void write_to_file()
    {
        std::ofstream fout(filename);

        for(auto& element : data)
            fout << element << "\n";

        fout.close();
    }

    void read_from_file()
    {
        std::ifstream fin(filename);

        if(!fin.is_open())
            return;

        TElem element;
        while(fin >> element)
            data.push_back(element);    // we do not add normally as we do not want to trigger the file write.

        fin.close();
    }

    void add_element(TElem element) override
    {
        data.push_back(element);
        write_to_file();
    }

    void update_element(std::size_t index, TElem newData) override
    {
        data[index] = newData;
        write_to_file();
    }

    void delete_element(std::size_t index) override
    {
        std::swap(data[index], data.back());
        data.pop_back();
        write_to_file();
    }
};