#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include "imagem.hpp"

struct media{

    unsigned char *ptr;
    int width, heigth;

    media(unsigned char *ptr, int width, int heigth) : ptr(ptr), width(width), heigth(heigth){};

    __host__ __device__
    unsigned char operator()(const unsigned char &i){
        int x = i % width;
        int y = i / width;

        unsigned char current = ptr[y * width + x];

        unsigned char forward  = (x + 1 <= heigth) ? ptr[y * width + (x + 1)] : 0;
        unsigned char backward = (x - 1 >= 0)      ? ptr[y * width + (x - 1)] : 0;
        unsigned char top      = (y - 1 >= 0)      ? ptr[(y - 1) * width + x] : 0;
        unsigned char down     = (y + 1 <= width)  ? ptr[(y + 1) * width + x] : 0;

        return (current + forward + backward + top + down) / 5;

    }
    
};

int main() {
    Imagem img = Imagem::read("imagem.pgm");

    thrust::device_vector<unsigned char> img_vec(img.pixels, img.pixels + img.total_size);
    thrust::device_vector<unsigned char> img_copy(img.total_size);

    thrust::counting_iterator<int> iter(0);

    media mean(img_vec.data().get(), img.cols, img.rows);
    thrust::transform(iter, iter + img_vec.size(), img_copy.begin(), mean);

    thrust::copy(img_copy.begin(), img_copy.end(), img.pixels);

    img.write("imagem_media.pgm");
}

