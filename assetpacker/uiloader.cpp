#include <string>
#include <fstream>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <vector>
#include <core/binaryfile.hpp>

// NAME IS ALWAYS 15 BYTES LONG
// .ui files look like this:
// UINT8                          - amount of textures
// ----------------------------------------------------- repeats from this
// UINT8 * 15                     - name
// UINT16                         - width
// UINT16                         - height
// UINT8 * ((width * height) * 4) - data

namespace uipacker{
    void makeui(std::string path){

        std::string realpath("assets/");
        realpath.append(path);
        realpath.append("/");

        binaryFile outputfile;
        std::string outputpath("../assets/");
        outputpath.append(path).append(".ui");
        outputfile.open(outputpath.c_str(), true);

        uint8_t fileamount = 0;
        for (const auto & file : std::filesystem::directory_iterator(realpath.c_str())){
            fileamount++;
        }

        outputfile.write(fileamount);

        for (const auto & file : std::filesystem::directory_iterator(realpath.c_str())){

            std::string filename(file.path().c_str());
            int textureX, textureY, channels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char* data = stbi_load(filename.c_str(), &(textureX), &(textureY), &channels, 4);

            std::string shortfilename_placeholder = filename.substr(filename.find_last_of('/')+1);
            std::string realshortname = shortfilename_placeholder.substr(0 , (shortfilename_placeholder.length() - 4));

            outputfile.writeChars(realshortname.c_str(), 15);
            outputfile.write((uint16_t)textureX);
            outputfile.write((uint16_t)textureY);
            outputfile.writeChars(data, textureX*textureY*4);

            delete[] data;
        }

        outputfile.close();
    }
}