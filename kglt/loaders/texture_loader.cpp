#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <SOIL/SOIL.h>

#include "texture_loader.h"

#include "../kazbase/exceptions.h"
#include "../kazbase/list_utils.h"
#include "../texture.h"

namespace kglt {
namespace loaders {

void TextureLoader::into(Loadable& resource, const LoaderOptions& options) {
    Loadable* res_ptr = &resource;
    Texture* tex = dynamic_cast<Texture*>(res_ptr);
    assert(tex && "You passed a Resource that is not a texture to the TGA loader");

    int width, height, channels;
    unsigned char* data = SOIL_load_image(
        filename_.encode().c_str(),
        &width,
        &height,
        &channels,
        SOIL_LOAD_AUTO
    );

    bool dont_fallback = (container::const_get(options, _u("dont_fallback"), _u("false")) == _u("true"));

    if(!data && !dont_fallback) {
        std::cout << "Falling back to checkerboard" << std::endl;
        
        //FIXME: Don't generate this each time!
        channels = 4;
        tex->set_bpp(channels * 8);
        tex->resize(64, 64);
        uint32_t j = 0;
        uint32_t switch_counter = 0;
        bool black = true;                
        for(uint32_t i = 0; i < 64 * 64; ++i) {
            if(j++ == 7) {
                black = !black;                
                j = 0;                
            }
            
            if(i % 64 == 0) {
                switch_counter++;
                if(switch_counter == 8) {
                    black = !black;                
                    switch_counter = 0;
                }
            }
            
            if(black) {
                tex->data()[i * channels] = 0;
                tex->data()[(i * channels) + 1] = 0;
                tex->data()[(i * channels) + 2] = 0;                                
                tex->data()[(i * channels) + 3] = 255;                
            } else {
                tex->data()[i * channels] = 255;
                tex->data()[(i * channels) + 1] = 255;
                tex->data()[(i * channels) + 2] = 255;                                
                tex->data()[(i * channels) + 3] = 255;                            
            }
        }
        
    } else if (!data) {
        throw IOError("Couldn't load the file: " + filename_.encode());
    } else {
        tex->set_bpp(channels * 8);
        tex->resize(width, height);
        tex->data().assign(data, data + (width * height * channels));

        tex->flip_vertically();

        SOIL_free_image_data(data);
    }
}

}
}
