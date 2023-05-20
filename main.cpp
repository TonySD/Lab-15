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
            futures.push_back(thread_pool.addTask(task(current, algorithm, std::promise<std::string>)));
        }
    }

    for (Hashes algorithm : all_hashes) {

    }

    for (auto &i : futures) {
        if (i.expected_hash == "") {
            std::cout << "File hash (" << algorithmToText(i.algorithm) << "): " << std::endl << i.got_hash << std::endl << std::endl;
            continue;
        }
        if (i.expected_hash != i.got_hash) {
            std::cout << "File " << i.filename << " is corrupted! (" << algorithmToText(i.algorithm) << ")" << std::endl;
            std::cout << "Expected hash: " << i.expected_hash << std::endl;
            std::cout << "Got hash: " << i.got_hash << std::endl << std::endl;
        } else {
            std::cout << "File " << i.filename << " is complete (" << algorithmToText(i.algorithm) << ")" << std::endl << std::endl;
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