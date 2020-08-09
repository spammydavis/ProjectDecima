//
// Created by MED45 on 03.08.2020.
//

#ifndef PROJECTDS_ARCHIVE_FILE_H
#define PROJECTDS_ARCHIVE_FILE_H

#include <cstdint>
#include <vector>

#include "archive_structs.hpp"
#include "mio.hpp"

namespace Decima {
    class Archive;

    class CompressedFile {
    public:
        CompressedFile(FileEntry* file_entry_, mio::mmap_source* filebuffer_, Archive* archive_, bool encrypted_);

        CompressedFile() = default;

        std::pair<std::vector<ChunkEntry>::iterator, std::vector<ChunkEntry>::iterator> chunk_range;
        FileEntry* file_entry = nullptr;
        mio::mmap_source* filebuffer = nullptr;
        Archive* archive = nullptr;
        bool encrypted = true;

        std::vector<uint8_t> storage;

        [[nodiscard]] inline bool is_valid() const { return file_entry != nullptr; };
        void unpack(uint32_t size); //TODO: size min = find minimal size
        void decrypt(uint32_t size); //TODO: size = any
        void get_raw();
    private:

    };

}

#endif //PROJECTDS_ARCHIVE_FILE_H
