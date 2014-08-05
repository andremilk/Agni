#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>
/*
Code changed from:
http://www.dimuthu.org/blog/2009/01/28/making-web-requests-using-curl-from-c-and-php/comment-page-1/
*/
/* function prototypes to define later */
size_t static write_callback_func(void *buffer,
                        size_t size,
                        size_t nmemb,
                        void *userp);

void get_request_info(CURL *curl_handle);

/* the function to return the content for a url */
int do_web_request(char *url)
{

    /* keeps the handle to the curl object */
    CURL *curl_handle = NULL;
    char *response = NULL;
    /* to keep the response */

    /* initializing curl and setting the url */
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1);

    /* follow locations specified by the response header */
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);

    /* setting a callback function to return the data */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback_func);

    /* passing the pointer to the response as the callback parameter */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

    /* perform the request */
    long resposta;
    curl_easy_perform(curl_handle);
    curl_easy_cleanup(curl_handle);
    curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &resposta);
    return resposta;
}

/* the function to invoke as the data recieved */
size_t static write_callback_func(void *buffer,
                        size_t size,
                        size_t nmemb,
                        void *userp)
{
    char **response_ptr =  (char**)userp;

    /* assuming the response is a string */
    //*response_ptr = strndup(buffer, (size_t)(size *nmemb));
}

