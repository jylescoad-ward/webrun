#include <iostream>
#include <curl/curl.h>
#include <string>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
	  std::cerr << argv[0] << ": Wrong number of arguments" << std::endl
			<< argv[0] << ": Usage: " << " url "
			<< std::endl;
	  return EXIT_FAILURE;
	}
	CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = argv[1];
    char outfilename[FILENAME_MAX] = ".webruntempfile";
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
	// its a pretty retarded way of doing this
	// but its the best i could come up with and
	// im very lazy at the moment to implement
	// anything better
	system("chmod +x ./.webruntempfile");
	system("./.webruntempfile && rm -rf ./.webruntempfile");
    return 0;
}
