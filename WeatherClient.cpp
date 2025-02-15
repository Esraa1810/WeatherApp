#include "WeatherClient.h"
#include <iostream>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <ctime>

using json = nlohmann::json;

// Constructor
WeatherClient::WeatherClient(const std::string& apiKey) : apiKey(apiKey), isFetching(false) {}

// Destructor (Ensures thread cleanup)
WeatherClient::~WeatherClient() {
    stopFetching();
    if (weatherThread.joinable()) {
        weatherThread.join();
    }
}

// Convert UNIX timestamp to human-readable format
std::string unixToTime(int unixTime) {
    time_t t = unixTime;
    struct tm timeinfo;
    localtime_s(&timeinfo, &t);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeinfo);
    return std::string(buffer);
}

// Fetch weather data asynchronously
void WeatherClient::fetchWeatherDataAsync(const std::string& city, std::function<void(std::string)> callback) {
    stopFetching(); // Stop previous request if running

    // Start a new thread to fetch weather data
    weatherThread = std::thread([this, city, callback]() {
        isFetching = true;

        httplib::Client cli("http://api.openweathermap.org");
        std::string url = "/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";

        auto res = cli.Get(url.c_str());

        if (!isFetching) return; // If user stopped request, exit thread

        if (res && res->status == 200) {
            json data = json::parse(res->body);

            // Extract all relevant weather details
            double temp = data["main"].value("temp", 0.0);
            double feelsLike = data["main"].value("feels_like", 0.0);
            double tempMin = data["main"].value("temp_min", 0.0);
            double tempMax = data["main"].value("temp_max", 0.0);
            int humidity = data["main"].value("humidity", 0);
            int pressure = data["main"].value("pressure", 0);
            double windSpeed = data["wind"].value("speed", 0.0);
            int windDirection = data["wind"].value("deg", 0);
            int visibility = data.value("visibility", 10000);
            int cloudCoverage = data["clouds"].value("all", 0);
            int sunrise = data["sys"].value("sunrise", 0);
            int sunset = data["sys"].value("sunset", 0);

            //  Check for rain/snow data
            double rain1h = data.contains("rain") ? data["rain"].value("1h", 0.0) : 0.0;
            double rain3h = data.contains("rain") ? data["rain"].value("3h", 0.0) : 0.0;
            double snow1h = data.contains("snow") ? data["snow"].value("1h", 0.0) : 0.0;
            double snow3h = data.contains("snow") ? data["snow"].value("3h", 0.0) : 0.0;

            std::string description = data["weather"][0].value("description", "Unknown");

            //  Format the result string (Now includes all data)
            std::string result = " Weather in " + city + ":\n";
            result += " Condition: " + description + "\n";
            result += " Temperature: " + std::to_string(temp) + "°C\n";
            result += " Feels Like: " + std::to_string(feelsLike) + "°C\n";
            result += " Min Temp: " + std::to_string(tempMin) + "°C,  Max Temp: " + std::to_string(tempMax) + "°C\n";
            result += " Humidity: " + std::to_string(humidity) + "%\n";
            result += " Pressure: " + std::to_string(pressure) + " hPa\n";
            result += " Wind: " + std::to_string(windSpeed) + " m/s, Direction: " + std::to_string(windDirection) + "°\n";
            result += " Visibility: " + std::to_string(visibility / 1000.0) + " km\n";
            result += " Cloud Coverage: " + std::to_string(cloudCoverage) + "%\n";
            result += " Sunrise: " + unixToTime(sunrise) + " |  Sunset: " + unixToTime(sunset) + "\n";

            if (rain1h > 0) result += "🌧 Rain (Last 1h): " + std::to_string(rain1h) + " mm\n";
            if (rain3h > 0) result += "🌧 Rain (Last 3h): " + std::to_string(rain3h) + " mm\n";
            if (snow1h > 0) result += "❄ Snow (Last 1h): " + std::to_string(snow1h) + " mm\n";
            if (snow3h > 0) result += "❄ Snow (Last 3h): " + std::to_string(snow3h) + " mm\n";

            callback(result);
        }
        else {
            callback("Error: Could not fetch weather data.");
        }

        isFetching = false;
        });

    weatherThread.detach();
}

// Stop the current request
void WeatherClient::stopFetching() {
    isFetching = false;
    if (weatherThread.joinable()) {
        weatherThread.join();
    }
}
ECHO is on.
