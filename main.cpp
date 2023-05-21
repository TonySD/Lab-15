#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <future>
#include <mutex>
#include <exception>
#include "hash.hpp"
#include "filetools.cpp"
#include "thread_pool.hpp"


std::mutex output;

// Compare Hashes with expected or output
void comparingHashes(std::map<Hashes, std::vector<file>> files) {
    std::vector<Hashes> all_hashes { Hashes::MD5, Hashes::CRC32, Hashes::SHA256 };
    std::vector<std::future<std::string>> futures;
    ThreadPool thread_pool;
    std::string got_string;
    
    for (Hashes algorithm : all_hashes) {
        for (file current : files[algorithm]) {
            thread_pool.addTask(task(current, algorithm));
        }
    }
}

int main(int argc, const char** argv) {
    if (std::filesystem::exists("Checksum.ini")) {
        comparingHashes(parseChecksum("Checksum.ini"));
    }

    if (argc < 4 && !std::filesystem::exists("Checksum.ini")) std::cout << "Usage: " << argv[0] << " filenames -a (crc32/md5/sha256)" << std::endl;
    else if (argc >= 4) {
        comparingHashes(parseArguments(argc, argv));
    }

    return 0;
}