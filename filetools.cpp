#include "all_structures.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


std::map<Hashes, std::vector<file>> parseArguments(int argc, const char** arguments) {
    std::map<Hashes, std::vector<file>> parsedFiles;
    Hashes algorithm;
    file example;
    example.expected_hash = "";
    size_t pointer = 0;
    while (strcmp(arguments[++pointer], "-a") != 0) {
        if (pointer >= argc) throw std::invalid_argument("You must specify hash-function! Check usage");
    }
    algorithm = parseAlgorithm(arguments[pointer + 1]);
    for (pointer = 1; pointer < argc; ++pointer) {
        if (strcmp(arguments[pointer], "-a") == 0) {
            algorithm = parseAlgorithm(arguments[++pointer]);
            continue;
        }
        example.filename = arguments[pointer];
        
        parsedFiles[algorithm].push_back(example);
    }
    return parsedFiles;
}

std::map<Hashes, std::vector<file>> parseChecksum(std::string checksumFilename) {
    std::ifstream in (checksumFilename);
    std::map<Hashes, std::vector<file>> parsedFiles;
    std::string current, filename;
    size_t pointer, hash_start;
    file current_file;
    Hashes algorithm;
    while (std::getline(in, current)) {
        // blank or comment
        if (';'  == current[0] || '\n' == current[0] || '\r' == current[0] ) {
            continue;
        }

        // new_algorithm
        if ('[' == current[0]) {
            pointer = 0;
            std::string string_alg;
            while (current[++pointer + 1] != ']') {}
            string_alg = current.substr(1, pointer);
            algorithm = parseAlgorithm(string_alg);
            continue;
        }

        pointer = 0;
        while (current[++pointer] != '=') {}    
        filename = current.substr(0, pointer);
        hash_start = pointer;
        if (current[pointer + 2] == 'x') hash_start += 2;
        pointer = 0;
        current_file.filename = filename;
        for (auto& character : current) { character = std::tolower(character); }
        current_file.expected_hash = current.substr(hash_start + 1, current.size() - hash_start);

        // Erasing some error char
        if (*(--current_file.expected_hash.end()) == (char) 13) {
            current_file.expected_hash.erase(--current_file.expected_hash.end());
        }

        parsedFiles[algorithm].push_back(current_file);
    }
    return parsedFiles;
}

std::vector<unsigned char> getBytesFromFile(std::string filename) {
    std::vector<unsigned char> bytes;
    std::ifstream in (filename, std::ios::binary);
    if (!in) throw std::invalid_argument("File doesn't exist!");

    char a;
    while (in.get(a)) {
        bytes.push_back(a);
    }
    bytes.shrink_to_fit();

    return bytes;
}