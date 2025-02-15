#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H

#include <string>
#include <thread>
#include <atomic>
#include <functional>  //  Needed for std::function

class WeatherClient {
private:
    std::string apiKey;  // API key for weather service
    std::thread weatherThread;  // Background thread for fetching data
    std::atomic<bool> isFetching;  // Flag to track if a request is running

public:
    explicit WeatherClient(const std::string& apiKey);
    ~WeatherClient();  // Destructor to clean up thread

    // Fetch weather asynchronously (Uses callback to send data)
    void fetchWeatherDataAsync(const std::string& city, std::function<void(std::string)> callback);

    //  Stop the current request (If the user enters a new city)
    void stopFetching();
};

#endif
ECHO is on.
