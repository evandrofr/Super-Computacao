#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include "imagem.hpp"

struct Limiar{

    __host__ __device__
    unsigned char operator()(const unsigned char &x){
        return x > 127 ? 255 : 0;
    }
    
};

int main() {
    Imagem img = Imagem::read("imagem.pgm");

    thrust::device_vector<unsigned char> img_vec(img.pixels, img.pixels + img.total_size);
    thrust::device_vector<unsigned char> img_copy(img.total_size);

    thrust::transform(img_vec.begin(), img_vec.end(), img_copy.begin(), Limiar());

    thrust::copy(img_copy.begin(), img_copy.end(), img.pixels);

    img.write("imagem_limiar.pgm");
}

