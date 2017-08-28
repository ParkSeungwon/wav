#include<iostream>
#include<string>
#include<fcntl.h>//O_CRATE
#include<unistd.h>//ftruccate
#include<sys/mman.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sstream>
#include<cmath>
#include"plot.h"

#define SIZE 10000000
using namespace std;

string psstm(string);
int main(int ac, char** av)
{
	const char* name = "shared";
	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	short* ptr = (short*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	stringstream ss;
	ss << psstm(string("python readwav.py ") + av[1]); 
	int freq, channel, size;
	ss >> freq >> channel >> size;
	valarray<float> v(size);
	auto fz = linspace(0, 1, freq);
	for(int i=0; i < size; i++) v[i] = *(ptr + i);
	shm_unlink(name);

	for(int i=0; i<size/channel/freq; i++) {//cut every 1 second and draw wav, FFT
		plot(fz, v[slice{freq*i,freq,channel}]);
		auto w = linspace(0, 1, 500);
		plot(w, abs(DFT(v[slice{freq*i,freq,channel}], w)));
	}
}



