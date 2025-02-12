### **📄 README **  
### **WeatherApp**  
A C++ weather application that fetches real-time weather data from **OpenWeatherMap API** and displays it in a **GUI using ImGui**. The project uses **multithreading** to keep the UI responsive while fetching data asynchronously.  

---

## **Features**
✔ Fetches weather data (temperature, humidity, wind speed, pressure, etc.)  
✔ Uses **multithreading (`std::thread`)** to prevent UI freezing  
✔ Displays real-time weather details in a **resizable UI (ImGui)**  
✔ Allows users to check weather conditions for multiple cities  
✔ Uses **HTTP requests (`httplib`)** to fetch weather data  
✔ Parses JSON responses using **nlohmann/json**  

---

## **Technologies Used**
- **C++**
- **OpenWeatherMap API**
- **ImGui** (for UI)
- **nlohmann/json** (for JSON parsing)
- **httplib** (for HTTP requests)
- **GLFW & OpenGL** (for UI rendering)
- **std::thread** (for asynchronous requests)  

---

## **Installation & Setup**
### **1. Clone the Repository**
```sh
git clone https://github.com/YOUR_USERNAME/WeatherApp.git
cd WeatherApp
```

### **2. Install Dependencies**
Ensure you have **vcpkg** installed, then install required libraries:
```sh
vcpkg install nlohmann-json:x64-windows
vcpkg install httplib:x64-windows
vcpkg install imgui[core,glfw,opengl3]:x64-windows
```

### **3. Open in Visual Studio**
1. Open **WeatherApp.sln** in **Visual Studio**  
2. Build the project (`Ctrl + Shift + B`)  
3. Run the program (`Ctrl + F5`)  

---

## **Usage**
1. Enter a **city name** to fetch weather data  
2. A **GUI window** will display weather details  
3. Close the window to enter a **new city**  
4. Type **"exit"** to quit the program  

---

## **Code Structure**
```
WeatherApp/
│── src/
│   ├── main.cpp            # Entry point
│   ├── WeatherClient.cpp   # Handles API requests
│   ├── WeatherUI.cpp       # Displays weather using ImGui
│── include/
│   ├── WeatherClient.h
│   ├── WeatherUI.h
│── assets/                 # Icons, images (optional)
│── WeatherApp.sln          # Visual Studio solution file
│── README.md               # Project documentation
```

---

## **API Key**
You need an **API key** from OpenWeatherMap:  
1. Sign up at [OpenWeatherMap](https://home.openweathermap.org/users/sign_up)  
2. Get your **free API key** from [API Keys Page](https://home.openweathermap.org/api_keys)  
3. Replace `"YOUR_API_KEY_HERE"` in `main.cpp`:  
```cpp
std::string apiKey = "YOUR_API_KEY_HERE";
```

---

## **Troubleshooting**
### **1. Can't Open `glfw3.lib`?**
Run:
```sh
vcpkg install glfw3:x64-windows
```

### **2. "Cannot Open `WeatherApp.exe`"?**
Try **running Visual Studio as Administrator**.

### **3. UI Freezes While Fetching?**
Ensure `fetchWeatherDataAsync()` is **running in a separate thread**:
```cpp
std::thread weatherThread([this, city, callback]() { ... });
```
